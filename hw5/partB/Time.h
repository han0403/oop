#include <iostream>
#include <iomanip>
using namespace std;

class Time
{
    private:
        int days;
        int hours;
        int minutes;
        int seconds;
    public:
        Time();
        Time(int num);
        Time(int num, int num2, int num3, int num4);
        friend ostream& operator <<(ostream& os, const Time& t);
        friend istream& operator >>(istream& is, Time& t);
        friend Time operator +(const Time& t, const Time& p);
        friend Time operator -(const Time& t, const Time& p);
        friend bool operator <(const Time& t, const Time& p);
        friend bool operator >(const Time& t, const Time& p);
        friend bool operator <=(const Time& t, const Time& p);
        friend bool operator >=(const Time& t, const Time& p);
        friend bool operator ==(const Time& t, const Time& p);
        friend bool operator !=(const Time& t, const Time& p);
};
//預設建構函數，宣告即初始為00~00:00:00
Time::Time() 
{
    days = 0;
    hours = 0;
    minutes = 0;
    seconds = 0;
}
//傳入一個參數則將之視為秒數，若為負數則存為預設值(即為0)，否則計算成simplified form
Time::Time(int num)
{
    if (num < 0)
    {
        days = 0;
        hours = 0;
        minutes = 0;
        seconds = 0;
    }    
    else
    {
        seconds = num;
        days = num/86400;
        num = num - 86400*days;
        hours = num/3600;
        num = num - 3600*hours;
        minutes = num/60;
        seconds = num - 60*minutes;
    }
}
//傳入四個參數則將之視為秒數，分別視之為天數.小時數.分鐘數.秒數，若其中有一個以上(包含一個)為負數則存為預設值(即為0)，否則計算成simplified form
Time::Time(int num, int num2, int num3, int num4)
{
    if ((num < 0) || (num2 < 0) || (num3 < 0) || (num4 <0))
    {
        days = 0;
        hours = 0;
        minutes = 0;
        seconds = 0;
    }
    else
    {
        int carry = 0;
        seconds = num4%60;
        carry = num4/60;
        minutes = (num3 + carry)%60;
        carry = (num3 + carry)/60;
        hours = (num2 + carry)%24;
        carry = (num2 + carry)/24;
        days = num + carry;
    }
}
//overload operator <<，將Time object以days~hh:mm:ss型態印出
ostream& operator <<(ostream& os, const Time& t)
{
    os << setfill('0') << setw(2) << t.days << "~" << setfill('0') << setw(2) << t.hours << ":" << setfill('0') << setw(2) << t.minutes << ":" << setfill('0') << setw(2) << t.seconds;
    return os;
}
//overload operator >>，將Time object輸入並將資訊存入days.hours.minutes.seconds
istream& operator >>(istream& is, Time& t)
{
    is >> t.days;
    is.ignore();//跳過字元'~' 
    is >> t.hours;
    is.ignore(); //跳過字元':'
    is >> t.minutes;
    is.ignore();//跳過字元':'
    is >> t.seconds;
    if ((t.days < 0) || (t.hours < 0) || (t.minutes < 0) || (t.seconds < 0))
    {
        t.days = 0;
        t.hours = 0;
        t.minutes = 0;
        t.seconds = 0;
    }
    else
    {
        t.seconds = t.days*86400 + t.hours*3600 + t.minutes*60 + t.seconds;
        t.days = t.seconds/86400;
        t.seconds = t.seconds - 86400*t.days;
        t.hours = t.seconds/3600;
        t.seconds = t.seconds - 3600*t.hours;
        t.minutes = t.seconds/60;
        t.seconds = t.seconds - 60*t.minutes;
    }
    return is;
}
//t加p，並回傳simplified form
Time operator +(const Time& t, const Time& p)
{
    Time temp{};
    int carry = 0;
    temp.seconds = (t.seconds + p.seconds)%60;
    carry = (t.seconds + p.seconds)/60;
    temp.minutes = (t.minutes + p.minutes + carry)%60;
    carry = (t.minutes + p.minutes + carry)/60;
    temp.hours = (t.hours + p.hours + carry)%24;
    carry = (t.hours + p.hours + carry)/24;
    temp.days = t.days + p.days + carry;
    return temp;
}
//t減p
Time operator -(const Time& t, const Time& p)
{
    Time temp{};
    int carry = 0;
    int num = 0;
    int num2 = 0;
    num = t.days*86400 + t.hours*3600 + t.minutes*60 + t.seconds;
    num2 = p.days*86400 + p.hours*3600 + p.minutes*60 + p.seconds;
    if (num < num2)
    {
        temp.days = 0;
        temp.hours = 0;
        temp.minutes = 0;
        temp.seconds = 0;
    }
    else
    {
        carry = num - num2;
        temp.days = carry/86400;
        carry = carry - 86400*temp.days;
        temp.hours = carry/3600;
        carry = carry - 3600*temp.hours;
        temp.minutes = carry/60;
        temp.seconds = carry - 60*temp.minutes;
    }
    return temp;
}
//t是否小於p，小於則回傳true，否則false
bool operator <(const Time& t, const Time& p)
{
    int num = 0;
    int num2 = 0;
    num = t.days*86400 + t.hours*3600 + t.minutes*60 + t.seconds;
    num2 = p.days*86400 + p.hours*3600 + p.minutes*60 + p.seconds;
    if (num < num2)
        return true;
    else
        return false;
}
//t是否大於p，大於則回傳true，否則false
bool operator >(const Time& t, const Time& p)
{
    int num = 0;
    int num2 = 0;
    num = t.days*86400 + t.hours*3600 + t.minutes*60 + t.seconds;
    num2 = p.days*86400 + p.hours*3600 + p.minutes*60 + p.seconds;
    if (num > num2)
        return true;
    else
        return false;
}
//t是否小於等於p，小於等於則回傳true，否則false
bool operator <=(const Time& t, const Time& p)
{
    int num = 0;
    int num2 = 0;
    num = t.days*86400 + t.hours*3600 + t.minutes*60 + t.seconds;
    num2 = p.days*86400 + p.hours*3600 + p.minutes*60 + p.seconds;
    if (num <= num2)
        return true;
    else
        return false;
}
//t是否大於等於p，大於等於則回傳true，否則false
bool operator >=(const Time& t, const Time& p)
{
    int num = 0;
    int num2 = 0;
    num = t.days*86400 + t.hours*3600 + t.minutes*60 + t.seconds;
    num2 = p.days*86400 + p.hours*3600 + p.minutes*60 + p.seconds;
    if (num >= num2)
        return true;
    else
        return false;
}
//t是否等於p，等於則回傳true，否則false
bool operator ==(const Time& t, const Time& p)
{
    int num = 0;
    int num2 = 0;
    num = t.days*86400 + t.hours*3600 + t.minutes*60 + t.seconds;
    num2 = p.days*86400 + p.hours*3600 + p.minutes*60 + p.seconds;
    if (num == num2)
        return true;
    else
        return false;
}
//t是否不等於p，不等於則回傳true，否則false
bool operator !=(const Time& t, const Time& p)
{
    int num = 0;
    int num2 = 0;
    num = t.days*86400 + t.hours*3600 + t.minutes*60 + t.seconds;
    num2 = p.days*86400 + p.hours*3600 + p.minutes*60 + p.seconds;
    if (num != num2)
        return true;
    else
        return false;
}