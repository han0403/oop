import java.io.*;
import java.util.Scanner;

public class average
{
	public static int check(float a) //確認輸入的成績是否為整數(合法成績)
	{
		if (a-(int)a == 0)
			return 1;
		else
			return 0;
	}
	public static void main(String args[])
	{
		int number=0, sum=0; //成績數目及總和
		float grade, average; //當前輸入的成績及最後的平均
		Scanner key=new Scanner(System.in);
		
		System.out.println("Please input your score:\n");
		grade=key.nextInt();
		
		while (grade>=0) //判斷當次輸入之分數是否合法，合法則加進總和，不合法則中斷程式
		{
			if ((check(grade)==0) || grade>100)
			{
				break;
			}
			while (grade<=100 && check(grade)==1)
			{
				sum=sum+(int)grade;
				number++;
				break;
			}
			System.out.println("Please input your score:\n");
			grade=key.nextFloat();
		}
		
		if ((grade<0 && grade!=-1) || (check(grade)==0) || grade>100) //不合法輸入成績將印出illegal input...
		{
			System.out.println("illegal input, ending the program...");
		}
		else //合法成績將算出平均並印出
		{
			average=(float)sum/number;
			System.out.println("Your average score is:"+average);
		}
	}
}