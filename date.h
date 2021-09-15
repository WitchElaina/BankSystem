#ifndef date_h
#define date_h

#include <iostream>

using namespace std;

// 建表: 辅助计算相对日期, 表示平年每个月1号到1月1号的天数
const int DAYS_EACH_MONTH[]={0,31,59,90,120,151,181,212,243,273,304,334,365};

// 建表: 辅助判断有效日期, 表示平年每个月的最大天数
const int DAY_EACH_MONTH[]={31,28,31,30,31,30,31,31,30,31,30,31};

// 日期类
class Date
{
    int year;
    int month;
    int day;

public:
    // 构造函数
    Date(int m_year,int m_month,int m_day);
    Date();

    // 按格式 XXXX-XX-XX 打印日期
    void show();
    // 按 XXXX/XX/XX 格式读取日期
    static Date read();
    // 获取年
    int getYear()const;
    // 获取月
    int getMonth()const;
    // 获取日
    int getDay()const;
    // 闰年判断
    bool isLeap(int m_year)const;
    // 获取当月最大天数
    int getMaxDay()const;
    // 转化成相对日期
    int date_trans()const;
    // 计算与目标日期的天数差
    int distance(const Date& m_date)const;
    // 重载运算符 < 以实现日期的比较
    bool operator < (const Date& m_date)const;
};


#endif /* date.h */