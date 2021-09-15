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
