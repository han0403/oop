#include <iostream>
using namespace std;

bool integer(float a)    //function用來測試輸入的分數是否為整數
{
    if (a - (int)a == 0)
        return 0;
    else
        return 1;
}

main()
{
    int number = 0;       //number為合法分數個數，sum為合法分數總和
    int sum = 0;
    float grade;          //grade為當次輸入之分數，average為平均
    float average;

    cout << "Please input your score :\n";
    cin >> grade;

    while (grade>=0)     //判斷當次輸入之分數是否合法，若合法則加進總和
    {
        if ((integer(grade) == 1) || grade>100)
        {
            break;
        }
        while (grade <= 100 && integer(grade) == 0)
        {
            sum = sum + grade;
            number++;
            break;
        }
        cout << "Please input your score :\n";
        cin >> grade;
    }

    if ((grade < 0 && grade != -1) || integer(grade) == 1 || grade>100) //若輸入之分數為不合法，則中斷程式並印出illegal...
    {
        cout << "illegal input, ending the program...";
    }
    else
    {
        average = (float) sum / number;                //計算平均值並印出
        cout << "Your average score is : " << average;
    }

    return 0;
}
