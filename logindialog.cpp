#include "logindialog.h"
#include "ui_logindialog.h"

#include <QObject>
#include <QMessageBox>
#include <QDataStream>
#include <QFile>
#include <QHash>
#include <iostream>
#include <QDebug>

#include "config.h"

LogInDialog::LogInDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LogInDialog)
{
    qDebug()<<COPYRIGHT_MESSAGE << GITHUB_REPO_URL;
    ui->setupUi(this);

}

LogInDialog::~LogInDialog()
{
    delete ui;
}

bool LogInDialog::findUsername(QString m_usrname)
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

bool LogInDialog::verifyPassword(QString m_usrname, QString m_password)
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

void LogInDialog::on_userName_textChanged(const QString &arg1)
{
    // username=ui->userName->text();
    username=arg1;
    qDebug()<<"text edited:"<<username;
}

void LogInDialog::on_userPassword_textChanged(const QString &arg1)
{
    // password=ui->userPassword->text();
    password=arg1;
    qDebug()<<"password edited:"<<password;
}



void LogInDialog::on_userRegister_clicked()
{
    qDebug()<<"start resgister";
    Register *res_ui=new Register;
    res_ui->exec();
}

void LogInDialog::on_buttonBox_accepted()
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

void LogInDialog::on_buttonBox_rejected()
{
    // Quit App
    qDebug()<<"Quit app";
    QMessageBox msg;
    msg.setText("Exited!");
    msg.exec();
    exit(0);
}
