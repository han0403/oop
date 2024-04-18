#include <iostream>
#include <stdlib.h>
using namespace std;

class coins
{
    public:
        double number;
        double convert(char *str); //將輸入string轉換成double數值number

        int q; //quaters數量
        int d; //dimes數量
        int n; //nickles數量
        int p; //pennies數量

        int compute(double value); //將value轉換成q,d,n,p組合

};

double coins::convert(char *str)
{
    number = strtod(str, NULL);
    return number;
}

int coins::compute(double value)
{
    q = (int)(value/0.25);
    value = value - q*0.25;
    d = (int)(value/0.1);
    value = value - d*0.1;
    n = (int)(value/0.05);
    value = value - n*0.05;
    p = (int)(value/0.01);
    return q, d, n, p;
}

int main(int argc, char *argv[])
{
    coins C; //宣告一coins struct C
    for (int i = 1; i < argc ; i++)
    {
        C.convert(argv[i]); //將字串轉換成數值
        C.compute(C.number); // 將數值轉換成q,d,n,p
        //印出
        cout << "$" << argv[i] << " : " << C.q << " quarters, " << 
        C.d << " dimes, " << C.n << " nickels, " << C.p << " pennies" << endl;
    }

    return 0;
}