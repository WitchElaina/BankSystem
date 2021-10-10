#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "register.h"
#include "ui_register.h"

namespace Ui {
class LogInDialog;
}

class LogInDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LogInDialog(QWidget *parent = nullptr);
    ~LogInDialog();
    QString username;
    QString password;
    bool loginStatus=false;
    void loginExec();

    // validate username
    bool findUsername(QString m_usrname);

    // verify password
    bool verifyPassword(QString m_usrname, QString m_password);

    // login
    void userLogin(QString m_usrname, QString m_password);

private slots:
    void on_userName_textChanged(const QString &arg1);

    void on_userPassword_textChanged(const QString &arg1);

    void on_userRegister_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::LogInDialog *ui;
};

#endif // LOGINDIALOG_H
