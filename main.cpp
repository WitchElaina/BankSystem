#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    LogInDialog w_login;
    w_login.exec();

    MainWindow w;
    w.userInit(&w_login);
    w.show();



    return a.exec();
}
