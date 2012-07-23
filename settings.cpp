#include "settings.h"

Settings::Settings()
{
    config = new QSettings("TimeIPS", "SupportMessage");
}

bool Settings::isConfigured()
{
    bool imConfigured = config->contains("im/client") && config->contains("im/account") && config->contains("im/buddies");
    bool mailConfigured = config->contains("mail/host") && config->contains("mail/username");

    return imConfigured && mailConfigured;
}
