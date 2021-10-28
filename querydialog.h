#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H


#include <QDialog>
#include <QDate>

namespace Ui {
class QueryDialog;
}

class QueryDialog : public QDialog
{
    Q_OBJECT

public:
    explicit QueryDialog(QWidget *parent = nullptr);
    ~QueryDialog();

    QDate query_date;

    void setDefaultDateToSystemDate();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::QueryDialog *ui;
};

#endif // QUERYDIALOG_H
