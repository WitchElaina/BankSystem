#include "register.h"
#include "ui_register.h"

#include <QDebug>
#include <QFile>
#include <fstream>
#include <QMessageBox>
using namespace std;


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
    // check UserData file
    QFile usr_data_file("UserData.txt");
    usr_data_file.open(QIODevice::ReadWrite);
    usr_data_file.setTextModeEnabled(1);
    QTextStream usr_data_stream(&usr_data_file);

    QString finder;

    do
    {
        usr_data_stream>>finder;
        qDebug()<<"finding:"+finder;
        if(m_usrname==finder)
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
    }while(!finder.isNull());

    usr_data_file.close();
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
        usr_data_file.open(QIODevice::ReadWrite);
        QTextStream usr_data_stream(&usr_data_file);
        QString reader;
        do
        {
            usr_data_stream>>reader;
        }while(!reader.isNull());

        // create TXT temp
        usr_data_stream<<username;


        // copy the original data


        // insert new data


        // replace the original QHash data
        usr_data_file.close();



    }

}
