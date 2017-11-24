#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MaxSize 100

struct StackRecord;
typedef struct StackRecord *Stack;

struct StackRecord
{
	int Top;
	char Data[MaxSize];
};

void MakeEmpty(Stack S)
{
	 S->Top = -1;
}

int Push(Stack S, char c)
{
	if (S->Top == MaxSize)
		return -1;
	S->Data[++S->Top] = c;
}

char Pop(Stack S)
{
	if (S->Top == -1)
		return -1;
	return S->Data[S->Top--];
}

char Peek(Stack S)
{
	if (S->Top == -1)
		return -1;
	return S->Data[S->Top];
}

int main()
{
	char a[200], b[6], c[4] ,*p, *q;
	int i;
	scanf("%s", &a);
	Stack S = (Stack)malloc(sizeof(StackRecord));
	MakeEmpty(S);
	for (p = a; *p != '\0'; p++)
	{
		if (*p == '(' || *p == '[' || *p == '{')
			Push(S, *p);
		else if (*p == 'b')
		{
			for ( q= p, i = 0; i < 5; i++)
			{
				b[i] = *q;
				q++;
			}
			b[i] = '\0';
			if (strcmp(b, "begin") == 0)
			{
				p = q;
				Push(S, *q);
			}
		}
		else if (*p == 'e')
		{
			for (q = p, i = 0; i < 3; i++)
			{
				c[i] = *q;
				q++;
			}
			c[i] = '\0';
			if (strcmp(c, "end") == 0)
			{
				p = q;
				if (Peek(S) == 'b')
					Pop(S);
				else
					printf("There is a end with no begin\n");
			}
		}
		else if (*p == ')')
		{
			if (Peek(S) == '(')
				Pop(S);
			else
				printf("There is a right parenthes with no left parethes\n");
		}
		else if (*p == ']')
		{
			if (Peek(S) == '[')
				Pop(S);
			else
				printf("There is a right bracket with no left bracket\n");
		}
		else if (*p == '}')
		{
			if (Peek(S) == '{')
				Pop(S);
			else
				printf("There is a right brace with no left brace\n");
		}
	}
}
