#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "logindialog.h"
#include "ui_logindialog.h"
#include "createsavaccountdialog.h"
#include "ui_createsavaccountdialog.h"
#include "createcreaccountdialog.h"
#include "ui_createcreaccountdialog.h"
#include "querydialog.h"
#include "ui_querydialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // show messagebox with custom string
    void showMessageBox(QString m_msg);

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

    void on_pushButton_cre_deposite_clicked();

    void on_pushButton_cre_withdraw_clicked();

    void on_pushButton_create_credit_account_clicked();

    void on_pushButton_create_savings_acount_clicked();

    void on_dateEdit_userDateChanged(const QDate &date);

    void on_pushButton_print_record_clicked();

    void on_pushButton_change_password_pressed();

    void on_pushButton_change_password_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
