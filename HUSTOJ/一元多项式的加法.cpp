/*
输入

输入数据包含多组测试数据，每组数据包含两行一元多项式。每个多项式包含若干对整数，每对整数的第一个是系数，第二个是指数。每个多项式不超过100项，整数间用空格隔开，并且指数是递减的。
输出

每组测试数据输出一行结果，每个整数后面空一格。(包括行尾)
样例输入

3 2 4 1 7 0
2 4 1 1
2 3
1 4
3 2 4 1 7 0
2 4 -4 1
样例输出

2 4 3 2 5 1 7 0 
1 4 2 3 
2 4 3 2 7 0 

提示：
1、由于多项式元素的重要信息在系数和指数，所以可以定义结点类型为含两个整数的结构体，一个代表系数而另一个代表指数。
2、定义完数据类型后，主要的就是怎么读取数据了。由于每个多项式占一行，所以可以用gets来读取一行，并判断是否为空
行：while(gets(strA) && strlen(strA))...然后就将字符串中的数据转换为多项式类型。此时使用到一个字符串处理函数
char * strtok ( char * str, const char * delimiters )。这个函数的主要功能是将字符串str按delimiters中的字符
分割。使用这个字符串处理函数时注意在处理某个字符串时首次使用时传递的参数是字符串指针而以后在使用时传递的参数是NULL。
3、下面的算法与有序序列有序合并算法类似。因为是多次循环，如果里面含有迭代变量（i，j之类的）注意下次循环时初值对不对。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct Node
{
	int a, e;
	struct Node *Next;
}*List, *Position;

void Add(List L, int a, int e)
{
	Position P = L;
	Position Tmp = (Node*)malloc(sizeof(Node));
	Tmp->a = a;
	Tmp->e = e;
	Tmp->Next = NULL;
	while (P->Next)
		P = P->Next;
	P->Next = Tmp;
}

void Print(List L)
{
	Position P;
	for (P = L->Next; P; P = P->Next)
		printf("%d %d ", P->a, P->e);
	printf("\n");
}

void Delete(List L)
{
	Position P = L->Next;
	while (P)
	{
		Position Q = P;
		L->Next = P->Next;
		free(Q);
		P = L->Next;
	}
}

void Union(List L1, List L2, List &L3)
{

	Position P1 = L1->Next, P2 = L2->Next;
	while (P1 && P2)
	{
		if (P1->e == P2->e)
		{
			if (P1->a + P2->a == 0)
				;
			else
				Add(L3, P1->a + P2->a, P1->e);
			P1 = P1->Next;
			P2 = P2->Next;
		}
		else if (P1->e < P2->e)
		{
			Add(L3, P2->a, P2->e);
			P2 = P2->Next;
		}
		else if (P1->e > P2->e)
		{
			Add(L3, P1->a, P1->e);
			P1 = P1->Next;
		}
	}
	while (P1)
	{
		Add(L3, P1->a, P1->e);
		P1 = P1->Next;
	}
	while (P2)
	{
		Add(L3, P2->a, P2->e);
		P2 = P2->Next;
	}
	Print(L3);
}

int main()
{
	int a, e;
	char strA[200];
	List L1 = (Node*)malloc(sizeof(Node)); L1->Next = NULL;
	List L2 = (Node*)malloc(sizeof(Node)); L2->Next = NULL;
	List L3 = (Node*)malloc(sizeof(Node)); L3->Next = NULL;
	while (gets(strA) && strlen(strA))
	{
		char *temp = strtok(strA, " ");
		while (temp)
		{
			a = atoi(temp);
			temp = strtok(NULL, " ");
			e = atoi(temp);
			temp = strtok(NULL, " ");
			Add(L1, a, e);
		}

		gets(strA);
		temp = strtok(strA, " ");
		while (temp)
		{
			a = atoi(temp);
			temp = strtok(NULL, " ");
			e = atoi(temp);
			temp = strtok(NULL, " ");
			Add(L2, a, e);
		}
		Union(L1, L2, L3);
		Delete(L1);
		Delete(L2);
		Delete(L3);
	}

	return 0;
}
