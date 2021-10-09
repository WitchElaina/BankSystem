#include "register.h"
#include "ui_register.h"

#include <QDebug>
#include <QFile>
#include <fstream>
#include <QMessageBox>
#include <QFileDialog>
#include "config.h"
using namespace std;

const QString invalid_chars[9]={" ","\\","/","[","]",",",":","username","password"};


Register::Register(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Register)
{
    ui->setupUi(this);
}

Register::~Register()
{
    delete ui;
}

bool Register::findUsername(QString m_usrname)
{
    // QString filename=QFileDialog::getOpenFileName(this,tr("Select UserData File"));
    // check UserData file
    QFile usr_data_file("UserData.txt");
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

        if(finder.contains("username:"+username+",password:"))
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

bool Register::spaceAndSignJudger(QString m_qstr)
{
    // Judge if a QString null
    if(m_qstr.isNull())
    {
        return true;
    }

    // Judge if a QString has invaild chars, such as " ", "/", "\"...
    for(int i=0;i<INVALID_CHAR_NUM;i++)
    {
        if(m_qstr.contains(INVALID_CHAR[i]))
        {
            qDebug()<<m_qstr+"contains invalid char"+INVALID_CHAR[i];
            return true;
        }
    }
    return false;
}

void Register::on_usrnameEdit_textChanged(const QString &arg1)
{
    username=arg1;
    qDebug()<<"input username:"<<username;
}

void Register::on_pwdEdit_textChanged(const QString &arg1)
{
    password=arg1;
    qDebug()<<"input password:"<<password;
}

void Register::on_buttonBox_accepted()
{
    // press the register button
    qDebug()<<"Submit the username and password\nUsername: "<<username<<"\nPassword: "<<password;

    // Judge if the username valid
    qDebug()<<"Judging if the username valid...";
    if(spaceAndSignJudger(username))
    {
        qDebug()<<"username invalid!";
        QMessageBox msgBox;
        msgBox.setText("用户名包含非法字符!");
        msgBox.exec();

    }

    // Judge if the password valid
    if(spaceAndSignJudger(password))
    {
        qDebug()<<"password invalid!";
        QMessageBox msgBox;
        msgBox.setText("密码包含非法字符!");
        msgBox.exec();

    }





    // Judge if the input username already exist
    bool username_exist=findUsername(username);

    if(username_exist)
    {
        qDebug()<<"the input username already exist";

        QMessageBox msgBox;
        msgBox.setText("用户名已存在!无法完成注册");
        msgBox.exec();
    }

    else
    {
        qDebug()<<"Creating new account...";

        // open the userdata file
        QFile usr_data_file("UserData.txt");



        // create IO device
        usr_data_file.open(QIODevice::ReadWrite | QIODevice::Append);
        QTextStream usr_data_stream(&usr_data_file);

        usr_data_stream<<"\nusername:"+username+",password:"+password;






        // replace the original QHash data
        usr_data_file.close();



    }

}
