#include <iostream>
#include <cstring>
#include <bitset>
#include <cmath>
#include <stack>
#include <iomanip>
#include <cstdlib>
#include <complex>
#include <complex.h>
using namespace std;

char opt_set[10] = "+-*/()=.^";
char opt_Set[8] = "+-*/=.^";
class Calculator
{
public:
	int level(char theOpt);									//操作符的优先级
	bool isRight(char theChar);								//判断输入的操作符是否合法，仅包括()+-*/
	bool isright(char thwChar);                             //单独判断连续输入两个运算符的错误
	bool delSpace(string& theString);						//用于去除空格并检查是否有非法字符
	bool change(string& from, string& to);					//将中缀表达式转换成后缀表达式
	bool count(string& theExp);							    //计算后缀表达式
	int isTriangle(string& theStr);					        //判断是否为三角函数或反三角函数并返回对应的编号
	double calNumber(string& theStr, int theInt);		    //求三角函数里包含的数字并求出对应的结果
public:
	stack<char> opt;                                        //操作符栈
	stack<double> val;                                      //操作数栈
};

int main()
{
	Calculator calculator;
	cout << "欢迎使用计算器" << endl;
	cout << "你可以使用这个计算器做以下运算" << endl;
	cout << "--加、减、乘、除、幂次(^)" << endl;
	cout << "--开方:sqrt, 输入时左右需加括号，如sqrt(4), 不可混合运算" << endl;
	cout << "--三角函数:输入时弧度左右需加括号，如sin(30)，不可混合运算" << endl;
	cout << "--进制转换:请先输入con,再依次输入想转换的数和进制数(2,8,10,16)" << endl;
	cout << "如果你想退出,输入exit即可" << endl;
	while (1)
	{
		string in_exp;
		cout << "----请输入表达式:";
		cin >> in_exp;
		if (in_exp == string("exit"))
		{
			cout << "感谢您的使用" << endl;
			break;
		}
		else if (in_exp == string("con"))                                                   //进制转换
		{
			int n, x;
			cin >> n >> x;
			switch (x)
			{
			case 2:cout << n << "的" << x << "进制为 : " << bitset<8>(n) << endl; break;
			case 8:cout << n << "的" << x << "进制为 : " << std::oct << n << endl; break;
			case 10:cout << n << "的" << x << "进制为 : " << std::dec << n << endl; break;
			case 16:cout << n << "的" << x << "进制为 : " << std::hex << n << endl; break;
			}
		}
		else if (calculator.isTriangle(in_exp) != 0)                                               //判断是否三角函数和反三角函数并求值
		{
			double res = 0;
			res = calculator.calNumber(in_exp, calculator.isTriangle(in_exp));
			if (res)
				cout << "结果为: " << res << endl;
		}
		else                                                                                       //是加减乘除的情况
		{
			cin.clear();
			cin.sync();                                                                            //清空错误字符
			while (!calculator.opt.empty())                                                        //判断栈是否为空 
			{
				calculator.opt.pop();                                                              //移除栈顶元素
			}
			while (!calculator.val.empty())
			{
				calculator.val.pop();
			}
			calculator.delSpace(in_exp);                                                          //整理表达式，去除空格
			string out_exp;
			out_exp.clear();
			calculator.change(in_exp, out_exp);	                                                  //转换为后缀表达式
			calculator.count(out_exp);                                                            //计算后缀表达式
			double result = calculator.val.top();
			cout << "结果为:" << (double)result << endl;
		}
		cout << endl;
	}
	return 0;
}

int Calculator::level(char a)
{
	switch (a)
	{
	case '(':return 0;
	case '+':
	case '-':return 1;
	case '*':
	case '^':
	case '/':return 2;
	case ')':return 3;
	}
}
bool Calculator::isRight(char theChar)
{
	for (int i = 0; i < 9; i++)
	{
		if (theChar == opt_set[i])
			return true;
	}
	return false;
}
bool Calculator::isright(char theChar)
{
	for (int i = 0; i < 7; i++)
	{
		if (theChar == opt_Set[i])
			return true;
	}
	return false;
}
bool Calculator::delSpace(string& theString)
{
	string a;
	int j = 0;
	for (int i = 0; i < theString.length(); i++)
	{
		if (isRight(theString[i]) || (theString[i] >= '0' && theString[i] <= '9'))
			a += theString[i];
		else if (theString[i] == ' ') {}
		else
		{
			cout << "输入错误，自动退出" << endl;
			exit(0);
		}
		if (i >= 1)
		{
			if (isright(theString[i]) && isright(theString[j]))
			{
				cout << "输入错误，自动退出" << endl;
				exit(0);
			}
			j++;
		}
	}
	theString = a;
	return true;
}
bool Calculator::change(string& from, string& to)
{
	int d = 0;
	int state = 1;
	char c;
	for (int i = 0; i < from.length(); i++)
	{
		c = from[i];
		if (c >= '0' && c <= '9')
		{
			to = to + c;
			d *= 10;
			d += c - '0';
			state = 0; //状态改为在数字内
		}
		else
		{
			if (state == 0 && c == '.')
			{
				to = to + '.';
				d = 0;
				continue;
			}
			if (state == 0 && c != '.')
			{
				to += ' ';
				d = 0;
			}
			if (c == '=')
				break;
			else if (c == '(')
				opt.push(c);
			else if (c == ')')
			{
				while (!opt.empty() && opt.top() != '(')
				{
					to += opt.top();
					to += ' ';
					opt.pop();
				}
				opt.pop();
			}
			else
			{
				while (1)
				{
					if (opt.empty() || opt.top() == '(')
						opt.push(c);
					else if (level(c) > level(opt.top()))
						opt.push(c);
					else
					{
						to += opt.top();
						to += ' ';
						opt.pop();
						continue;
					}
					break;
				}
			}
			state = 1; //状态为在数字外
		}
	}
	while (!opt.empty())
	{
		to += opt.top();
		to += ' ';
		opt.pop();
	}
	return true;
}
bool Calculator::count(string& theExp)
{
	int a = 0; //暂存数字
	int state = 1;//初始状态为在数字外
	char c;
	bool b = false;
	double count = 1.0;
	for (int i = 0; i < theExp.length(); i++)
	{
		c = theExp[i];
		if ((c >= '0' && c <= '9') || c == '.')
		{
			if (c >= '0' && c <= '9')
			{
				a *= 10;
				a += c - '0';
				state = 0; //状态为在数字内
				if (b == true)
					count *= 10.0;
			}
			if (c == '.') {
				b = true;
				continue;
			}
		}
		else
		{
			b = false;
			double ans = a / count;
			count = 1.0;
			if (state == 0)
			{
				val.push(ans);
				a = 0;
			}
			double x, y;
			if (c != ' ')
			{
				x = val.top(); val.pop();
				y = val.top(); val.pop();
				switch (c)
				{
				case '+':val.push(x + y); break;
				case '-':val.push(y - x); break;
				case '*':val.push(x * y); break;
				case '/':val.push(y / x); break;
				case '^':val.push(pow(y, x)); break;
				default:cout << "未知的错误!" << endl;
				}
			}
			state = 1;
		}
	}
	return true;
}
int Calculator::isTriangle(string& theStr)
{
	string str1 = "sin";
	string str2 = "cos";
	string str3 = "tan";
	string str4 = "arcsin";
	string str5 = "arccos";
	string str6 = "arctan";
	string str7 = "sqrt";
	const char* show1, * show2, * show3, * show4, * show5, * show6, * show7;
	show1 = strstr(theStr.c_str(), str1.c_str());                              //c_str():将c++中string转化为C中字符数组
	if (show1 != NULL)                                                        //strstr(a,b):判断b是否为a的子字符串
		return 1;
	show2 = strstr(theStr.c_str(), str2.c_str());
	if (show2 != NULL)
		return 2;
	show3 = strstr(theStr.c_str(), str3.c_str());
	if (show3 != NULL)
		return 3;
	show4 = strstr(theStr.c_str(), str4.c_str());
	if (show4 != NULL)
		return 4;
	show5 = strstr(theStr.c_str(), str5.c_str());
	if (show5 != NULL)
		return 5;
	show6 = strstr(theStr.c_str(), str6.c_str());
	if (show6 != NULL)
		return 6;
	show7 = strstr(theStr.c_str(), str7.c_str());
	if (show7 != NULL)
		return 7;
	return 0;
}
double Calculator::calNumber(string& theStr, int theInt)
{
	int b = 0;
	for (int i = 0; theStr[i] != ')'; i++)
	{
		if (theStr[i] >= '0' && theStr[i] <= '9')
		{
			b *= 10;
			b += theStr[i] - '0';
		}
	}
	double a = 0.0;
	switch (theInt)
	{
	case 1:a = sin(b); break;
	case 2:a = cos(b); break;
	case 3:a = tan(b); break;
	case 4:a = asin(b); break;
	case 5:a = acos(b); break;
	case 6:a = atan(b); break;
	case 7:a = sqrt(b); break;
	default:return 0;
		break;
	}
	return a;
}