#include "querydialog.h"
#include "ui_querydialog.h"

QueryDialog::QueryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QueryDialog)
{
    ui->setupUi(this);

}

QueryDialog::~QueryDialog()
{
    delete ui;
}

void QueryDialog::setDefaultDateToSystemDate()
{
    ui->dateEdit->setDate(query_date);
}

void QueryDialog::on_buttonBox_accepted()
{
    query_date=ui->dateEdit->date();
}
