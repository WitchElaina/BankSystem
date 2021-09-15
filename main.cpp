#include "mainwindow.h"
#include "login.h"
#include "withdrawdialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    LogIn w1;
    w1.show();
    WithdrawDialog w2;
    w2.show();
    return a.exec();
}
