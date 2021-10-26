#ifndef CREATESAVACCOUNTDIALOG_H
#define CREATESAVACCOUNTDIALOG_H

#include <QDialog>
#include <QDebug>

namespace Ui {
class CreateSavAccountDialog;
}

class CreateSavAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CreateSavAccountDialog(QWidget *parent = nullptr);
    ~CreateSavAccountDialog();
    QString username;
    QString account_name;
    double rate;

    // validat input
    bool verifyInput();

    // show username
    void showUsername(QString m_username);

private slots:
    void on_lineEdit_account_name_textChanged(const QString &arg1);

    void on_lineEdit_rate_windowIconTextChanged(const QString &iconText);

    void on_lineEdit_rate_textChanged(const QString &arg1);

private:
    Ui::CreateSavAccountDialog *ui;
};

#endif // CREATESAVACCOUNTDIALOG_H
