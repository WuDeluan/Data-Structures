/*
输入

有多组测试数据，每组测试数据占两行。第一行是集合A，第一个整数m（0<=m<=100）代表集合A起始有m个元素，后面有m个非递减排序的整数，代表A中的元素。第二行是集合B，第一个整数n(0<=n<=100)代表集合B起始有n个元素，后面有n个非递减排序的整数，代表B中的元素。每行中整数之间用一个空格隔开。
输出

每组测试数据只要求输出一行，这一行含有 m+n 个来自集合 A 和集合B 中的元素。结果依旧是非递减的。每个整数间用一个空格隔开。
样例输入

4 3 5 8 11
7 2 6 8 9 11 15 20
样例输出

2 3 5 6 8 8 9 11 11 15 2
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
	for (P = L->Next; P; P = P->Next)
		//(P->Next) ? printf("%d ", P->Number) : printf("%d\n", P->Number);
		printf("%d ", P->Number);
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

void Union(List L1, List L2,List &L3)
{
	Position P1, P2;
	P1 = L1->Next;
	P2 = L2->Next;
	while (P1 && P2)
	{
		if (P1->Number < P2->Number)
		{
			Add(L3, P1->Number);
			P1 = P1->Next;
		}
		else
		{
			Add(L3, P2->Number);
			P2 = P2->Next;
		}
	}
	while (P1)
	{
		Add(L3, P1->Number);
		P1 = P1->Next;
	}
	while (P2)
	{
		Add(L3, P2->Number);
		P2 = P2->Next;
	}
	Print(L3);
}

int main()
{
	List L1 = (Node*)malloc(sizeof(Node)); L1->Next = NULL;
	List L2 = (Node*)malloc(sizeof(Node)); L2->Next = NULL;
	List L3 = (Node*)malloc(sizeof(Node)); L3->Next = NULL;

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
		Union(L1, L2, L3);
		Delete(L1);
		Delete(L2);
		Delete(L3);
	}
}
