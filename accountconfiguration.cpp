#include "accountconfiguration.h"
#include "ui_accountconfiguration.h"
#include "im/clients/pidgin.h"
#include "im/clients/none.h"
#include "im/clients/imclient.h"
#include <QListWidgetItem>

AccountConfiguration::AccountConfiguration(Settings * settings, QWidget *parent) : QDialog(parent), ui(new Ui::AccountConfiguration), imClient(0), settings(settings)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentIndex(0);

    populateSupportedClients();
    restoreSelections(); // Must be called before signals are connected to ensure they don't fire when restoring selections
    restoreEmailSettings();
    setupSignals();

}

AccountConfiguration::~AccountConfiguration()
{
    delete ui;
}

void AccountConfiguration::populateSupportedClients()
{
    ui->cmbClients->addItem(QIcon(":/images/no-selection.png"), "None", "none");
    ui->cmbClients->addItem(QIcon(":/images/pidgin.png"), "Pidgin", "pidgin");
}

void AccountConfiguration::restoreSelections()
{
    int clientIndex = ui->cmbClients->findData(settings->client());
    if ( -1 == clientIndex ) return; // No suported client matches the configuration option

    ui->cmbClients->setCurrentIndex(clientIndex);

    populateAccounts(clientIndex);
    int accountIndex = ui->cmbAccounts->findData(settings->account());
    if ( -1 == accountIndex ) return;
    ui->cmbAccounts->setCurrentIndex(accountIndex);

    populateBuddies(accountIndex);
    QStringList buddies = settings->buddies();

    for(int i = 0; i < ui->lstBuddies->count(); ++i) {
        QListWidgetItem * item = ui->lstBuddies->item(i);

        if ( buddies.contains(item->data(Qt::UserRole).toString()) )
            ui->lstBuddies->setCurrentItem(item, QItemSelectionModel::Select);
    }
}

void AccountConfiguration::restoreEmailSettings()
{
    ui->txtHost->setText(settings->host());
    ui->txtPort->setText(QString::number(settings->port()));
    ui->txtUsername->setText(settings->username());
    ui->txtPassword->setText(settings->password());

    if ( settings->useSsl() ) ui->chkUseSsl->setCheckState(Qt::Checked);
}

void AccountConfiguration::setupSignals()
{
    connect(ui->cmbClients, SIGNAL(currentIndexChanged(int)), this, SLOT(populateAccounts(int)));
    connect(ui->cmbAccounts, SIGNAL(currentIndexChanged(int)), this, SLOT(populateBuddies(int)));

    connect(ui->btnBoxSaveOrCancel, SIGNAL(accepted()), this, SLOT(saveSettings()));
    connect(ui->btnBoxSaveOrCancel, SIGNAL(rejected()), this, SLOT(close()));
}

void AccountConfiguration::populateAccounts(int clientIndex)
{
    assignImClient(clientIndex);
    QList<Account> accounts = imClient->getAccounts();

    ui->cmbAccounts->clear();
    foreach(Account account, accounts) {
        ui->cmbAccounts->addItem(account.name(), account.id());
    }
}

void AccountConfiguration::populateBuddies(int accountIndex)
{
    int accountId = ui->cmbAccounts->itemData(accountIndex, Qt::UserRole).toInt();
    QList<Buddy> buddies = imClient->getBuddies(accountId);

    ui->lstBuddies->clear();
    foreach(Buddy buddy, buddies) {
        QListWidgetItem * item = new QListWidgetItem(buddy.alias());
        item->setData(Qt::UserRole, buddy.name());
        ui->lstBuddies->addItem(item);
    }
}

void AccountConfiguration::assignImClient(int clientIndex)
{
    QString clientName = ui->cmbClients->itemData(clientIndex, Qt::UserRole).toString();

    if ( imClient ) imClient->deleteLater();

    imClient = ImClient::getImClient(clientName);
    imClient->setParent(this);
}

void AccountConfiguration::saveSettings()
{
    QString client = ui->cmbClients->itemData(ui->cmbClients->currentIndex(), Qt::UserRole).toString();
    int account = ui->cmbAccounts->itemData(ui->cmbAccounts->currentIndex(), Qt::UserRole).toInt();

    QList<QListWidgetItem *> buddies = ui->lstBuddies->selectedItems();
    QStringList buddyNames;

    foreach(QListWidgetItem * item, buddies) {
        buddyNames.append(item->data(Qt::UserRole).toString());
    }

    settings->setClient(client);
    settings->setAccount(account);
    settings->setBuddies(buddyNames);

    settings->setHost(ui->txtHost->text());
    settings->setPort(ui->txtPort->text().toInt());
    settings->setUseSsl(ui->chkUseSsl->isChecked());
    settings->setUsername(ui->txtUsername->text());
    settings->setPassword(ui->txtPassword->text());

    emit configured();

    close();
}
