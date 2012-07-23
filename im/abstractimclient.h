#ifndef ABSTRACTIMCLIENT_H
#define ABSTRACTIMCLIENT_H

#include <QObject>

#include "models/account.h"
#include "models/buddy.h"

class AbstractImClient : public QObject
{
    Q_OBJECT
public:
    explicit AbstractImClient(QObject *parent = 0);

    virtual QList<Account> getAccounts() = 0;
    virtual QList<Buddy> getBuddies(int) = 0;

public slots:
    virtual int im(int, Buddy, QString) = 0;

signals:
    void inaccessible(QString);
    void failed(QString);
    void successful();
};

#endif // ABSTRACTIMCLIENT_H
