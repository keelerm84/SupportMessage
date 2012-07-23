#ifndef NONE_H
#define NONE_H

#include "../abstractimclient.h"

class None : public AbstractImClient
{
public:
    explicit None(QObject * parent = 0);

    QList<Account> getAccounts() { return QList<Account>(); }
    QList<Buddy> getBuddies(int) { return QList<Buddy>(); }

public slots:
    int im(int, Buddy, QString) { emit inaccessible(tr("No valid client has been selected.")); }
};

#endif // NONE_H
