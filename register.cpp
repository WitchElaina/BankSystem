#include "register.h"
#include "ui_register.h"

#include <QDebug>
#include <QFile>
#include <QMessageBox>


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
    // open user data file in readonly mode
    QFile usr_data("UserData.dat");
    bool isOpened;

    // check if the UserData file is opened correctly
    isOpened=usr_data.open(QIODevice::ReadWrite);
    if(!isOpened)
    {
        qDebug()<<"Error!Find file error01";
        throw "Error!Can't find UserData!";
    }

    qDebug()<<"file opened";
    QDataStream usr_data_stream(&usr_data);
    QHash<QString, QString> finder;
    usr_data_stream>>finder;
    usr_data.close();


    if(finder.find(m_usrname)!=finder.end()&&finder.end().key()!=m_usrname)
    {
        // find the input username successfully
        qDebug()<<"find the input username successfully";
        return true;
    }
    qDebug()<<"cannot find the input username";
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
    bool username_exist=0;//findUsername(username);

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
        QFile usr_data("UserData.dat");
        bool isOpened=usr_data.open(QIODevice::ReadWrite);
        if(!isOpened)
        {
            // check if the file opened
            qDebug()<<"Error!Find file error01";
            throw "Error!Can't find UserData!";
        }


        // create IO device
        QDataStream usr_data_stream(&usr_data);
        qDebug()<<"create IODevice";

        // create QHash temp
        QHash<QString, QString> temp;
        qDebug()<<"create Qhash";

        // copy the original data
        usr_data_stream>>temp;
        qDebug()<<"copy original data";

        // insert new data
        temp.insert(username,password);
        qDebug()<<"insert new data";

        // replace the original QHash data
        usr_data_stream<<temp;
        qDebug()<<"replace data";


        usr_data.close();
    }

}
