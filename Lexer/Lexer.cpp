#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

string func[20] = { "sin","cos","tg","ctg","^","log","lg","ln" };
string num[20];
string vari[20];
string compart[20] = { " ","\t","\n","(",")",";" };
string operation[20] = { "+","*","/","=" };
char ch[20];
int token[100];
string str;
int k = 0;
int tokeni = 0;
int k1 = 0, k2 = 0;
int state, g = 0;

/*记号表
	01	02	03	04	05	06	07	08	09	10
	sin	cos	tg	ctg	^	log	lg	ln	-	+
	11	12	13	14	15	16	17	18	19	20
	*	/	=	空	\t	\n	(	)	;	常
	21	22	23
	变	？	err
*/

bool Ischar(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return 1;
	else
		return 0;
}

bool Isnumber(char c)
{
	if (c >= '0' && c <= '9')
		return 1;
	else
		return 0;
}

bool Isnumbers(char c)
{
	if (c >= '1' && c <= '9')
		return 1;
	else
		return 0;
}

bool Isfunc(string c)
{
	for (int i = 0; i < 8; i++)
	{
		if (func[i].compare(c) == 0)
			return 1;
	}
	return 0;
}

bool Isunderline(char c)
{
	if (c == '_')
		return 1;
	else return 0;
}

bool Isoperate(char c)
{
	if (c == '+' || c == '*' || c == '/' || c == '=')
		return 1;
	else
		return 0;
}

bool Iscompart(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '(' || c == ')' || c == ';')
		return 1;
	else
		return 0;
}

int move(int state, char c)
{
	bool Isletter, Isdigit, Isdigits, IsUnderline, IsOperate, IsCompart;
	g = 0;
	Isletter = Ischar(c);
	Isdigit = Isnumber(c);
	Isdigits = Isnumbers(c);
	IsUnderline = Isunderline(c);
	IsOperate = Isoperate(c);
	IsCompart = Iscompart(c);
	
	/*判断运算符*/
	if (state == 1 && c == '-')
	{
		state = 2;
		//ch[k] = c;
		//k++;
		cout << c << "\t运算符<9>" << endl;
		token[tokeni] = 9;
		tokeni++;
		return state;
	}
	if (state == 1 && (IsOperate == 1 || IsCompart == 1 ))
	{
		//cout << "\n当前k=" << k << endl;
		ch[k] = c;
		str = ch[k];
		//cout << endl << "已经进入运算符或分隔符判断了,当前判断的是："<<str<< endl;
		int i = 0;
		int p = 0;
		for (i = 0; i < 20; i++)
		{
			if (str == operation[i])
			{
				//cout <<endl<< "是运算符，str=" << str << endl;
				p = 1;
				break;
			}
			if (str == compart[i])
			{
				p = 2;
				break;
			}
		}
		if (p == 1)
		{
			cout << str << "\t运算符<" << i + 10<<">"<<endl;
			token[tokeni] = i + 10;
			tokeni++;
		}
		if (p == 2)
		{
			cout << str << "\t分隔符<" << i + 14 << ">" << endl;
			token[tokeni] = i + 14;
			tokeni++;
		}
		state = 1;
		k = 0;
		return state;
	}

	if (state == 1 && c == '?')
	{
		ch[k] = c;
		str = ch;
		cout << str << "\t运算符<22>" << endl;
		token[tokeni] = 22;
		tokeni++;
		state = 1;
		k = 0;
		return state;
	}

	if (state == 1 && c == '^')
	{
		ch[k] = c;
		str = ch;
		cout << str << "\t函数<05>" << endl;
		token[tokeni] = 05;
		tokeni++;
		state = 1;
		k = 0;
		return state;
	}

	/*判断常量*/
	if (state == 1 && Isdigits == 1)
	{
		state = 3;
		ch[k] = c;
		k++;
		return state;
	}

	if (state == 1 && c == '0')
	{
		state = 4;
		ch[k] = c;
		k++;
		return state;
	}

	if (state == 1 && (c == 'PI' || c == 'E'))
	{
		state = 5;
		ch[k] = c;
		k++;
		return state;
	}

	if (state == 2 && Isdigits == 1)
	{
		state = 3;
		ch[k] = c;
		k++;
		return state;
	}

	if (state == 2 && c == '0')
	{
		state = 4;
		ch[k] = c;
		k++;
		return state;
	}

	if (state == 3 && Isdigit == 1)
	{
		state = 3;
		ch[k] = c;
		k++;
		return state;
	}

	if ((state == 3 || state == 4) && c == '.')
	{
		state = 6;
		ch[k] = c;
		k++;
		return state;
	}

	if (state == 6 && Isdigits == 1)
	{
		state = 7;
		ch[k] = c;
		k++;
		return state;
	}

	if (state == 6 && c == '0')
	{
		state = 6;
		ch[k] = c;
		k++;
		return state;
	}

	if (state == 7 && c == '0')
	{
		state = 6;
		ch[k] = c;
		k++;
		return state;
	}

	if (state == 7 && Isdigits == 1)
	{
		state = 7;
		ch[k] = c;
		k++;
		return state;
	}

	if ((state == 3 && Isdigit == 0 && c != '.') || (state == 4 && c != '.') || (state == 5) || (state == 7 && Isdigit == 0))
	{
		ch[k] = '\0';
		str = ch;
		int i, p = 0;
		for (i = 0; i < 20; i++)
		{
			if (str == num[i])
			{
				p = 1;
				break;
			}
		}
		if (p == 1)
			cout << str << "\t常量<20>" << endl;
		else
		{
			num[k1] = str;
			cout << str << "\t常量<20>" << endl;
			k1++;
		}
		token[tokeni] = 20;
		tokeni++;
		g = 1;
		//cout << endl << "g=" << g << endl;
		state = 1;
		k = 0;
		return state;
	}

	/*判断变量*/
	if (state == 1 && (Isletter == 1 || IsUnderline == 1))
	{
		state = 8;
		ch[k] = c;
		k++;
		return state;
	}

	if (state == 8 && (Isletter == 1 || Isdigit == 1 || IsUnderline == 1))
	{
		state = 8;
		ch[k] = c;
		k++;
		return state;
	}

	if (state == 8 && (Isletter == 0 || Isdigit == 0 || IsUnderline == 0))
	{
		ch[k] = '\0';
		str = ch;
		if (str == "PI")
		{
			cout << str << "\t常量<20>" << endl;
			token[tokeni] = 20;
			tokeni++;
			state = 1;
			k = 0;
			g = 1;
			return state;
		}

		int i, p = 0;
		for (i = 0; i < 20; i++)
		{
			if (str == func[i])
			{
				p = 1;
				break;
			}
		}
		if (p == 1)
		{
			cout << str << "\t 函数<" << i + 1 << ">" << endl;
			token[tokeni] = i + 1;
			tokeni++;
		}
		else {
			for (i = 0; i < 20; i++)
			{
				if (vari[i] == str)
				{
					p = 1;
					break;
				}
			}
			if (p == 1)
			{
				cout << str << "\t变量<21> " << endl;
			}
			else
			{
				vari[k2] = str;
				k2++;
				cout << str << "\t变量<21>" << endl;
			}
		token[tokeni] = 21;
		tokeni++;
		}
		g = 1;
		state = 1;
		k = 0;
		return state;
	}
	else
	{
		state = 1;
		cout << "error!" << endl;
		return state;
	}
	return 0;
}

int main()
{
	int j;
	state = 1;
	char c;
	FILE *fp = NULL;
	errno_t err;
	err = fopen_s(&fp,"test.txt", "r");
	while ((c = fgetc(fp)) != EOF)
	{
		//cout <<endl<< c << endl;
		state = move(state, c);
		if (g == 1)
		{
			//cout << "我又运行一次了哦,现在的c为：" <<c<<"state是："<<state<< endl;
			state = move(state, c);
		}
	}
	fclose(fp);
	cout << "token序列：" << endl;
	for (j = 0; j < tokeni; j++)
	{
		cout.fill('0');
		cout << "<" << token[j] << ">";
	}
	cout << endl;
	return 0;
}

