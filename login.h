#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "register.h"
#include "ui_register.h"



namespace Ui {
class LogIn;
}

class LogIn : public QWidget
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();
    QString username;
    QString password;




private:
    Ui::LogIn *ui;


public slots:

// validate username
bool findUsername(QString m_usrname);

// verify password
bool verifyPassword(QString m_usrname, QString m_password);

// login
void userLogin(QString m_usrname, QString m_password);

// press Quit button
void on_userQuit_clicked();

void on_userName_textChanged();
private slots:
void on_userPassword_textChanged();
void on_logIn_clicked();
void on_userPassword_textChanged(const QString &arg1);
void on_userRegister_clicked();
void on_forgotPassword_clicked();
};

#endif // LOGIN_H
