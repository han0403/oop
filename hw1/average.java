import java.io.*;
import java.util.Scanner;

public class average
{
	public static int check(float a) //�T�{��J�����Z�O�_�����(�X�k���Z)
	{
		if (a-(int)a == 0)
			return 1;
		else
			return 0;
	}
	public static void main(String args[])
	{
		int number=0, sum=0; //���Z�ƥؤ��`�M
		float grade, average; //��e��J�����Z�γ̫᪺����
		Scanner key=new Scanner(System.in);
		
		System.out.println("Please input your score:\n");
		grade=key.nextInt();
		
		while (grade>=0) //�P�_����J�����ƬO�_�X�k�A�X�k�h�[�i�`�M�A���X�k�h���_�{��
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
		
		if ((grade<0 && grade!=-1) || (check(grade)==0) || grade>100) //���X�k��J���Z�N�L�Xillegal input...
		{
			System.out.println("illegal input, ending the program...");
		}
		else //�X�k���Z�N��X�����æL�X
		{
			average=(float)sum/number;
			System.out.println("Your average score is:"+average);
		}
	}
}