#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
#define MaxSize 20
template <typename T>
class Stack
{
public:
	void InitStack()
	{
		Top = -1;
	}

	int IsEmpty() 
	{
		return Top == -1;
	}

	int Push(T X) 
	{
		if (Top + 1 == MaxSize)
			return -1;
		Data[++Top] = X;
		return 0;
	}

	T Pop() 
	{
		if (Top == -1)
			return 0;
		return Data[Top--];
	}

	T Peek()
	{
		if (Top == -1)
			return 0;
		return Data[Top];
	}
private:
	int Top;
	T Data[MaxSize];
};

void Operate(Stack<double> &OperandStack, Stack<char> &OperatorStack)
{
	char op = OperatorStack.Pop();
	double a = OperandStack.Pop();
	double b = OperandStack.Pop();
	if (op == '+')
		OperandStack.Push(a + b);
	else if (op == '-')
		OperandStack.Push(b - a);
	else if (op == '*')
		OperandStack.Push(a * b);
	else if (op == '/')
		OperandStack.Push(b / a);
}
int IsOperator(char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')'|| c == '#')
		return 1;
	else
		return 0;
}
int EvaluateExpression(char *Expression)
{
	Stack<char> OperatorStack;
	Stack<double> OperandStack;
	OperandStack.InitStack();
	OperatorStack.InitStack();
	char *c;
	int i = 0;
	while ( Expression[i] != '#')
	{
		if (Expression[i] == '+' || Expression[i] == '-')
		{
			
			while (!OperatorStack.IsEmpty() && OperatorStack.Peek() == '+' || OperatorStack.Peek() == '-'
				|| OperatorStack.Peek() == '*' || OperatorStack.Peek() == '/')
				Operate(OperandStack, OperatorStack);
			OperatorStack.Push(Expression[i]); 
		}
		else if (Expression[i] == '*' || Expression[i] == '/')
		{
			while (!OperatorStack.IsEmpty() && OperatorStack.Peek() == '*' || OperatorStack.Peek() == '/')
				Operate(OperandStack, OperatorStack);
			OperatorStack.Push(Expression[i]); 
		}
		else if (Expression[i] == '(')
		{
			OperatorStack.Push(Expression[i]); 
		}
		else if (Expression[i] == ')')
		{
			while (OperatorStack.Peek() != '(') 
				Operate(OperandStack, OperatorStack);
			OperatorStack.Pop(); 
		}
		else
		{
			double num = 0;
			while (!IsOperator(Expression[i]))
			{
				num *= 10;
				num += (Expression[i] - '0');
				i++;
			}
			OperandStack.Push(num);
			i--;
		}
		i++;
			 
	}
	while (!OperatorStack.IsEmpty()) 
	{
		Operate(OperandStack, OperatorStack);
	}
	return OperandStack.Pop();
}

int main()
{
	char MyExpression[20];
	while (scanf("%s", &MyExpression) != EOF)
	{
		printf("%d\n",EvaluateExpression(MyExpression));
	}
}
