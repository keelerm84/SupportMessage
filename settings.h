#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QVariant>
#include <QStringList>
#include "datatypes.h"

class Settings
{
public:
    explicit Settings();

    // IM Settings
    inline QString client()                 { return config->value("im/client", "none").toString(); }
    inline void setClient(QString c)        { config->setValue("im/client", c); }

    inline int account()                    { return config->value("im/account", -1).toInt(); }
    inline void setAccount(int a)           { config->setValue("im/account", a); }

    inline QStringList buddies()             { return config->value("im/buddies").toStringList(); }
    inline void setBuddies(QStringList b)    { config->setValue("im/buddies", b); }

    // Email Settings
    inline QString host()                   { return config->value("mail/host", "localhost").toString(); }
    inline void setHost(QString h)          { config->setValue("mail/host", h); }

    inline int port()                       { return config->value("mail/port", 25).toInt(); }
    inline void setPort(int p)              { config->setValue("mail/port", p); }

    inline bool useSsl()                    { return config->value("mail/useSsl", true).toBool(); }
    inline void setUseSsl(bool ssl)         { config->setValue("mail/useSsl", ssl); }

    inline QString username()               { return config->value("mail/username", "").toString(); }
    inline void setUsername(QString u)      { config->setValue("mail/username", u); }

    inline QString password()               { return config->value("mail/password", "").toString(); }
    inline void setPassword(QString p)      { config->setValue("mail/password", p); }

    // Misc.
    bool isConfigured();

private:
    QSettings * config;

};

#endif // SETTINGS_H
