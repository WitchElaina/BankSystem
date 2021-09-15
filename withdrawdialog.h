#ifndef WITHDRAWDIALOG_H
#define WITHDRAWDIALOG_H

#include <QDialog>

namespace Ui {
class WithdrawDialog;
}

class WithdrawDialog : public QDialog
{
    Q_OBJECT

public:
    explicit WithdrawDialog(QWidget *parent = nullptr);
    ~WithdrawDialog();

private:
    Ui::WithdrawDialog *ui;
};

#endif // WITHDRAWDIALOG_H
