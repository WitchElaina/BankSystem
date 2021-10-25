#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "ui_logindialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // initialize user data
    void userInit(LogInDialog *m_login_dialog);

    // flash data throw commmand lines
    void flashuserData();

    // flash GUI
    void flashGUI();
private slots:


    void on_pushButton_logout_clicked();

    void on_pushButton_sav_deposite_clicked();

    void on_pushButton_sav_withdraw_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
