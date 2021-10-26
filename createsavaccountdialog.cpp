#include "createsavaccountdialog.h"
#include "ui_createsavaccountdialog.h"

CreateSavAccountDialog::CreateSavAccountDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CreateSavAccountDialog)
{
    ui->setupUi(this);
}

CreateSavAccountDialog::~CreateSavAccountDialog()
{
    delete ui;
}

bool CreateSavAccountDialog::verifyInput()
{
    if(account_name.contains(" "))
        // account name cannot contain space " "
        return false;

    if(rate<=0||rate>=1)
        // invalid rate
        return false;

    return true;
}

void CreateSavAccountDialog::on_lineEdit_account_name_textChanged(const QString &arg1)
{
    account_name=arg1;
    qDebug()<<"Account Name:"+account_name;
}

void CreateSavAccountDialog::on_lineEdit_rate_windowIconTextChanged(const QString &iconText)
{
    ;
}


void CreateSavAccountDialog::on_lineEdit_rate_textChanged(const QString &arg1)
{
    rate=arg1.toDouble();
    qDebug()<<"Account Rate:"+arg1;
}
