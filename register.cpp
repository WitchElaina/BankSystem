#include "register.h"
#include "ui_register.h"

#include <QDebug>


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
}
