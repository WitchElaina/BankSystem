#include "account.h"
#include "config.h"
#include <qdebug.h>

// 初始化系统总金额
double Account::total=0;

// 初始化历史流水
//multimap<Date,AccountRecord> Account::recordMap;

// 保留两位小数
double set_precision_2(double original_num)
{
    bool lessThanZero=false;
    // floor函数向下取整
    if (original_num<0)
    {
        original_num=-original_num;
        lessThanZero=true;
    }
    
    original_num=floor(original_num * 100 + 0.5)/100;

    if(lessThanZero)
    {
        original_num=-original_num;
    }
    return original_num;
}

// 累加器方法
// 累加器构造函数
Accumulator::Accumulator(Date m_lastDate, double m_value)
{
    // 赋值
    lastDate=m_lastDate;
    value=0;
    // 默认和为0
    sum=0;
}
// 累加器默认构造函数
Accumulator::Accumulator()
{
    value=0;
    sum=0;
}

// 求和
double Accumulator::getSum(Date m_date)
{
    // 返回当期时间差
    sum+=m_date.distance(lastDate)*value;
    return sum;
}

// 数值改变函数
void Accumulator::change(Date m_lastDate, double m_value)
{
    getSum(m_lastDate);
    // 重新赋值
    lastDate=m_lastDate;
    value=m_value;
}

// 数值重设函数
void Accumulator::reset(Date m_lastDate, double m_value)
{
    sum=0;
    // 重设当前累加器数值
    change(m_lastDate, m_value);
}


// 账目记录类方法
// 构造函数
AccountRecord::AccountRecord(Date m_date, string* m_id, double m_amount, double m_balance, string m_desc)
{
    date=m_date;
    id=m_id;
    amount=m_amount;
    balance=m_balance;
    desc=m_desc;
}
AccountRecord::AccountRecord()
{

}

void AccountRecord::show()
{
    date.show();
    cout<<"\t"<<amount<<"\t"<<balance<<'\t'<<desc<<endl;
}

double AccountRecord::getAmount()
{
    return amount;
}

string* AccountRecord::getID()
{
    return id;
}

QString AccountRecord::getInfo()
{
    QString temp,ans;
    temp.setNum(date.getYear());
    ans=temp;
    temp.setNum(date.getMonth());
    ans+="/"+temp;
    temp.setNum(date.getDay());
    ans+="/"+temp;
    temp.setNum(amount);
    ans+="\t"+temp;
    temp.setNum(balance);
    ans+="\t"+temp;
    temp=temp.fromStdString(desc);
    qDebug()<<temp;
    ans+="\t"+temp;

    return ans;

}

// 账户基类方法
// 构造函数
Account::Account(Date m_date,string m_id)
{
    // 赋值
    id=m_id;

    // 余额默认为0
    balance=0;

    // 打印创建成功信息
    m_date.show();
    cout<<"\t#"<<id+" created"<<endl;


}

Account::~Account() {}

// 账户变动记录辅助函数
void Account::record(Date m_date, double m_amount,string m_desc)
{
    // 变动记录入余额
    balance+=m_amount;
    total+=m_amount;

    // 打印流水信息
    m_date.show();
    cout<<"\t#"<<id<<"\t"<<m_amount<<"\t"<<balance<<"\t"+m_desc<<endl;  

    // 记录流水信息
    AccountRecord m_account_record(m_date, &id, m_amount, getBalance(), m_desc);


    recordMap.insert(pair<Date, AccountRecord>(m_date, m_account_record));
}

// 获取用户ID
string Account::getID()
{
    return id;
}

string *Account::getIDPtr()
{
    return &id;
}
// 获取用户余额
double Account::getBalance()
{
    return balance;
}
// 获取系统总存款
double Account::getTotal()
{
    return total;
}
// 历史流水查询
void Account::query(Date begin_date, Date end_date)
{
    multimap<Date,AccountRecord>::iterator it;
    for(it=recordMap.begin();it!=recordMap.end();it++)
    {
        // check date
        if((it->first)<=(end_date)&&(begin_date)<=(it->first))
            it->second.show();
    }
}

void Account::queryGUI(QDate query_date, QString query_sort_method, QTextEdit* text)
{

    multimap<Date,AccountRecord>::iterator it;
    Date begin_date;
    begin_date.resetDate(query_date);
    Date end_date(begin_date.getYear(),begin_date.getMonth()+1,1);

    for(it=recordMap.begin();it!=recordMap.end();it++)
    {
        // check date
        if((it->first)<(end_date)&&(begin_date)<=(it->first))
            text->append(it->second.getInfo());
    }
}

// 储蓄卡类方法
// 储蓄卡类构造函数
SavingsAccount::SavingsAccount(Date m_date, string m_id, double m_rate): Account(m_date,m_id)
{
    // 赋值
    rate=m_rate;
    // 初始化累加器
    acc.reset(m_date,getBalance());

}

// 获取利率
double SavingsAccount::getRate()
{
    return rate;   
}

// 存款函数
void SavingsAccount::deposit(Date m_date, double m_amount,string m_desc)
{
    // 更新累加器
    //  核心: 此处更新累加器时, 所使用的value应该是存款之前的账户总额, 因此使用balance作为value, 取款函数同理
    acc.change(m_date, m_amount+getBalance());  
    
    // 存入余额并打印信息
    record(m_date, m_amount, m_desc);
}

// 取款函数
void SavingsAccount::withdraw(Date m_date,double m_amount,string m_desc)
{
    // 取款数字需要改变为负数完成运算
    m_amount=-m_amount;

    // 更新累加器
    acc.change(m_date, m_amount+getBalance());  
    
    // 存入余额并打印信息
    record(m_date, m_amount, m_desc);   
}

// 结算利息函数
void SavingsAccount::settle(Date m_date)
{
    // 不是新的一年则不计算年利息
    if(m_date.getMonth()!=1)
    {
        return ;
    }
    // 利息
    double interest;

    // 更新累加器
    acc.change(m_date, getBalance());

    // 计算总存款时间

    // 计算利息
    interest=set_precision_2(acc.getSum(m_date)/(SAVING_ACCOUNT_PERIOD+1)*rate);

    // 利息记入本金
    //  使用存款函数, 将利息存入本金
    deposit(m_date, interest, "interest");

}
// 打印账户信息
void SavingsAccount::show()
{
    cout<<getID()<<"\t"<<"Balance: "<<getBalance();
}

double SavingsAccount::getCredit()
{
    return 0;
}

// get current month bills
double SavingsAccount::getCurMonthBillAmount(Date m_date, string m_bill_kind, string* m_id)
{
    double total=0;
    multimap<Date,AccountRecord>::iterator it;
    for(it=recordMap.begin();it!=recordMap.end();it++)
    {
        // In the wrong month
        if(it->first.getYear()!=m_date.getYear() || it->first.getMonth()!=m_date.getMonth() || it->second.getID()!=m_id)
            continue;

        // Deposite mode
        if(m_bill_kind=="deposite")
        {
            if(it->second.getAmount()>0)
            {
                total+=it->second.getAmount();
            }
        }

        // Withdraw mode
        else if(m_bill_kind=="withdraw")
        {
            if(it->second.getAmount()<0)
            {
                total+=it->second.getAmount();
            }
        }

        // Invalid value of mod
        else
        {
            exit(5);
        }
    }

    //return amount of bill
    if(total>=0)
        return total;
    else
        return -total;
}

// 信用卡类方法
// 信用卡类构造函数
CreditAccount::CreditAccount(Date m_date, string m_id, double m_credit, double m_rate, double m_fee): Account(m_date, m_id)
{
    // 赋值
    credit=m_credit;
    rate=m_rate;
    fee=m_fee;
    a_date=m_date;
    // 初始化累加器
    acc.reset(m_date,getBalance());

}

// 获取信用额度
double CreditAccount::getCredit()
{
    return credit;
}

// 获取利息
double CreditAccount::getRate()
{
    return rate;   
}

// 获取年费
double CreditAccount::getFee()
{
    return fee;
}

// 获取可用额度
double CreditAccount::getAvailableCredit()
{
    return credit+getBalance();
}


// 还款函数
void CreditAccount::deposit(Date m_date, double m_amount,string m_desc)
{
    // 更新累加器
    //  核心: 此处更新累加器时, 所使用的value应该是存款之前的账户总额, 因此使用balance作为value, 消费函数同理
    acc.change(m_date, m_amount+getBalance());  
    
    // 记入账户并打印信息
    record(m_date, m_amount, m_desc);
}

// 消费函数
void CreditAccount::withdraw(Date m_date,double m_amount,string m_desc)
{
    // 消费数字需要改变为负数完成运算
    m_amount=-m_amount;

    // 减少每月额度
    credit+=m_amount;

    // 更新累加器
    acc.change(m_date, m_amount+getBalance());  
    
    // 记入账户并打印信息
    record(m_date, m_amount, m_desc);   

    if(m_desc=="interest")
    {
        // 结算利息
        acc.reset(m_date, getBalance());
        
        // 刷新每月额度
        credit=10000;
    }
}

// 结算函数
void CreditAccount::settle(Date m_date)
{
    // 利息
    double interest;

    // 年费
    bool annual_fee=false;

    // 更新累加器
    acc.change(m_date, getBalance());

    // 计算总存款时间

    // 计算利息
    interest=set_precision_2(acc.getSum(m_date)*rate);
    withdraw(m_date, -interest, "interest");
    
    // 判断是否需要交年费
    if(m_date.getYear()!=a_date.getYear())
    {
        annual_fee=true;
    }
    // 将利息与年费记入消费记录
    if(annual_fee)
        withdraw(m_date, CREDIT_ACCOUNT_ANNUAL_FEE, "annual fee");

    a_date=m_date;
    
}

// 打印账户信息
void CreditAccount::show()
{
    cout<<getID()<<"\t"<<"Balance: "<<getBalance()<<"\tAvailable credit:"<<getCredit();   
}

// get current month bills
double CreditAccount::getCurMonthBillAmount(Date m_date, string m_bill_kind, string* m_id)
{
    double total=0;
    multimap<Date,AccountRecord>::iterator it;
    for(it=recordMap.begin();it!=recordMap.end();it++)
    {
        // In the wrong month
        if(it->first.getYear()!=m_date.getYear() || it->first.getMonth()!=m_date.getMonth() || it->second.getID()!=m_id)
            continue;

        // Deposite mode
        if(m_bill_kind=="deposite")
        {
            if(it->second.getAmount()>0)
            {
                total+=it->second.getAmount();
            }
        }

        // Withdraw mode
        else if(m_bill_kind=="withdraw")
        {
            if(it->second.getAmount()<0)
            {
                total+=it->second.getAmount();
            }
        }

        // Invalid value of mod
        else
        {
            exit(5);
        }
    }

    //return amount of bill
    if(total>=0)
        return total;
    else
        return -total;
}

