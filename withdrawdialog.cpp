#include "withdrawdialog.h"
#include "ui_withdrawdialog.h"
#include <QDate>



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

void WithdrawDialog::setDate(Date m_date)
{
    year=m_date.getYear();
    month=m_date.getMonth();
    day=m_date.getDay();
    QDate date_shown;
    m_date.setDate(date_shown);
    QString temp;
    temp.setNum(day);
    ui->day_input->setText(temp);
    temp.setNum(month);
    ui->month_input->setText(temp);
    temp.setNum(year);
    ui->year_input->setText(temp);

}

bool WithdrawDialog::verifyInput()
{
    Date* input_date=new Date(year,month,day);
    bool result=input_date->isValid();

    if(desc.empty())
        result=false;

    if(ui->amount_input->text().isNull())
        result=false;

    if(ui->amount_input->text().toDouble()==0)
        result=false;

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
