#ifndef ACCOUNTCONFIGURATION_H
#define ACCOUNTCONFIGURATION_H

#include <QDialog>
#include "im/abstractimclient.h"
#include "settings.h"

namespace Ui {
class AccountConfiguration;
}

class AccountConfiguration : public QDialog
{
    Q_OBJECT

public:
    explicit AccountConfiguration(Settings *, QWidget *parent = 0);
    ~AccountConfiguration();

protected:
    void populateSupportedClients();
    void restoreSelections();
    void restoreEmailSettings();
    void setupSignals();

protected slots:
    void populateAccounts(int);
    void populateBuddies(int);
    void assignImClient(int);
    void saveSettings();

signals:
    void configured();

private:
    Ui::AccountConfiguration *ui;
    AbstractImClient * imClient;
    Settings * settings;
};

#endif // ACCOUNTCONFIGURATION_H
