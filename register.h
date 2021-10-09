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

    bool findUsername(QString m_usrname);

    bool spaceAndSignJudger(QString m_qstr);

private slots:
    void on_usrnameEdit_textChanged(const QString &arg1);

    void on_pwdEdit_textChanged(const QString &arg1);

    void on_buttonBox_accepted();

private:
    Ui::Register *ui;
};

#endif // REGISTER_H
