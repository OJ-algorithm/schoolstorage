#include<stdio.h>
#include<math.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
#include<stdlib.h>
#include<time.h>
#include<fstream>
#include<iomanip>
#include<iostream>
using namespace std;
void float1();//小数运算
void intadd();//整数加减运算
void intmul();//整数乘法运算
void intdiv();//整数除法运算
void fractionadd();//分数加减运算
void fractionmul();//分数乘除运算
int mainmenu();
int menu();
void mix();//混合运算，包含括号和基本运算符
int rightnum = 0;//每道题目分值一分，计算学生得分情况
int wrongnum = 0;
int score = 0;

//小数加减

void float1()
{
	int num, n = 0;					//输入计算范围和题目数量
	printf("选择加减运算的范围：\n");
	scanf_s("%d", &num);
	printf("生成题目数量：\n");
	scanf_s("%d", &n);
	std::ofstream ofile;
	ofile.open(".\\test-float.txt");
	for (int i = 0; i < n; i++)
	{
		int a, b, f1, f2;
		float c = 1.0, f3 = 0.1, f4 = 0.1;
		srand((int)time(0));
		a = -num + rand() % (2 * num + 1);//计算范围为-num到num
		srand(i);
		b = -(num)+rand() % (2 * num + 1);
		srand((int)time(0));
		f1 = 1 + rand() % 9;
		srand(i);
		f2 = 1 + rand() % 9;
		f3 = f3 * f1;
		f4 = f4 * f1;
		float num1, num2, num3 = 1.0;
		num1 = a * 1.0 + f3;
		num2 = b * 1.0 + f4;
		if (num1 >= 0.0 && num2 >= 0.0)
		{
			printf("请计算：\n\t\t %.1f + %.1f = ", num1, num2);
			ofile << num1 << "+" << num2 << "=" << num1 + num2 << endl;
		}
		if (num1 >= 0.0 && num2 < 0.0)
		{
			num3 = -num2;
			printf("请计算：\n\t\t %.1f - %.1f = ", num1, num3);
			ofile << num1 << "-" << num3 << "=" << num1 + num2 << endl;
		}
		if (num1 < 0.0 && num2 >= 0.0)
		{
			printf("请计算：\n\t\t %.1f + %.1f = ", num1, num2);
			ofile << num1 << "+" << num2 << "=" << num1 + num2 << endl;
		}
		if (num1 < 0.0 && num2 < 0.0)
		{
			num3 = -num2;
			printf("请计算：\n\t\t %.1f -%.1f = ", num1, num3);
			ofile << num1 << "-" << num3 << "=" << num1 + num2 << endl;
		}
		cin >> c;
		float d = (num1 + num2) * 1.0;
		if (d == c)
		{
			printf("回答正确!\n");
			rightnum++;
		}
		else
		{
			printf("回答错误!\n");
			cout << "前往文件查看正确答案" << endl;
			wrongnum++;
		}
	}
	ofile.close();
}
int gcd(int m, int n) //辗转相除法求最大公约数
{
	if (n == 0) //没有空格
		return m;
	else
		return gcd(n, m % n);
}
//整数加法
void intadd()
{
	int num, n = 0;					//输入计算范围和题目数量
	printf("选择加减运算的范围：\n");
	scanf_s("%d", &num);
	printf("生成题目数量：\n");
	scanf_s("%d", &n);
	std::ofstream ofile;
	ofile.open(".\\test-intadd.txt");
	for (int i = 0; i < n; i++)
	{
		int a, b, c, d, e;
		srand((int)time(0));
		a = -num + rand() % (2 * num + 1);//计算范围为-num到num
		srand(i);
		b = -(num)+rand() % (2 * num + 1);
		if (a >= 0 && b >= 0)
			printf("请计算：\n\t\t %d + %d = ", a, b);
		if (a >= 0 && b < 0)
		{
			e = -b;
			printf("请计算：\n\t\t %d - %d = ", a, e);
		}
		if (a < 0 && b >= 0)
			printf("请计算：\n\t\t %d + %d = ", a, b);
		if (a < 0 && b < 0)
		{
			e = -b;
			printf("请计算：\n\t\t %d - %d = ", a, e);
		}
		d = a + b;
		ofile << a << '+' << b << '=' << d << endl;
		scanf_s("%d", &c);
		if (a + b == c)
		{
			printf("回答正确!\n");
			rightnum++;
		}
		else
		{
			printf("回答错误!\n");
			cout << "前往文件查看正确答案" << endl;
			wrongnum++;
		}
	}
	ofile.close();
}
//整数乘法
void intmul()
{
	int num, n = 0;					//输入计算范围和题目数量
	printf("选择乘除运算的范围：\n");
	scanf_s("%d", &num);
	printf("生成题目数量：\n");
	scanf_s("%d", &n);
	std::ofstream ofile;
	ofile.open(".\\test-intmul.txt");
	for (int i = 0; i < n; i++)
	{
		int a, b, c, d;
		srand((int)time(0));
		a = -num + rand() % (2 * num + 1);//计算范围为-num到num
		srand(i);
		b = 1 + rand() % (num - 1);
		printf("请计算：\n\t\t %d × %d = ", a, b);
		d = a * b;
		ofile << a << "×" << b << '=' << d << endl;
		scanf_s("%d", &c);
		if (c == d)
		{
			printf("回答正确!\n");
			rightnum++;
		}
		else
		{
			printf("回答错误!\n");
			cout << "前往文件查看正确答案" << endl;
			wrongnum++;
		}
	}
	ofile.close();
}
//整数除法
void intdiv()
{
	int num, n = 0;					//输入计算范围和题目数量
	printf("选择乘除运算的范围：\n");
	scanf_s("%d", &num);
	printf("生成题目数量：\n");
	scanf_s("%d", &n);
	std::ofstream ofile;
	ofile.open(".\\test-intdiv.txt");
	int a, b, d, m, p;
	for (int i = 0; i < n; i++)
	{
		srand((int)time(0));
		a = -num + rand() % (2 * num + 1);//计算范围为-num到num
		srand(i);
		b = 1 + rand() % (num - 1);
		m = a, p = b;
		gcd(m, p);
		a = a / gcd(m, p);
		b = b / gcd(m, p);
		if (a == 0 || b == 1 && a >= b)
		{
			printf("请计算：\n\t\t %d ÷ %d = ", m, p);
			cin >> d;
			ofile << a << "÷" << b << '=' << a << endl;
			if (d == a)
			{
				printf("回答正确!\n");
				rightnum++;
			}
			else
			{
				printf("回答错误!\n");
				cout << "前往文件查看正确答案" << endl;
				wrongnum++;
			}
		}
		else
		{
			n++;
			continue;
		}
	}
	ofile.close();
}

//分数运算

void fractionmul()
{
	int n, ran;
	cout << "输入分母大小范围:" << endl;
	cin >> ran;
	cout << "输入生成题目数量：" << endl;
	cin >> n;
	std::ofstream ofile;
	ofile.open(".\\test-fractionmul.txt");
	int a, b, d, e, f, g, m, p;
	for (int i = 0; i < n; i++)
	{
		f = 0, g = 0;
		int op;
		string s;
		int c;
		srand((int)time(0));
		a = 1 + rand() % ran;//计算范围为-num到num
		srand(i);
		b = 1 + rand() % ran;
		srand(i + 1);
		d = 1 + rand() % ran;
		srand(i + 2);
		e = 1 + rand() % ran;
		srand(i + 3);
		op = 1 + rand() % 2;
		switch (op)
		{

		case 1:
			f = a * d, g = b * e, g = b * e;
			m = f, p = g;
			f = f / gcd(m, p);
			g = g / gcd(m, p);
			int a1, b1, d1, e1;
			a1 = a, b1 = b;
			d1 = d, e1 = e;
			a = a / gcd(a1, b1);
			b = b / gcd(a1, b1);
			d = d / gcd(d1, e1);
			e = e / gcd(d1, e1);
			if (f == 0 || g == 1)
			{
				printf("请输入答案：\n\t\t %d/%d×%d/%d = ", a, b, d, e);
				ofile << a << '/' << b << "×" << d << '/' << e << '=' << f << endl;
				cin >> c;
				if (c == f)
				{
					cout << "回答正确!" << endl;
					rightnum++;

				}
				else
				{
					cout << "回答错误!" << endl;
					cout << "前往文件查看正确答案" << endl;
					wrongnum++;

				}
			}
			else
			{
				printf("请输入答案：\n\t\t %d/%d×%d/%d = ", a, b, d, e);
				ofile << a << '/' << b << "×" << d << '/' << e << '=' << f << '/' << g << endl;
				int num1, num2;
				char ch;
				cin >> num1 >> ch >> num2;
				if (num1 == f && num2 == g)
				{
					cout << "回答正确!" << endl;
					rightnum++;

				}
				else
				{
					cout << "回答错误!" << endl;
					cout << "前往文件查看正确答案" << endl;
					wrongnum++;

				}

			}
			break;

		case 2:
			f = a * e, g = b * d;
			m = f, p = g;
			f = f / gcd(m, p);
			g = g / gcd(m, p);
			int a2, b2, d2, e2;
			a2 = a, b2 = b;
			d2 = d, e2 = e;
			a = a / gcd(a2, b2);
			b = b / gcd(a2, b2);
			d = d / gcd(d2, e2);
			e = e / gcd(d2, e2);
			if (f == 0 || g == 1)
			{
				printf("请输入答案：\n\t\t %d/%d÷%d/%d = ", a, b, d, e);
				ofile << a << '/' << b << "÷" << d << '/' << e << '=' << f << endl;
				cin >> c;
				if (c == f)
				{
					cout << "回答正确!" << endl;
					rightnum++;

				}
				else
				{
					cout << "回答错误!" << endl;
					cout << "前往文件查看正确答案" << endl;
					wrongnum++;
				}
			}
			else
			{
				printf("请输入答案：\n\t\t %d/%d÷%d/%d = ", a, b, d, e);
				ofile << a << '/' << b << "÷" << d << '/' << e << '=' << f << '/' << g << endl;
				int num1, num2;
				char ch;
				cin >> num1 >> ch >> num2;
				if (num1 == f && num2 == g)
				{
					cout << "回答正确!" << endl;
					rightnum++;

				}
				else
				{
					cout << "回答错误!" << endl;
					cout << "前往文件查看正确答案" << endl;
					wrongnum++;
				}
			}break;

		}
	}
	ofile.close();
}

//分数加减运算
void fractionadd()
{
	int n, num0;
	cout << "输入分母范围" << endl;
	cin >> num0;
	cout << "输入生成题目数量：" << endl;
	cin >> n;
	std::ofstream ofile;
	ofile.open(".\\test-fractionadd.txt");
	int a, b, d, e, f, g, m, p;
	for (int i = 0; i < n; i++)
	{
		f = 0, g = 0;
		int op;
		int c;
		//scanf_s("%d/%d %c %d/%d", &a, &b, &op, &d, &e);
		srand((int)time(0));
		a = 1 + rand() % num0;//计算范围为-num到num
		srand(i);
		b = 1 + rand() % num0;
		srand(i + 1);
		d = 1 + rand() % num0;
		srand(i + 2);
		e = 1 + rand() % num0;
		srand(i + 3);
		op = 1 + rand() % 2;
		//cin >> a >> b >> op >> d >> e;
		switch (op)
		{
		case 1:
			f = a * e + b * d, g = b * e;
			m = f, p = g;
			f = f / gcd(m, p);
			g = g / gcd(m, p);
			int a1, b1, d1, e1;
			a1 = a, b1 = b;
			d1 = d, e1 = e;
			a = a / gcd(a1, b1);
			b = b / gcd(a1, b1);
			d = d / gcd(d1, e1);
			e = e / gcd(d1, e1);
			if (f == 0 || g == 1)
			{
				printf("请输入答案：\n\t\t %d/%d+%d/%d = ", a, b, d, e);
				ofile << a << '/' << b << '+' << d << '/' << e << '=' << f << endl;
				cin >> c;
				if (c == f)
				{
					cout << "回答正确!" << endl;
					rightnum++;

				}
				else
				{
					cout << "回答错误!" << endl;
					cout << "前往文件查看正确答案" << endl;
					wrongnum++;

				}
			}
			else
			{
				printf("请输入答案：\n\t\t %d/%d+%d/%d = ", a, b, d, e);
				ofile << a << '/' << b << '+' << d << '/' << e << '=' << f << '/' << g << endl;
				int num1, num2;
				char ch;
				cin >> num1 >> ch >> num2;
				if (num1 == f && num2 == g)
				{
					cout << "回答正确!" << endl;
					rightnum++;

				}
				else
				{
					cout << "回答错误!" << endl;
					cout << "前往文件查看正确答案" << endl;
					wrongnum++;

				}
			}
			break;

		case 2:
			f = a * e - b * d, g = b * e;
			if (f >= 0) {
				m = f, p = g;
				f = f / gcd(m, p);
				g = g / gcd(m, p);
			}
			else
			{
				m = -f, p = g;
				f = f / gcd(m, p);
				g = g / gcd(m, p);
			}
			int a2, b2, d2, e2;
			a2 = a, b2 = b;
			d2 = d, e2 = e;
			a = a / gcd(a2, b2);
			b = b / gcd(a2, b2);
			d = d / gcd(d2, e2);
			e = e / gcd(d2, e2);
			if (f == 0 || g == 1)
			{
				printf("请输入答案：\n\t\t %d/%d-%d/%d = ", a, b, d, e);
				ofile << a << '/' << b << '-' << d << '/' << e << '= ' << f << endl;
				cin >> c;
				if (c == f)
				{
					cout << "回答正确!" << endl;
					rightnum++;

				}
				else
				{
					cout << "回答错误!" << endl;
					cout << "前往文件查看正确答案" << endl;
					wrongnum++;
				}

			}

			else
			{
				printf("请输入答案：\n\t\t %d/%d-%d/%d = ", a, b, d, e);
				ofile << a << '/' << b << '+' << d << '/' << e << '= ' << f << '/' << g << endl;
				int num1, num2;
				char ch;
				cin >> num1 >> ch >> num2;
				if (num1 == f && num2 == g)
				{
					cout << "回答正确!" << endl;
					rightnum++;

				}
				else
				{
					cout << "回答错误!" << endl;
					cout << "前往文件查看正确答案" << endl;
					wrongnum++;

				}

			}
			break;
		}
	}
	ofile.close();
}
int mainmenu()
{
	int choise;
	printf("\t  1.整数加减运算\n\n");
	printf("\t  2.整数乘法运算\n\n");
	printf("\t  3.整数除法运算\n\n");
	printf("\t  4.小数加减运算\n\n");
	printf("\t  5.分数加减运算\n\n");
	printf("\t  6.分数乘除运算\n\n");
	printf("\t  7.退出本次练习\n\n");
	printf("\t  请输入相应的序号选择题目类型\n");
	cin >> choise;
	//system("cls");
	switch (choise)
	{
	case 1:intadd(); system("pause"); system("cls"); menu();  break;
	case 2:intmul(); system("pause"); system("cls"); menu();  break;
	case 3:intdiv(); system("pause"); system("cls"); menu();  break;
	case 4:float1(); system("pause"); system("pause");  system("cls"); menu(); break;
	case 5:fractionadd(); system("pause"); system("cls"); menu(); break;
	case 6:fractionmul(); system("pause"); system("cls"); menu(); break;
	case 7:return 1; break;
	default:printf("请正确输入序号!\n"); mainmenu(); break;
	}
}
int menu()
{
	int con;
	printf("\n\t1.继续进行运算？\n");
	printf("\n\t2.退出本次练习？\n");
	cin >> con;
	switch (con)
	{
	case 1:
		system("cls");
		mainmenu();
		break;
	case 2:
		return 1;
		break;
	default:
		printf("请正确输入序号!\n");
		return 1;
		break;
	}
}
int main()
{
	int mainmenu();
	if (mainmenu() == 1)
	{
		printf("您总共完成了 %d 道题\n正确数量 %d 道\n错误数量 %d 道\n", rightnum + wrongnum, rightnum, wrongnum);
		score = rightnum;
		printf("您本次练习得分为%d\n", score);
		system("pause");
	}
}