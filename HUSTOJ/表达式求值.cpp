/*
输入

以“#”结尾的表达式，运算数为正整数。每个表达式占一行。
输出

输出表达式运算的结果。
样例输入

4+2*3-10/5#
3*(7-2)#
2*3/2#
样例输出

8
15
3

*/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
#define MaxSize 200

template <typename T>
class Stack
{
public:
	Stack()
	{
		Top = -1;
	}

	int empty()
	{
		return Top == -1;
	}

	int push(T X) 
	{
		if (Top + 1 == MaxSize)
			return -1;
		Data[++Top] = X;
		return 0;
	}

	T pop() 
	{
		if (Top == -1)
			return 0;
		return Data[Top--];
	}

	T top()
	{
		if (Top == -1)
			return NULL;
		return Data[Top];
	}
private:
	int Top; 
	T Data[MaxSize];
};


void J(Stack<int> &Operand, Stack<char> &Operator)
{
	char op = Operator.pop();
	int a = Operand.pop();
	int b = Operand.pop();
	if (op == '+')
		Operand.push(a + b);
	else if (op == '-')
		Operand.push(b - a);
	else if (op == '*')
		Operand.push(a * b);
	else if (op == '/')
		Operand.push(b / a);
}

int IsOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/'
		|| c == '(' || c == ')' || c == '#')
		return 1;
	else
		return 0;
}

int main()
{
	char s[100], *p, *q;
	Stack<int> Operant;
	Stack<char> Operator;
	while (scanf("%s", s) != EOF)
	{
		for (p = s; *p != '#'; p++)
		{
			if (*p == '+' || *p == '-')
			{
				while (Operator.top() == '+' || Operator.top() == '-' ||
					Operator.top() == '*' || Operator.top() == '/')
					J(Operant, Operator);
				Operator.push(*p);
			}
			else if (*p == '*' || *p == '/')
			{
				while(Operator.top() == '*' || Operator.top() == '/')
					J(Operant, Operator);
				Operator.push(*p);
			}
			else if (*p == '(')
				Operator.push(*p);
			else if (*p == ')')
			{
				while (Operator.top() != '(')
					J(Operant, Operator);
				Operator.pop();
			}
			else if (!IsOperator(*p))
			{
				int i = 0;
				char a[6];
				a[i] = *p;
				while (!IsOperator(*(p+1)))
					a[++i] = *(++p);
				a[i+1] = '\0';   //!!!!!
				Operant.push(atoi(a));
			}
		}
		while (!Operator.empty())
			J(Operant, Operator);
		printf("%d\n", Operant.top());
	}
}
