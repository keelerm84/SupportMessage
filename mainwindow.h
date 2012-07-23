#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void show();

protected slots:
    void showConfiguration();
    void showMessage();

private:
    Ui::MainWindow *ui;
    Settings settings;
};

#endif // MAINWINDOW_H
