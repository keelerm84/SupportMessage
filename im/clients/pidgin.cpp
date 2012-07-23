#include "pidgin.h"
#include <QDBusConnection>
#include <QDBusPendingReply>

Pidgin::Pidgin(QObject * parent) : AbstractImClient(parent)
{
    pidgin = new PidginService("im.pidgin.purple.PurpleService", "/im/pidgin/purple/PurpleObject", QDBusConnection::sessionBus(), 0);
}

QList<Account> Pidgin::getAccounts()
{
    QList<Account> accounts;
    QDBusPendingReply<QList<int> > reply = pidgin->PurpleAccountsGetAll();
    reply.waitForFinished();

    if ( reply.isError() ) return accounts;

    foreach(int accountId, reply.value() ) {
        Account a(accountId);
        a.setName(lookupAccountName(accountId));
        a.setAlias(lookupAccountAlias(accountId));

        accounts.append(a);
    }

    return accounts;
}

QList<Buddy> Pidgin::getBuddies(int accountId)
{
    QList<Buddy> buddies;
    QDBusPendingReply<QList<int> > reply = pidgin->PurpleFindBuddies(accountId, "");
    reply.waitForFinished();

    if ( reply.isError() ) return buddies;

    foreach(int buddyId, reply.value() ) {
        Buddy b(lookupBuddyName(buddyId));
        b.setAlias(lookupBuddyAlias(buddyId));

        buddies.append(b);
    }

    return buddies;
}

int Pidgin::im(int accountId, Buddy buddy, QString message)
{
    QDBusPendingReply<int> convReply = pidgin->PurpleConversationNew(1, accountId, buddy.name());
    convReply.waitForFinished();

    if ( convReply.isError() ) return -1;
    int conversationId = convReply.value();

    QDBusPendingReply<int> msgReply = pidgin->PurpleConversationGetImData(conversationId);
    msgReply.waitForFinished();

    if ( msgReply.isError() ) return -2;
    int msgId = msgReply.value();

    QDBusPendingReply<> sendReply = pidgin->PurpleConvImSend(msgId, message);
    sendReply.waitForFinished();

    if ( sendReply.isError() ) return -3;
    pidgin->PurpleConversationDestroy(conversationId);
}

QString Pidgin::lookupAccountAlias(int accountId) {
    QDBusPendingReply<QString> reply = pidgin->PurpleAccountGetAlias(accountId);
    reply.waitForFinished();


    if ( reply.isError() ) return "";

    return reply.value();

}

QString Pidgin::lookupAccountName(int accountId) {
    QDBusPendingReply<QString> reply = pidgin->PurpleAccountGetNameForDisplay(accountId);
    reply.waitForFinished();

    if ( reply.isError() ) return "";

    return reply.value();
}

QString Pidgin::lookupBuddyAlias(int buddyId) {
    QDBusPendingReply<QString> reply = pidgin->PurpleBuddyGetAlias(buddyId);
    reply.waitForFinished();

    if ( reply.isError() ) {
        return "";
    }

    return reply.value();
}

QString Pidgin::lookupBuddyName(int buddyId) {
    QDBusPendingReply<QString> reply = pidgin->PurpleBuddyGetName(buddyId);
    reply.waitForFinished();

    if ( reply.isError() ) {
        return "";
    }

    return reply.value();
}
