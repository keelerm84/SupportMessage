#ifndef MESSAGE_H
#define MESSAGE_H

#include <QWidget>
#include "settings.h"
#include "im/models/buddy.h"

namespace Ui {
class Message;
}

class Message : public QWidget
{
    Q_OBJECT

public:
    explicit Message(Settings *, QWidget *parent = 0);
    ~Message();

protected slots:
    void clearForm(bool confirm = true);
    void sendMessage();

protected:
    void buildBuddyList();
    void sendEmail();
    void notifyOfEmail();

private:
    Ui::Message *ui;
    Settings *settings;

    QList<Buddy> buddies;
};

#endif // MESSAGE_H
