#ifndef CREATECREACCOUNTDIALOG_H
#define CREATECREACCOUNTDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class CreateCreAccountDialog;
}

class CreateCreAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateCreAccountDialog(QWidget *parent = nullptr);
    ~CreateCreAccountDialog();
    QString username;
    QString account_name;
    double rate;
    double annual_fee;
    double credit;

    // validat input
    bool verifyInput();

    // show username
    void showUsername(QString m_username);

private slots:
    void on_lineEdit_account_name_textChanged(const QString &arg1);

    void on_lineEdit_credit_textChanged(const QString &arg1);

    void on_lineEdit_rate_textChanged(const QString &arg1);

    void on_lineEdit_annual_fee_textChanged(const QString &arg1);

private:
    Ui::CreateCreAccountDialog *ui;
};

#endif // CREATECREACCOUNTDIALOG_H
