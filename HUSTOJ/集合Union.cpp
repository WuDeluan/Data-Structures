/*
输入

有多组测试数据，每组测试数据占两行。第一行是集合A，第一个整数m（0<m<=100）代表集合A起始有m个元素，后面有m个整数，代表A中的元素。第二行是集合B，第一个整数n(0<n<=100)代表集合B起始有n个元素，后面有n个整数，代表B中的元素。每行中整数之间用一个空格隔开。
输出

每组测试数据输出n+2行：前两行分别输出集合A、集合B中的数据，后面n行是每次从B中取出元素插入到A尾部后的集合A。每行整数之间用一个空格隔开，每组测试数据之间用一行空行隔开。
样例输入

5 1 5 2 6 3
3 1 7 9
1 3
2 2 7
4 2 5 1 4
4 1 2 4 5
样例输出

1 5 2 6 3
1 7 9
1 5 2 6 3
1 5 2 6 3 7
1 5 2 6 3 7 9

3
2 7
3 2
3 2 7

2 5 1 4
1 2 4 5
2 5 1 4
2 5 1 4
2 5 1 4
2 5 1 4

提示：

1、使用数组时，给集合 A 分配的空间不小于200。因为将 B 中的元素添加到 A 中时，可能会超过 100 了。

2、利用 scanf("%d",&m) != EOF 来判断是否还有输入数据。

3、一个细节问题就是题目要求输出的格式是每行中元素之间用一个空格隔开，每组输出间用一个空行隔开。
也就是说4个元素间只有3个空格，2组输出间只有1个空行。处理方法都一样。两种方法：一是除了第一个元素，
后面的每个元素之前输出个空格；二是除了最后一个元素，前面的每个元素之后都输出一个空格。我往往采用第
一种方式，因为许多编程语言中的数组都是从0开始的，而0正是判断语句中的“假”（当然Java中不是这样的）。
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	int Number;
	struct Node *Next;
}*List, *Position;

void Add(List L, int X)
{
	Position P = L;
	Position Tmp = (Node*)malloc(sizeof(Node));
	Tmp->Number = X;
	Tmp->Next = NULL;

	while (P->Next)
		P = P->Next;
	P->Next = Tmp;
}

void Print(List L)
{
	Position P;
	for (P = L->Next; P->Next; P = P->Next)
		printf("%d ", P->Number);
	printf("%d\n", P->Number);
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

void Union(List L1, List L2)
{
	Position P1, P2;
	Print(L1);
	Print(L2);
	int k;
	for (P2 = L2->Next; P2; P2 = P2->Next)
	{
		k = 0;
		for (P1 = L1->Next; P1; P1 = P1->Next)
		{
			if (P1->Number == P2->Number)
				k = 1;
		}
		if (k == 0)
			Add(L1, P2->Number);
		Print(L1);
	}
}
int main()
{
	List L1 = (Node*)malloc(sizeof(Node)); L1->Next = NULL;
	List L2 = (Node*)malloc(sizeof(Node)); L2->Next = NULL;

	int n, m;
	while (scanf("%d", &n) != EOF)
	{
		while (n--)
		{
			scanf("%d", &m);
			Add(L1, m);
		}
		scanf("%d", &n);
		while (n--)
		{
			scanf("%d", &m);
			Add(L2, m);
		}
		Union(L1, L2);
		printf("\n");
		Delete(L1);
		Delete(L2);
	}
}
