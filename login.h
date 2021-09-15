#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>

namespace Ui {
class LogIn;
}

class LogIn : public QWidget
{
    Q_OBJECT

public:
    explicit LogIn(QWidget *parent = nullptr);
    ~LogIn();

private:
    Ui::LogIn *ui;
};

#endif // LOGIN_H
