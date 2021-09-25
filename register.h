#ifndef REGISTER_H
#define REGISTER_H

#include <QDialog>

namespace Ui {
class Register;
}

class Register : public QDialog
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();
    QString username;
    QString password;
    QHash<QString,QString> usr_hash;

private slots:
    void on_usrnameEdit_textChanged(const QString &arg1);

    void on_pwdEdit_textChanged(const QString &arg1);

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
