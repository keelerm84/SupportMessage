#ifndef PIDGIN_H
#define PIDGIN_H

#include "../abstractimclient.h"
#include "pidginservice.h"

class Pidgin : public AbstractImClient
{
public:
    explicit Pidgin(QObject *parent = 0);

    QList<Account> getAccounts();
    QList<Buddy> getBuddies(int);

public slots:
    int im(int, Buddy, QString);

protected:
    QString lookupAccountAlias(int);
    QString lookupAccountName(int);

    QString lookupBuddyAlias(int);
    QString lookupBuddyName(int);

private:
    PidginService * pidgin;

};

#endif // PIDGIN_H
