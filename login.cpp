#include "login.h"
#include "ui_login.h"

#include <QObject>
#include <QMessageBox>
#include <QDataStream>
#include <QFile>
#include <QHash>
#include <iostream>
#include <QDebug>

#include "config.h"

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

    // check UserData file
    QFile usr_data_file(USER_DATA_FILE);
    if(usr_data_file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"Opened!";
    }
    usr_data_file.setTextModeEnabled(1);
    QTextStream usr_data_stream(&usr_data_file);

    QString finder;

    while(usr_data_stream.readLineInto(&finder))
    {

        usr_data_stream>>finder;
        qDebug()<<"finding:"+finder;

        if(finder.contains("username:"+m_usrname+",password:"))
        {
            // find success
            qDebug()<<"find success";
            return true;
        }
        else
        {
            // cannot find
            qDebug()<<"cannot find";
        }
    };

    usr_data_file.close();
    return false;
}

bool LogIn::verifyPassword(QString m_usrname, QString m_password)
{
    // open user data file in readonly mode

    QFile usr_data(USER_DATA_FILE);
    usr_data.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream usr_data_stream(&usr_data);
    // verify the Password
    QString finder;
    while(usr_data_stream.readLineInto(&finder))
    {
        qDebug()<<"finding...current line:"+finder;
        if(finder.contains("username:"+m_usrname+",password:"))
        {
            qDebug()<<"find username success!";
            qDebug()<<"validating password...";
            if(finder.contains(",password:"+m_password+";"))
            {
                // Password correct
                qDebug()<<"Password correct";
                return true;
            }
            else
            {
                // Password error
                qDebug()<<"Password error";
                return false;
            }
        }
        else
        {
            qDebug()<<"cannot find username!";
        }
    }
    return false;
}

void LogIn::userLogin(QString m_usrname, QString m_password)
{
//    try {
//        if(findUsername(m_usrname)) {
//            if(verifyPassword(m_usrname,m_password)) {
//                // login successfully
//            }
//            else {
//                // password is incorrect
//                throw false;
//            }
//        }

//    }
//    catch (QString msg) {
//        // can't find Data file
//    }
//    catch (bool) {
//        // password is incorrect
//    }

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
            QMessageBox msg;
            msg.setText("Login successfuly!");
            msg.exec();
            loginStatus=true;
            close();

        }
        else
        {
            // password error           
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


void LogIn::loginExec()
{
    ;
}
