/*
一个简单的行编辑程序的功能是：接收用户从终端输入的程序或数据，并存入用户的数据区。
由于用户在终端上进行输入时，不能保证不出差错，因此，若在编辑程序中，“每接收一个
字符即存入用户数据区”的做法显然不是很恰当。较好的做法是，设立一个输入缓冲区，用
以接收用户输入的一行字符，然后逐行存入用户数据区。允许用户输入出差错，并在发现有
误时可以及时更正。例如，当用户发现刚刚键入的一个字符是错的时，可补进一个退格符“#”
，以表示前一个字符无效；如果发现当前键入的行内错误较多或难以补救，则可以键入一个
退行符“@”，以表示当前行中的字符均无效。例如假设从终端接收了这样的两行字符：
whil##ilr#e(s#*s)
outcha@    putchar(*s=#++);
则实际有效的是下列两行：
while(*s)
putchar(*s++);
为此，可设这个输入缓冲区为一个栈结构，每当从终端接收了一个字符之后先作如下判别：
如果它不是退格符也不是退行符，则将该字符压入栈顶；如果是一个退格符，则从栈顶删去
一个字符；如果它是一个退行符，则将字符栈清为空栈。*/

#include <stdio.h>
#include <stdlib.h>
#define MaxSize 20

typedef char ElementType;
typedef struct StackRecord {
	int Top;
	ElementType Data[MaxSize];
};
typedef StackRecord *Stack;

void MakeEmpty(Stack S)
{
	S->Top = -1;
}

int Pop(Stack S, ElementType &X)
{
	if (S->Top == -1)
		return -1;
	X = S->Data[S->Top--];
	return 0;
}

int Push(Stack S, ElementType X)
{
	if (S->Top + 1 == MaxSize)
		return -1;
	S->Data[++S->Top] = X;
	return 0;
}

ElementType Peek(Stack S)
{
	if (S->Top == -1)
		return -1;
	return S->Data[S->Top];
}

void LineEdit()
{
	char ch, *temp;
	Stack S;
	S = (Stack)malloc(sizeof(StackRecord));
	MakeEmpty(S);
	ch = getchar();
	while (ch != EOF) {
		while (ch != EOF && ch != '\n')
		{
			switch (ch) {
			case '#':Pop(S, ch); break;
			case '@':MakeEmpty(S); break;
			default:Push(S, ch); break;
			}
			ch = getchar();
		}
		int Temp = S->Top;
		S->Top = 0;
		while (S->Top <= Temp) {
			printf("%c", S->Data[S->Top]);
			S->Top++;
		}
		MakeEmpty(S);
		printf("\n");
		if (ch != EOF) {
			ch = getchar();
		}
	}
}

int main()
{
	LineEdit();
}
