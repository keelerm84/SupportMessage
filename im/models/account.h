#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>

class Account
{
public:
    Account(int);

    void setName(QString n)     { m_name = n; }
    void setAlias(QString a)    { m_alias = a; }

    int id()                    { return m_id; }
    QString name()              { return m_name; }
    QString alias()             { return m_alias; }

private:
    int m_id;
    QString m_name;
    QString m_alias;

};

#endif // ACCOUNT_H
