#include <iostream>
using namespace std;

class Cube
{
    private :
        double x, y, z;
    public:
        bool operator !=(const Cube& right);
        friend double operator /(const Cube& first, const Cube& second);
};
//member function overload operator !=，如果他們不相等則傳回true，否則傳回false
bool Cube::operator !=(const Cube& right)
{
    int product, product2;
    product = (*this).x * (*this).y * (*this).z;
    product2 = right.x*right.y*right.z;
    if (product != product2)
        return true;
    else
        return false;
}
//non-member function overload operator /，傳回物件A之xyz總和除以物件B之xyz總和之值
double operator /(const Cube& first, const Cube& second)
{
    double temp, sum, sum2;
    sum = first.x + first.y + first.z;
    sum2 = second.x + second.y + second.z;
    temp = sum/sum2;
    return temp;
}