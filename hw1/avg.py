#確認輸入的分數是否為整數(合法分數)
def check(grade):
    grade2 = int(grade)
    return (bool(grade - grade2 == 0))

#新建變數
number = 0
sum=0.0
#input grade
grade=input('Please input your score :\n')
grade=float(grade)
#判斷當次輸入之分數是否合法，合法則加進總和，不合法則中斷程式
while grade>=0:
    if ((check(grade) != True) or (grade>100)):
        break
    while (grade<=100 and check(grade)):
        sum = sum + grade
        number=number+1
        break
    grade = input('Please input your score :\n')
    grade = float(grade)
#分數不合法則印出illegal...，合法則印出平均值
if ((grade<0 and grade!=-1) or (check(grade) == False) or (grade>100)):
    print('illegal input, ending the program...')
else:
    average = sum/number
    print('Your average score is:{}'.format(average))
