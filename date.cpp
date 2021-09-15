#include "date.h"

// 构造函数
Date::Date(int m_year,int m_month,int m_day)
{
    year=m_year;
    month=m_month;
    day=m_day;
}

Date::Date() {}

// 按格式 XXXX-XX-XX 打印日期
void Date::show()
{
    cout<<year<<"-"<<month<<"-"<<day;
}

// 按 XXXX/XX/XX 格式读取日期
Date Date::read()
{
    int r_year, r_month, r_day;
    scanf("%d/%d/%d", &r_year, &r_month, &r_day);
    Date r_date(r_year, r_month, r_day);
    return r_date;
}

// 获取年
int Date::getYear()const
{
    return year;
}

// 获取月
int Date::getMonth()const
{
    return month;
}

// 获取日
int Date::getDay()const
{
    return day;
}

// 闰年判断
bool Date::isLeap(int m_year)const
{
    // 如果不是整百年且年份能被4整除, 是闰年
    // 如果是整百年且是整400年, 是闰年
    if((m_year%100==0||m_year%400==0)&&(m_year%4==0||m_year%100!=0))
        return true;
    else
        return false;
}

// 获取当月最大天数
int Date::getMaxDay()const
{
    // 不是2月, 则平年闰年天数一致, 直接查表获得对打天数
    if(getMonth()!=2)
        return DAY_EACH_MONTH[getMonth()-1];

    // 是2月, 判断平年闰年
    else
    {
        if(isLeap(getYear()))
            // 闰年2月多一天
            return DAY_EACH_MONTH[getMonth()-1]+1;

        else
            return DAY_EACH_MONTH[getMonth()-1];
    }
}

// 转换成相对日期
//  利用相对日期, 先计算出两日期距1年1月1日的相对天数差, 再求出相差时间
int Date::date_trans()const
{
    
    int day_sum=0;
    for(int i=1;i<getYear();i++)
    {
        day_sum+=365;
        if(isLeap(i))
            day_sum++;
    }

    day_sum+=DAYS_EACH_MONTH[getMonth()-1];

    day_sum+=getDay();

    return day_sum;
}

// 计算与目标日期差
//  利用相对日期方便计算
int Date::distance(const Date& m_date)const
{
    return date_trans()-m_date.date_trans();
}

// 重载运算符 < 以实现日期的比较
bool Date::operator < (const Date& m_date)const
{
    // 日期差为负, 则所比较天数相对日期大于被比较天数, <成立, 取真
    if(distance(m_date)<0)
        return true;
    
    else
        return false;
}
