#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace std;

struct deleter {
    template <class T> void operator () (T* p) {
        delete p;

    }
};


QString error_msg[]={
    "Error 0: 余额不足!",
    "Error 1: 取款数额小于0",
    "Error 2: 存款数额小于0",
    "Error 3: 还款数额小于0",
    "Error 4: 消费数额小于0",
    "Error 5: 额度不足"
};

Date date(2008, 11, 1);//起始日期
vector<Account *> accounts;//创建账户数组，元素个数为0
//Account* accounts[3];//创建账户数组，元素个数为0
Account* default_account=new SavingsAccount (date,"dafault_account",0);
CommandTranslator cmd_translator;
double total_income=0,total_expend=0,total_temp=0;
QDate qdate_temp;
// query text temp
multimap<Date,QString> date_append_temp;
multimap<double,QString> balance_append_temp;
//vector<QString> append_temp;



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

void MainWindow::showMessageBox(QString m_msg)
{
    QMessageBox msg;
    msg.setText(m_msg);
    msg.exec();
}

void MainWindow::flashuserData()
{
    // show info
    QString info;
    string* id_ptr;


    //SavingsAcc info
    if (accounts[DEFAULT_ACCOUNT_INDEX]->has_savings)
    {
        // user savings account balance
        info.setNum(accounts[SAVINGS_ACCOUNT_INDEX]->getBalance(),'f',2);
        ui->usr_sav_balance->setText(info);

        // user savings account rate
        info.setNum(accounts[SAVINGS_ACCOUNT_INDEX]->getRate()*100,'f',2);
        ui->usr_sav_rate->setText(info+"%");

        // user savings account current month income
        id_ptr=accounts[SAVINGS_ACCOUNT_INDEX]->getIDPtr();
        total_temp=accounts[SAVINGS_ACCOUNT_INDEX]->getCurMonthBillAmount(date,"deposite",id_ptr);
        info.setNum(total_temp,'f',2);
        ui->usr_sav_month_income->setText(info);
        total_income=total_temp;

        // user savings account current month expend
        total_temp=accounts[SAVINGS_ACCOUNT_INDEX]->getCurMonthBillAmount(date,"withdraw",id_ptr);
        info.setNum(total_temp,'f',2);
        ui->usr_sav_month_expend->setText(info);
        total_expend=total_temp;

        // reset total temp
        total_temp=0;
    }


    // CreditAcc info
    if(accounts[DEFAULT_ACCOUNT_INDEX]->has_credit)
    {
        // user credit account balance
        info.setNum(accounts[CREDIT_ACCOUNT_INDEX]->getBalance(),'f',2);
        ui->usr_cre_balance->setText(info);

        // user credit account credit
        info.setNum(accounts[CREDIT_ACCOUNT_INDEX]->getCredit(),'f',2);
        ui->usr_cre_credit->setText(info);

        // user credit account rate
        info.setNum(accounts[CREDIT_ACCOUNT_INDEX]->getRate()*100,'f',2);
        ui->usr_cre_rate->setText(info+"%");

        // user credit account current month income
        id_ptr=accounts[CREDIT_ACCOUNT_INDEX]->getIDPtr();
        total_temp=accounts[CREDIT_ACCOUNT_INDEX]->getCurMonthBillAmount(date,"deposite",id_ptr);
        info.setNum(total_temp,'f',2);
        ui->usr_cre_month_income->setText(info);
        total_income=total_temp;

        // user credit account current month expend
        total_temp=accounts[CREDIT_ACCOUNT_INDEX]->getCurMonthBillAmount(date,"withdraw",id_ptr);
        info.setNum(total_temp,'f',2);
        ui->usr_cre_month_expend->setText(info);
        total_expend=total_temp;

        // reset total temp
        total_temp=0;
    }



    // total info

    // total Balance
    info.setNum(accounts[SAVINGS_ACCOUNT_INDEX]->getTotal(),'f',2);
    ui->usr_balance->setText(info);

    // total month expend
    info.setNum(total_expend,'f',2);
    ui->month_expend->setText(info);

    // total month income
    info.setNum(total_income,'f',2);
    ui->month_income->setText(info);


}

void MainWindow::flashGUI()
{

    // Set PushButton Enabled
    if (accounts[DEFAULT_ACCOUNT_INDEX]->has_savings)
    {
        ui->pushButton_create_savings_acount->setEnabled(false);
        ui->pushButton_sav_deposite->setEnabled(true);
        ui->pushButton_sav_withdraw->setEnabled(true);
    }
    else
    {
        ui->pushButton_create_savings_acount->setEnabled(true);
        ui->pushButton_sav_deposite->setEnabled(false);
        ui->pushButton_sav_withdraw->setEnabled(false);
    }

    if(accounts[DEFAULT_ACCOUNT_INDEX]->has_credit)
    {
        ui->pushButton_create_credit_account->setEnabled(false);
        ui->pushButton_cre_deposite->setEnabled(true);
        ui->pushButton_cre_withdraw->setEnabled(true);
    }
    else
    {
        ui->pushButton_create_credit_account->setEnabled(true);
        ui->pushButton_cre_deposite->setEnabled(false);
        ui->pushButton_cre_withdraw->setEnabled(false);
    }

    date.setDate(qdate_temp);
    ui->dateEdit->setDate(qdate_temp);
}

//void MainWindow::queryResult(QDate query_date, QString query_account, QString query_sort_method)
//{

//}


void MainWindow::userInit(LogInDialog *m_login_dialog)
{
    ui->usr_name->setText( m_login_dialog->username );
//    accounts[DEFAULT_ACCOUNT_INDEX]=default_account;
    accounts.push_back(default_account);
//    accounts[CREDIT_ACCOUNT_INDEX]=default_account;
    accounts.push_back(default_account);
//    accounts[SAVINGS_ACCOUNT_INDEX]=default_account;
    accounts.push_back(default_account);


    // set Date
    QDate default_date;
    date.setDate(default_date);
    ui->dateEdit->setDate(default_date);


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

    try {
        while (rec)
        {
            char type;
            int index, day,year,month;
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
                   accounts[SAVINGS_ACCOUNT_INDEX]=account;
                   accounts[DEFAULT_ACCOUNT_INDEX]->has_savings=true;

               }
               else {
                   usr_cmd >> credit >> rate >> fee;
                   account = new CreditAccount(date, id, credit, rate, fee);
                   accounts[CREDIT_ACCOUNT_INDEX]=account;
                   accounts[DEFAULT_ACCOUNT_INDEX]->has_credit=true;
               }
               //accounts.push_back(account);
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
    //           Account::query(date1, date2);
               break;

            case 'j'://new cmd, jump to specific date
                usr_cmd >> year >> month >> day;
                if(year==date.getYear()&&month==date.getMonth())
                {
                    date.resetDate(QDate(year,month,day));
                    break;
                }
                for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)
                    (*iter)->settle(date);
                break;

            }
         }
    }
    catch(int i)
    {
        qDebug()<<error_msg[i];
    }



    usr_cmd.close();



    // load user data
    flashuserData();

    //Reflash GUI
    flashGUI();

    // show notification
    if(accounts[CREDIT_ACCOUNT_INDEX]->getBalance()<0)
        showMessageBox("信用卡需要还款, 请及时处理");

    //Release Mem
    // for_each(accounts.begin(), accounts.end(), deleter());

}







void MainWindow::on_pushButton_logout_clicked()
{
    showMessageBox("Exited!Bye~");
//    QMessageBox msg;
//    msg.setText("Exited!Bye~");
//    msg.exec();
    exit(0);

}

void MainWindow::on_pushButton_sav_deposite_clicked()
{
    WithdrawDialog *withdraw_window=new WithdrawDialog;
    withdraw_window->setDate(date);
    withdraw_window->setWindowTitle("储蓄卡存款");
    withdraw_window->exec();
    if(withdraw_window->verifyInput())
    {
        try {
            accounts[SAVINGS_ACCOUNT_INDEX]->deposit(Date(withdraw_window->year,withdraw_window->month,withdraw_window->day),withdraw_window->amount,withdraw_window->desc);
        } catch (int i) {
            qDebug()<<error_msg[i];
            showMessageBox(error_msg[i]);
            return ;
        }

        cmd_translator.depositeGUI(ui->usr_name->text().toStdString(),SAVINGS_ACCOUNT_INDEX,withdraw_window->amount,withdraw_window->desc);       
    }

    delete withdraw_window;
    flashuserData();
    flashGUI();
}

void MainWindow::on_pushButton_sav_withdraw_clicked()
{
    WithdrawDialog *withdraw_window=new WithdrawDialog;
    withdraw_window->setDate(date);
    withdraw_window->setWindowTitle("储蓄卡支出");
    withdraw_window->exec();
    if(withdraw_window->verifyInput())
    {
        try {
            accounts[SAVINGS_ACCOUNT_INDEX]->withdraw(Date(withdraw_window->year,withdraw_window->month,withdraw_window->day),withdraw_window->amount,withdraw_window->desc);
        } catch (int i) {
            qDebug()<<error_msg[i];
            showMessageBox(error_msg[i]);
            return ;
        }
        cmd_translator.withdrawGUI(ui->usr_name->text().toStdString(),SAVINGS_ACCOUNT_INDEX,withdraw_window->amount,withdraw_window->desc);
    }

    delete withdraw_window;
    flashuserData();
    flashGUI();
}

void MainWindow::on_pushButton_cre_deposite_clicked()
{
    WithdrawDialog *withdraw_window=new WithdrawDialog;
    withdraw_window->setDate(date);
    withdraw_window->setWindowTitle("信用卡还款");
    withdraw_window->exec();
    if(withdraw_window->verifyInput())
    {
        try {
            accounts[CREDIT_ACCOUNT_INDEX]->deposit(Date(withdraw_window->year,withdraw_window->month,withdraw_window->day),withdraw_window->amount,withdraw_window->desc);
        } catch (int i) {
            qDebug()<<error_msg[i];
            showMessageBox(error_msg[i]);
            return ;
        }
        cmd_translator.depositeGUI(ui->usr_name->text().toStdString(),CREDIT_ACCOUNT_INDEX,withdraw_window->amount,withdraw_window->desc);

    }
    delete withdraw_window;
    flashuserData();
    flashGUI();
}



void MainWindow::on_pushButton_cre_withdraw_clicked()
{
    WithdrawDialog *withdraw_window=new WithdrawDialog;
    withdraw_window->setDate(date);
    withdraw_window->setWindowTitle("信用卡消费");
    withdraw_window->exec();
    if(withdraw_window->verifyInput())
    {
        try {
           accounts[CREDIT_ACCOUNT_INDEX]->withdraw(Date(withdraw_window->year,withdraw_window->month,withdraw_window->day),withdraw_window->amount,withdraw_window->desc);
            } catch (int i) {
            qDebug()<<error_msg[i];
            showMessageBox(error_msg[i]);
            return ;
        }
        cmd_translator.withdrawGUI(ui->usr_name->text().toStdString(),CREDIT_ACCOUNT_INDEX,withdraw_window->amount,withdraw_window->desc);
    }
    delete withdraw_window;
    flashuserData();
    flashGUI();
}

void MainWindow::on_pushButton_create_credit_account_clicked()
{
    CreateCreAccountDialog *creat_window=new CreateCreAccountDialog;
    creat_window->showUsername(ui->usr_name->text());

    creat_window->exec();
    if(creat_window->verifyInput())
    {
        // trans GUI operation to command lines
        cmd_translator.createCreditAccountGUI(ui->usr_name->text().toStdString(),creat_window->account_name.toStdString(),creat_window->credit,creat_window->rate,creat_window->annual_fee);
        // create account
        Account* account = new CreditAccount(date, creat_window->account_name.toStdString(),creat_window->credit,creat_window->rate,creat_window->annual_fee);
        accounts[CREDIT_ACCOUNT_INDEX]=account;
        accounts[DEFAULT_ACCOUNT_INDEX]->has_credit=true;
    }
    delete creat_window;
    flashuserData();
    flashGUI();
}

void MainWindow::on_pushButton_create_savings_acount_clicked()
{
    CreateSavAccountDialog *creat_window=new CreateSavAccountDialog;
    creat_window->showUsername(ui->usr_name->text());

    creat_window->exec();
    if(creat_window->verifyInput())
    {
        // trans GUI operation to command lines
        cmd_translator.createSavingsAccountGUI(ui->usr_name->text().toStdString(),creat_window->account_name.toStdString(),creat_window->rate);

        // create account
        Account* account = new SavingsAccount(date, creat_window->account_name.toStdString(),creat_window->rate);
        accounts[SAVINGS_ACCOUNT_INDEX]=account;
        accounts[DEFAULT_ACCOUNT_INDEX]->has_savings=true;
    }
    delete creat_window;
    flashuserData();
    flashGUI();


}

void MainWindow::on_dateEdit_userDateChanged(const QDate &qdate)
{
    Date from_qdate;

    from_qdate.resetDate(qdate);

    if(from_qdate<=date)
    {
        QDate temp;
        // can't jump previous date
        date.setDate(temp);
        ui->dateEdit->setDate(temp);
        return ;
    }



    // settle
    if(!(from_qdate.getMonth()==date.getMonth()&&from_qdate.getYear()==date.getYear()))
    {
        try{
        if(accounts[DEFAULT_ACCOUNT_INDEX]->has_savings)
            accounts[SAVINGS_ACCOUNT_INDEX]->settle(from_qdate);

        if(accounts[DEFAULT_ACCOUNT_INDEX]->has_credit)
            accounts[CREDIT_ACCOUNT_INDEX]->settle(from_qdate);
        }
        catch(int i)
        {
            qDebug()<<error_msg[i];
        }

    }

    // set System Date
    date.resetDate(qdate);

    // trans GUI operation to command lines
    cmd_translator.dateChangeGUI(ui->usr_name->text().toStdString(),date.getYear(),date.getMonth(),date.getDay());

    flashuserData();
    flashGUI();

}

void MainWindow::on_pushButton_print_record_clicked()
{
    // 新建窗口让用户输入查询流水的年月
    QueryDialog *query_window=new QueryDialog;
    // 将窗口默认时间设置为当前的年月
    query_window->query_date.setDate(date.getYear(),date.getMonth(),1);
    query_window->setDefaultDateToSystemDate();
    query_window->exec();
    // 清楚先前文本处理流中的缓存信息
    ui->queryResult->clear();
    // 打印标头
    ui->queryResult->append("Date\tAmount\tBalance\tDescripiton");
    // 清除按日期排序multimap中缓存的内容
    date_append_temp.clear();
    // 清除按数额排序multimap中缓存的内容
    balance_append_temp.clear();
    qDebug()<<QString((ui->comboBox_select_rec_type->currentIndex()));

    if(ui->comboBox_select_rec_type->currentIndex()<=1)
    {
        accounts[ui->comboBox_select_rec_type->currentIndex()]->queryGUI(query_window->query_date,date_append_temp,balance_append_temp);
    }
    else
    { 
        accounts[SAVINGS_ACCOUNT_INDEX]->queryGUI(query_window->query_date,date_append_temp,balance_append_temp);
        accounts[CREDIT_ACCOUNT_INDEX]->queryGUI(query_window->query_date,date_append_temp,balance_append_temp);
    }

    // sort
    // 读取comboBox控件中用户选择的排序种类
    if(ui->comboBox->currentIndex()==0)
    {

        // sort by time时间排序
        multimap<Date,QString>::iterator it;
        for(it=date_append_temp.begin();it!=date_append_temp.end();it++)
            ui->queryResult->append(it->second);

    }
    else
    {
        // sort by amount数额排序
        multimap<double,QString>::iterator it;
        for(it=balance_append_temp.begin();it!=balance_append_temp.end();it++)
            ui->queryResult->append(it->second);
    }

}

void MainWindow::on_pushButton_change_password_pressed()
{
    ui->pushButton_change_password->setText(">_<Comming Soon>_<");
}

void MainWindow::on_pushButton_change_password_released()
{
    ui->pushButton_change_password->setText("修改密码");
}
