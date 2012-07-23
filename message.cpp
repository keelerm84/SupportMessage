#include "message.h"
#include "ui_message.h"
#include <QMessageBox>
#include "im/clients/imclient.h"
#include "abstractimclient.h"
#include "SmtpClient/SmtpMime"

Message::Message(Settings * settings, QWidget *parent) : settings(settings), QWidget(parent), ui(new Ui::Message)
{
    ui->setupUi(this);

    connect(ui->btnClear, SIGNAL(clicked()), this, SLOT(clearForm()));
    connect(ui->btnSend, SIGNAL(clicked()), this, SLOT(sendMessage()));

    buildBuddyList();
}

Message::~Message()
{
    delete ui;
}

void Message::clearForm(bool confirm)
{
    if ( confirm ) {
        QMessageBox prompt;
        prompt.setWindowTitle(tr("Confirm Clear"));
        prompt.setText(tr("Are you sure you wish to clear all of the message information?  Once cleared, it must be re-entered."));
        prompt.setInformativeText("Do you want to clear all changes?");
        prompt.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        int ret = prompt.exec();

        if ( ret == QMessageBox::No ) return;
    }

    ui->txtCustNo->setText("");
    ui->txtContact->setText("");
    ui->txtPhone->setText("");
    ui->txtSubject->setText("");
    ui->txtMessage->setText("");
}

void Message::sendMessage()
{
    sendEmail();
    notifyOfEmail();
    clearForm(false);
}

void Message::buildBuddyList()
{
    buddies.empty();

    AbstractImClient * client = ImClient::getImClient(settings->client());
    QStringList notifyBuddyNames = settings->buddies();

    foreach(Buddy buddy, client->getBuddies(settings->account()) ) {
        if ( notifyBuddyNames.contains(buddy.name())) {
            buddies.append(buddy);
        }
    }

    client->deleteLater();
}

void Message::sendEmail()
{
    QString subject = QString("C#%1 -- %2").arg(ui->txtCustNo->text()).arg(ui->txtSubject->text());
    QString body = QString("Contact %1 at %2\n\n%3").arg(ui->txtContact->text()).arg(ui->txtPhone->text()).arg(ui->txtMessage->toPlainText());

    SmtpClient smtp(settings->host(), settings->port(), settings->useSsl() ? SmtpClient::SslConnection : SmtpClient::TcpConnection);
    smtp.setUser(settings->username());
    smtp.setPassword(settings->password());

    MimeMessage message;
    message.setSender(new EmailAddress("supportinfo@timeips.com", "TimeIPS Support Message"));
    message.addRecipient(new EmailAddress("supportinfo@timeips.com", "TimeIPS Support"));
    message.setSubject(subject);

    MimeText text;
    text.setText(body);

    message.addPart(&text);

    smtp.connectToHost();
    smtp.login();
    smtp.sendMail(message);
    smtp.quit();
}

void Message::notifyOfEmail()
{
    AbstractImClient * client = ImClient::getImClient(settings->client());
    bool failedToSendIm = false;
    foreach(Buddy buddy, buddies) {
        if ( 0 != client->im(settings->account(), buddy, tr("A new message has been sent to the support queue.")) ) {
            failedToSendIm = true;
        }
    }
    client->deleteLater();
}
