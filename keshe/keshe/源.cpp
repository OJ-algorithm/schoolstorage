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
	int level(char theOpt);									//�����������ȼ�
	bool isRight(char theChar);								//�ж�����Ĳ������Ƿ�Ϸ���������()+-*/
	bool isright(char thwChar);                             //�����ж�������������������Ĵ���
	bool delSpace(string& theString);						//����ȥ���ո񲢼���Ƿ��зǷ��ַ�
	bool change(string& from, string& to);					//����׺���ʽת���ɺ�׺���ʽ
	bool count(string& theExp);							    //�����׺���ʽ
	int isTriangle(string& theStr);					        //�ж��Ƿ�Ϊ���Ǻ��������Ǻ��������ض�Ӧ�ı��
	double calNumber(string& theStr, int theInt);		    //�����Ǻ�������������ֲ������Ӧ�Ľ��
public:
	stack<char> opt;                                        //������ջ
	stack<double> val;                                      //������ջ
};

int main()
{
	Calculator calculator;
	cout << "��ӭʹ�ü�����" << endl;
	cout << "�����ʹ���������������������" << endl;
	cout << "--�ӡ������ˡ������ݴ�(^)" << endl;
	cout << "--����:sqrt, ����ʱ����������ţ���sqrt(4), ���ɻ������" << endl;
	cout << "--���Ǻ���:����ʱ��������������ţ���sin(30)�����ɻ������" << endl;
	cout << "--����ת��:��������con,������������ת�������ͽ�����(2,8,10,16)" << endl;
	cout << "��������˳�,����exit����" << endl;
	while (1)
	{
		string in_exp;
		cout << "----��������ʽ:";
		cin >> in_exp;
		if (in_exp == string("exit"))
		{
			cout << "��л����ʹ��" << endl;
			break;
		}
		else if (in_exp == string("con"))                                                   //����ת��
		{
			int n, x;
			cin >> n >> x;
			switch (x)
			{
			case 2:cout << n << "��" << x << "����Ϊ : " << bitset<8>(n) << endl; break;
			case 8:cout << n << "��" << x << "����Ϊ : " << std::oct << n << endl; break;
			case 10:cout << n << "��" << x << "����Ϊ : " << std::dec << n << endl; break;
			case 16:cout << n << "��" << x << "����Ϊ : " << std::hex << n << endl; break;
			}
		}
		else if (calculator.isTriangle(in_exp) != 0)                                               //�ж��Ƿ����Ǻ����ͷ����Ǻ�������ֵ
		{
			double res = 0;
			res = calculator.calNumber(in_exp, calculator.isTriangle(in_exp));
			if (res)
				cout << "���Ϊ: " << res << endl;
		}
		else                                                                                       //�ǼӼ��˳������
		{
			cin.clear();
			cin.sync();                                                                            //��մ����ַ�
			while (!calculator.opt.empty())                                                        //�ж�ջ�Ƿ�Ϊ�� 
			{
				calculator.opt.pop();                                                              //�Ƴ�ջ��Ԫ��
			}
			while (!calculator.val.empty())
			{
				calculator.val.pop();
			}
			calculator.delSpace(in_exp);                                                          //������ʽ��ȥ���ո�
			string out_exp;
			out_exp.clear();
			calculator.change(in_exp, out_exp);	                                                  //ת��Ϊ��׺���ʽ
			calculator.count(out_exp);                                                            //�����׺���ʽ
			double result = calculator.val.top();
			cout << "���Ϊ:" << (double)result << endl;
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
			cout << "��������Զ��˳�" << endl;
			exit(0);
		}
		if (i >= 1)
		{
			if (isright(theString[i]) && isright(theString[j]))
			{
				cout << "��������Զ��˳�" << endl;
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
			state = 0; //״̬��Ϊ��������
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
			state = 1; //״̬Ϊ��������
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
	int a = 0; //�ݴ�����
	int state = 1;//��ʼ״̬Ϊ��������
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
				state = 0; //״̬Ϊ��������
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
				default:cout << "δ֪�Ĵ���!" << endl;
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
	show1 = strstr(theStr.c_str(), str1.c_str());                              //c_str():��c++��stringת��ΪC���ַ�����
	if (show1 != NULL)                                                        //strstr(a,b):�ж�b�Ƿ�Ϊa�����ַ���
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