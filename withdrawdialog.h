#ifndef WITHDRAWDIALOG_H
#define WITHDRAWDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include "date.h"
#include "config.h"



namespace Ui {
class WithdrawDialog;
}

class WithdrawDialog : public QDialog
{
    Q_OBJECT

public:
    double amount=0;
    int year=-1;
    int month=-1;
    int day=-1;
    string desc;

    explicit WithdrawDialog(QWidget *parent = nullptr);
    ~WithdrawDialog();



    //set Amount
    void setAmount();

    //set description
    void setDesc();

    // input verify
    bool verifyInput();

    // set Date
    void setDate(Date m_date);

private slots:

    void on_year_input_textChanged(const QString &arg1);

    void on_month_input_textChanged(const QString &arg1);

    void on_day_input_textChanged(const QString &arg1);

    void on_amount_input_textChanged(const QString &arg1);

    void on_desc_input_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::WithdrawDialog *ui;
};

#endif // WITHDRAWDIALOG_H
