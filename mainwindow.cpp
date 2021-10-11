#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "account.h"

#include <QFile>
#include <QDebug>
#include <QDomDocument>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::userInit(LogInDialog *m_login_dialog)
{
    ui->usr_name->setText( m_login_dialog->username );


}




