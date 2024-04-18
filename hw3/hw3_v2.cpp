#include <iostream>
#include <stdlib.h>
using namespace std;

class coins
{
    public:
        coins (char *str)
        {
            dollars_value = strtod(str, NULL);
        }
        void do_something()
        {
            display();
        }
        /*
        double r_value()
        {
            return dollars_value;
        }
        double r_q()
        {
            return q;
        }
        double r_d()
        {
            return d;
        }
        double r_n()
        {
            return n;
        }
        double r_p()
        {
            return p;
        }
        */

    private:
        double dollars_value; //string's converted value
        int q; //quarters
        int d; //dimes
        int n; //nickels
        int p; //pennies

        int compute()
        {
            double num = dollars_value;
            q = num / 0.25;
            num = num - q*0.25;
            d = num / 0.1;
            num = num - d*0.1;
            n = num / 0.05;
            num = num - n*0.05;
            p = num / 0.01;
        }

        void display()
        {
            cout << "$" << dollars_value << " = " << q << " quarters, "
            << d << " dimes, " << n << " nickels, " << p << " pennies" << endl;
        }
};

int main(int argc, char *argv[])
{
    for (int i = 1; i <= argc ; i++)
    {
        coins C(argv[i]);
        C.do_something();
    }

    return 0;
}