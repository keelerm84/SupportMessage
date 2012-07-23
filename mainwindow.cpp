#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include "accountconfiguration.h"
#include "message.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("TimeIPS Support Message Recorder"));

    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionConfiguration, SIGNAL(triggered()), this, SLOT(showConfiguration()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::show()
{
    QMainWindow::show();
    if ( ! settings.isConfigured() ) {
        showConfiguration();
    } else {
        showMessage();
    }
}

void MainWindow::showConfiguration()
{
    AccountConfiguration config(&settings, this);

    connect(&config, SIGNAL(configured()), this, SLOT(showMessage()));

    config.setModal(true);
    config.exec();
}

void MainWindow::showMessage()
{
    Message * message = new Message(&settings, this);
    setCentralWidget(message);
}
