/*
输入

输入数据只有一组，包含很多行。每行有1~3个整数。第一个整数如果是0，则表示输出双向链表中的所有元素；第一个整数如果是1，表示插入1个整数，其后跟2个整数i、e代表在第i个位置插入e；第一个整数如果是2，表示删除1个整数，其后跟1个整数i，表示删除的位置为i。
起始双向链表为空表。保证链表中每个元素不会重复，同时所有的操作都合法。
输出

当需要输出双向链表中的所有元素时输出，每次输出一行。整数间用一个空格隔开。
样例输入

1 1 2
0
1 2 7
0
2 1
0
1 2 4
1 3 5
1 2 6
0
2 3
0
样例输出

2
2 7
7
7 6 4 5
7 6 5
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	int Number;
	struct Node *Next, *Prev;
}*List,*Position;

int Delete(List L, int a)
{
	Position P, Q;
	int i;

	for (i = 0, P = L; P->Next; P = P->Next)
	{
		if (i == a - 1)
		{
			Q = P->Next;
			P->Next = Q->Next;
			if(Q->Next)
			  Q->Next->Prev = P;
			free(Q);
			return 1;
	    }
		i++;
	}
	return -1;
}

int Insert(List L, int a, int e)
{
	Position P;
	Position Tmp = (Node*)malloc(sizeof(Node));
	Tmp->Number = e;
	Tmp->Next = NULL;
	int i;
	for (i = 0, P = L; P; P = P->Next)
	{
		if (i == a - 1)
		{
			Tmp->Next = P->Next;
			if (P->Next)
				P->Next->Prev = Tmp;
			P->Next = Tmp;
			Tmp->Prev = P;
			return 1;
		}
		i++;
	}
	return -1;
}

int Print(List L)
{
	Position P;
	if (L->Next)
	{
		for (P = L->Next; P; P = P->Next)
		{
			if (P->Next)
				printf("%d ", P->Number);
			else
				printf("%d\n", P->Number);
		}
		return 1;
	}
	else
		return -1;
}

int main()
{
	List L = (Node*)malloc(sizeof(Node));
	L->Next = NULL;
	int n, a, e;
	while (scanf("%d", &n) != EOF)
	{
		if (n == 1)
		{
			scanf("%d %d", &a, &e);
			Insert(L, a, e);
		}
		else if (n == 2)
		{
			scanf("%d", &a);
			Delete(L, a);
		}
		else if (n == 0)
			Print(L);
	}
}
