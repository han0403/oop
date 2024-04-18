#include <iostream>
#include<string>
#include<stack>
#include <queue>
#include <fstream>
#include <random>
#include <time.h>
#include <sstream>
using namespace std;
//若為個位數則直接回傳，否則將十位數與個位數相加再回傳
int getDigit(int number)
{
    if ((number/10) == 0)
        return number;
    else
        return ((number/10) + (number%10));
}
//依照ppt中step2內容，將偶數位數字各自乘以2後相加
int sumofDoubleEvenPlace(const string &cardNumber)
{
    //宣告
    stack<char> S;
    unsigned int sum = 0, num, i;
    //將string內容push進stack
    for (i = 0; i < cardNumber.size(); i++)
    {
        if ((cardNumber[i] != '\r') && (cardNumber[i] != '\n'))
            S.push(cardNumber[i]);
    }
    //計算偶數位之數字*2之和
    for (i = cardNumber.size()-2; i >= 0; i = i-2)
    {
        if (S.empty())
            break;
        else
        {
            S.pop();
            if (S.empty())
                break;
            else
            {
                num = getDigit(((int)S.top() - 48) * 2);
                sum = sum + num;
                S.pop();
            }
        }
    }
    //回傳
    return sum;
}
//依照ppt中step3內容，將奇數位數字各自相加
int sumOfOddPlace(const string &cardNumber)
{
    //宣告
    stack<char> S;
    unsigned int sum = 0, i;
    //將string內容push進stack
    for (i = 0; i < cardNumber.size(); i++)
    {
        if ((cardNumber[i] != '\r') && (cardNumber[i] != '\n'))
            S.push(cardNumber[i]);
    }
    //將奇數位數字相加
    for (i = cardNumber.size()-1; i >= 0; i = i-2)
    {
        if (S.empty())
            break;
        else
        {
            sum = sum + ((int)S.top() - 48);
            S.pop();
            if (S.empty())
                break;
            else
                S.pop();
        }
    }
    //回傳
    return sum;
}
//判斷是否為合法信用卡號(若step2跟step3內容相加後除以10，可整除則為合法卡號回傳true，其餘為不合法回傳false)
bool isvalid(const string &cardNumber)
{
    //宣告
    unsigned int i;
    //將step2和step3內容相加
    int num = sumofDoubleEvenPlace(cardNumber) + sumOfOddPlace(cardNumber);
    //計算信用卡號有幾碼
    int sum = 0;
    for (i = 0; i < cardNumber.size(); i++)
    {
        if ((cardNumber[i] != '\r') && (cardNumber[i] != '\n'))
            sum = sum + 1;
    }
    //step2和step3內容相加後除以10，若能整除且信用卡號介於13~16碼間則回傳true，否則回傳false
    if (((num%10) == 0) && (sum >= 13) && (sum <= 16))
        return true;
    else
        return false;
}
//確認為哪種信用卡，回傳信用卡號判斷碼
int startsWith(const string &cardNumber)
{
    queue<char> Q;
    unsigned int i;
    for (i = 0; i < cardNumber.size(); i++)
        Q.push(cardNumber[i]);
    if ((Q.front() == '4') || (Q.front() == '5') || (Q.front() == '6'))
        return ((int)Q.front() - 48);
    else if (Q.front() == '3')
    {
        Q.pop();
        if (Q.front() == '7')
            return 37;
    }
    else
        return 0;
}
//製造信用卡號
string fakeOne(const string &brand)
{
    unsigned int i;
    char tmp;
    string str;
    for (i = 0; i < 16; i++)
    {
        tmp = rand() % ('9' - '0' + 1) + '0';
        if (i == 0)
        {
            if ((brand.compare("004") == 0) || (brand.compare("004\r") == 0))
                tmp = '4';
            if ((brand.compare("005") == 0) || (brand.compare("005\r") == 0))
                tmp = '5';
            if ((brand.compare("006") == 0) || (brand.compare("006\r") == 0))
                tmp = '6';
            if ((brand.compare("0037") == 0) || (brand.compare("0037\r") == 0))
                tmp = '3';
        }
        if (((i == 1) && (brand.compare("0037") == 0)) || ((i == 1) && (brand.compare("0037\r") == 0)))
        {
            tmp = '7';
        }
        str += tmp;
    }
    return str;
}

int main()
{
    //宣告
    string line;
    struct timespec start, ending;
    double run_time;
    //傳入測資
    ifstream myfile;
    myfile.open("input.txt");
    //以行為單位讀取
    while (getline(myfile, line))
    {
        string ans, cardnum;
        //若此行不為004,005,006及0037，則開始判斷此信用卡號是否合法
        if ((line.compare("004") != 0) && (line.compare("005") != 0) && (line.compare("006") != 0) && (line.compare("0037") != 0)
            && (line.compare("004\r") != 0) && (line.compare("005\r") != 0) && (line.compare("006\r") != 0) && (line.compare("0037\r") != 0))
        {
            //判斷屬於何種信用卡，以及若回傳值非四種信用卡號之開頭，則輸出字串為an invalid card number
            int num = startsWith(line);
            if (num == 4)
                ans = "Visa card";
            else if (num == 5)
                ans = "MasterCard card";
            else if (num == 6)
                ans = "Discover card";
            else if (num == 37)
                ans = "American Express card";
            else
                ans = "card number";
            //判斷是否合法並輸出結果
            if (isvalid(line) != 0)
            {
                cout << line << endl;
                cout << ": a valid " << ans << endl;
            }
            else
            {
                cout << line << endl;
                cout << ": an invalid " << ans << endl;
            }
        }
        else
        {
            //若此行為004,005,006,0037，則輸出對應的一串合法信用卡號
            while (isvalid(cardnum) == 0)
            {
                //計時開始
                clock_gettime(CLOCK_MONOTONIC, &start);
                cardnum = fakeOne(line);
            }
            //計時結束
            clock_gettime(CLOCK_MONOTONIC, &ending);
            //計算時間差並轉換成微秒
            run_time = (double)(ending.tv_nsec - start.tv_nsec)/1000;

            if ((line.compare("004") == 0) || (line.compare("004\r") == 0))
                ans = "Visa card";
            if ((line.compare("005") == 0) || (line.compare("005\r") == 0))
                ans = "MasterCard card";
            if ((line.compare("006") == 0) || (line.compare("006\r") == 0))
                ans = "Discover card";
            if ((line.compare("0037") == 0) || (line.compare("0037\r") == 0))
                ans = "American Express card";
            cout << "Generated a valid " << ans << " : " << cardnum << "; ";
            cout << "Timing: " << run_time << " microseconds\n";
        }
        string line;
    }
    //關閉測試檔
    myfile.close();
    return 0;
}
