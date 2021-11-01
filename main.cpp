#include "mainwindow.h"
#include "logindialog.h"

QString SYS_DIR;



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QMessageBox msgBox1;
    msgBox1.setText("Please Select the dir of UserData.\n请选择保存用户数据的文件夹");
    msgBox1.exec();
    QDir a_dir(QFileDialog::getExistingDirectory());
    msgBox1.setText(a_dir.path()+" selected!");
    SYS_DIR=a_dir.path();
    qDebug()<<SYS_DIR;
    QDir::setCurrent(SYS_DIR);
    msgBox1.exec();

    LogInDialog w_login;
    while(!w_login.loginStatus)
        w_login.exec();

    MainWindow w;
    w.userInit(&w_login);
    w.show();



    return a.exec();
}
