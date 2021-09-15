#ifndef account_h
#define account_h

#include<cmath>
#include "date.h"
#include <algorithm>
#include <vector>
#include <map>


// 累加器类
class Accumulator
{
    // 上次操作日期
    Date lastDate;
    // 操作数额
    double value;
    // 和
    double sum;

public:
    // 累加器构造函数
    Accumulator(Date m_lastDate, double m_value);
    Accumulator();
    // 求和
    double getSum(Date m_date);
    // 数值刷新函数
    void change(Date m_lastDate, double m_value);
    // 数值重置函数
    void reset(Date m_lastDate, double m_value);

};


// 账目记录类
class AccountRecord
{
    // 日期
    Date date;
    // 账户
    string* id;
    // 交易数额
    double amount;
    // 账户余额
    double balance;
    // 详细信息
    string desc;

public:
    // 构造函数
    AccountRecord(Date m_date, string* m_id, double m_amount, double m_balance, string m_desc);
    AccountRecord();
    void show();
};

// 用户类基类
class Account
{
    // 用户ID
    string id;
    // 用户余额
    double balance;
    // 系统总存款
    static double total;
    // 账目记录
    static multimap<Date, AccountRecord>recordMap;

    
public:
    // 构造函数
    Account(Date m_date,string m_id);

    //
    virtual ~Account();

    // 账户变动记录辅助函数
    void record(Date m_date, double m_amount,string m_desc);
    // 获取用户ID
    string getID();
    // 获取用户余额
    double getBalance();
    // 获取系统总存款
    static double getTotal();
    // 打印用户信息函数
    virtual void show()=0;
    // 存款函数
    virtual void deposit(Date m_date, double m_amount, string m_desc )=0;
    // 取款函数
    virtual void withdraw(Date m_date, double m_amount, string m_desc )=0;
    // 结算利息函数
    virtual void settle(Date date)=0;
    // 历史流水查询
    static void query(Date begin_date, Date end_date);
    
};


// 储蓄卡类
class SavingsAccount:virtual public Account
{
    // 累加器
    Accumulator acc;
    // 利率
    double rate;

public:
    // 储蓄卡类构造函数
    SavingsAccount(Date m_date, string m_id, double m_rate);
    // 获取利率
    double getRate();
    // 存款函数
    void deposit(Date m_date, double m_amount,string m_detail);
    // 取款函数
    void withdraw(Date m_date,double m_amount,string m_detail);
    // 结算利息函数
    void settle(Date m_date);
    // 打印账户信息
    void show();

};


// 信用卡类
class CreditAccount:virtual public Account
{
    // 累加器
    Accumulator acc;
    // 信用额度
    double credit;
    // 利息
    double rate;
    // 年费
    double fee;
    Date a_date;


public:
    // 信用卡类构造函数
    CreditAccount(Date m_date, string m_id, double m_credit, double m_rate, double m_fee);
    // 获取信用额度
    double getCredit();
    // 获取利息
    double getRate();  
    // 获取年费
    double getFee();
    // 获取可用额度
    double getAvailableCredit();
    // 还款函数
    void deposit(Date m_date, double m_amount,string m_detail);
    // 支付函数
    void withdraw(Date m_date,double m_amount,string m_detail);
    // 结算利息函数
    void settle(Date m_date);
    // 打印账户信息
    void show();
};


#endif /* account_h */
