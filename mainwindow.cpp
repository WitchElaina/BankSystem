#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "account.h"

#include <QFile>
#include <QDebug>


#include <vector>
#include <algorithm>
#include <fstream>
using namespace std;

//struct deleter {
//    template <class T> void operator () (T* p) {
//        delete p;
//    }
//};



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

    // Open userdata file

    // Run Init commandline

    Date date(2008, 11, 1);//起始日期
    vector<Account *> accounts;//创建账户数组，元素个数为0
    //Account *accounts[2];


    char cmd;
    fstream usr_cmd;
    bool rec;

    usr_cmd.open(m_login_dialog->username.toStdString()+".txt", ios::in);
    if(!usr_cmd)
    {
       qDebug()<<"Error! No command history!";
       usr_cmd.close();
       rec=false;
    }
    else
    {
       qDebug()<<"Recovering commands history...";
       usr_cmd.close();
       rec=true;
       usr_cmd.open(m_login_dialog->username.toStdString()+".txt", ios::in);

    }

    // Recovery
    while (rec)
    {
        char type;
        int index, day;
        double amount, credit, rate, fee;
        string id, desc;
        Account* account;

        Date date1, date2;

        if(!(usr_cmd>>cmd))
        {
           break;
        }

        switch (cmd) {
        case 'a'://增加账户
           usr_cmd >> type >> id;
           if (type == 's') {
               usr_cmd >> rate;
               account = new SavingsAccount(date, id, rate);

           }
           else {
               usr_cmd >> credit >> rate >> fee;
               account = new CreditAccount(date, id, credit, rate, fee);
           }
           accounts.push_back(account);
           break;

        case 'd'://存入现金
           usr_cmd >> index >> amount;
           getline(usr_cmd, desc);
           accounts[index]->deposit(date, amount, desc);
           break;

        case 'w'://取出现金
           usr_cmd >> index >> amount;
           getline(usr_cmd, desc);
           accounts[index]->withdraw(date, amount, desc);
           break;

        case 's'://查询各账户信息
           for (size_t i = 0; i < 2/*accounts.size()*/; i++) {
               cout << "[" << i << "] ";
               accounts[i]->show();
               cout << endl;
           }
           break;

        case 'c'://改变日期
           usr_cmd >> day;
           if (day < date.getDay())
               cout << "You cannot specify a previous day";

           else if (day > date.getMaxDay())
               cout << "Invalid day";

           else
               date = Date(date.getYear(), date.getMonth(), day);
           break;

        case 'n'://进入下个月
           if (date.getMonth() == 12)
               date = Date(date.getYear() + 1, 1, 1);
           else
               date = Date(date.getYear(), date.getMonth() + 1, 1);
           for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
               (*iter)->settle(date);
           break;

        case 'q'://查询一段时间内的账目
           date1 = Date::read();
           date2 = Date::read();
           Account::query(date1, date2);
           break;

        }
   }

    usr_cmd.close();


    // show info
//   QString info;
//    info.setNum(accounts[0]->getTotal());
//    ui->usr_balance->setText(info);



}




