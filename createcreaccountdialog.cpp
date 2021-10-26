#include "createcreaccountdialog.h"
#include "ui_createcreaccountdialog.h"

CreateCreAccountDialog::CreateCreAccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateCreAccountDialog)
{
    ui->setupUi(this);
}

CreateCreAccountDialog::~CreateCreAccountDialog()
{
    delete ui;
}

bool CreateCreAccountDialog::verifyInput()
{
    if(account_name.contains(" "))
        // account name cannot contain space " "
        return false;

    if(rate<=0||rate>=1)
        // invalid rate
        return false;

    if(credit<=0)
        // invalid credit
        return false;

    if(annual_fee<=0)
        // invalid annual fee
        return false;

    return true;
}

void CreateCreAccountDialog::showUsername(QString m_username)
{
    ui->lineEdit_username->setText(m_username);
}

void CreateCreAccountDialog::on_lineEdit_account_name_textChanged(const QString &arg1)
{
    account_name=arg1;
    qDebug()<<"Account Name:"+account_name;
}

void CreateCreAccountDialog::on_lineEdit_credit_textChanged(const QString &arg1)
{
    credit=arg1.toDouble();
    qDebug()<<"Account Credit:"+arg1;
}

void CreateCreAccountDialog::on_lineEdit_rate_textChanged(const QString &arg1)
{
    rate=arg1.toDouble();
    qDebug()<<"Account Rate:"+arg1;
}

void CreateCreAccountDialog::on_lineEdit_annual_fee_textChanged(const QString &arg1)
{
    annual_fee=arg1.toDouble();
    qDebug()<<"Account Annual_fee:"+arg1;
}
