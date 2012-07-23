#ifndef BUDDY_H
#define BUDDY_H

#include <QString>

class Buddy
{
public:
    Buddy(QString);

    QString name()  { return m_name; }
    QString alias() { return m_alias; }

    void setAlias(QString a) { m_alias = a; }

private:
    QString m_alias;
    QString m_name;
};

#endif // BUDDY_H
