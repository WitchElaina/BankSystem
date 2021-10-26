#include "withdrawdialog.h"
#include "ui_withdrawdialog.h"


WithdrawDialog::WithdrawDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WithdrawDialog)
{
    ui->setupUi(this);
}

WithdrawDialog::~WithdrawDialog()
{
    delete ui;
}

bool WithdrawDialog::verifyInput()
{
    Date* input_date=new Date(year,month,day);
    bool result=input_date->isValid();
    delete input_date;

    if(result)
        return true;

    else
        return false;
}

void WithdrawDialog::on_year_input_textChanged(const QString &arg1)
{
    qDebug()<<"input:"+arg1;
    year=arg1.toInt();
//    qDebug()<<"now year is:";
}

void WithdrawDialog::on_month_input_textChanged(const QString &arg1)
{
    qDebug()<<"input:"+arg1;
    month=arg1.toInt();



//    qDebug()<<"now month is:";
}



void WithdrawDialog::on_day_input_textChanged(const QString &arg1)
{
    qDebug()<<"input:"+arg1;
    day=arg1.toInt();
//    qDebug()<<"now day is:";
}

void WithdrawDialog::on_amount_input_textChanged(const QString &arg1)
{
    qDebug()<<"input:"+arg1;
    amount=arg1.toDouble();
//    qDebug()<<"now amount is:";
}


void WithdrawDialog::on_desc_input_textChanged(const QString &arg1)
{
    qDebug()<<"input:"+arg1;
    desc=arg1.toStdString();
//    qDebug()<<"now amount is:";
}

void WithdrawDialog::on_buttonBox_accepted()
{
    // validat inputs
    if(!verifyInput())
    {
        QMessageBox msg;
        msg.setText("Invalid input!");
        msg.exec();
    }
}
