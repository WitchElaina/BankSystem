#include "login.h"
#include "ui_login.h"



#include <QObject>
#include <QMessageBox>
#include <QDataStream>
#include <QFile>
#include <QHash>
#include <iostream>
#include <QDebug>



using namespace std;

LogIn::LogIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);

}

LogIn::~LogIn()
{
    delete ui;
}



bool LogIn::findUsername(QString m_usrname)
{
    // open user data file in readonly mode
    QFile usr_data("UserData.dat");
    bool isOpened;

    // check if the UserData file is opened correctly
    isOpened=usr_data.open(QIODevice::ReadWrite);
    if(!isOpened)
    {
        throw "Error!Can't find UserData!";
    }

    QDataStream usr_data_stream(&usr_data);
    QHash<QString, QString> finder;
    usr_data_stream>>finder;
    usr_data.close();

    if(1)
    {
        // find the input username successfully
        return 1;
    }
    return 0;
}


bool LogIn::verifyPassword(QString m_usrname, QString m_password)
{
    // open user data file in readonly mode
    QFile usr_data("UserData.dat");
    usr_data.open(QIODevice::ReadWrite);
    QDataStream usr_data_stream(&usr_data);
    QHash<QString, QString> finder;
    usr_data_stream>>finder;
    usr_data.close();
    qDebug()<<finder.find(m_usrname).value();

    // verify the Password
    if(finder.find(m_usrname).value()==m_password)
    {
        return  1;
    }
    else
    {
        return  0;
    }
}

void LogIn::userLogin(QString m_usrname, QString m_password)
{
    try {
        if(findUsername(m_usrname)) {
            if(verifyPassword(m_usrname,m_password)) {
                // login successfully
            }
            else {
                // password is incorrect
                throw false;
            }
        }

    }
    catch (QString msg) {
        // can't find Data file
    }
    catch (bool) {
        // password is incorrect
    }
}

void LogIn::on_userQuit_clicked()
{
    qDebug()<<"press exit button";
    QMessageBox msgBox;
    msgBox.setText("App Exited!");
    msgBox.exec();
    // exit the program
    exit(0);
}

void LogIn::on_userName_textChanged()
{
    username=ui->userName->text();
    qDebug()<<"text edited:"<<username;

}

void LogIn::on_userPassword_textChanged()
{
    password=ui->userPassword->text();
    qDebug()<<"password edited:"<<password;
}

void LogIn::on_userPassword_textChanged(QString const& arg)
{

}

void LogIn::on_logIn_clicked()
{
    qDebug()<<"start login";

    // verify if username exist
    qDebug()<<"finding username...";
    bool username_exist=findUsername(username);
    if(username_exist)
    {
        // find success
        qDebug()<<"verifying password...";
        if(verifyPassword(username,password))
        {
            // password correct
            qDebug()<<"password correct";
            QMessageBox msg;
            msg.setText("Login successfuly!");
            msg.exec();
        }
        else
        {
            // password error
            qDebug()<<"password error";
            QMessageBox msg;
            msg.setText("Password is wrong!");
            msg.exec();
        }
    }
    else
    {
        // username doesn't exist
        qDebug()<<"cann't find username";
        QMessageBox msg;
        msg.setText("User doesn't exist!\nPlease register first.");
        msg.exec();
    }
}

void LogIn::on_userRegister_clicked()
{
    qDebug()<<"start resgister";
    Register *res_ui=new Register;
    res_ui->exec();
}

void LogIn::on_forgotPassword_clicked()
{
    qDebug()<<"forgot password";
    QMessageBox msgBox;
    msgBox.setText("Developing...Couldn't use the function now.");
    msgBox.exec();
}
