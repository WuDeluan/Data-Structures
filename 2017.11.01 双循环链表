/*
输入

输入数据只有一组，包含很多行。每行有1~3个整数。第一个整数如果是0，则表示输出双向链表中的所有元素；第一个整数如果是1，表示插入1个整数，其后跟2个整数i、e代表在第i个位置插入e；第一个整数如果是2，表示删除1个整数，其后跟1个整数i，表示删除的位置为i。
起始双向链表为空表。保证链表中每个元素不会重复，同时所有的操作都合法。
输出

当需要输出双向链表中的所有元素时输出，每次输出一行。整数间用一个空格隔开*/
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node *Next;
	struct Node *Prev;
	int Data;
}*Position, *List;

Position Find(List L, int i)
{
	Position P = L;
	int j = 1;
	do {
		if (j == i)
			return P;
		j++;
		P = P->Next;
	} while (P != L);
	return NULL;
}

void Insert(List L, int i, int X)
{
	Position P;
	if (L->Next)
	{
		Position TmpCell = (Node*)malloc(sizeof(Node));
		TmpCell->Data = X;
		P = Find(L, i - 1);
		if (P) {
			TmpCell->Next = P->Next;
			P->Next->Prev = TmpCell;
			P->Next = TmpCell;
			TmpCell->Prev = P;
		}
	}
	else
	{
		L->Data = X;
		L->Next = L;
		L->Prev = L;
	}
}

void Delete(List &L, int i)
{
	Position P = Find(L, i);
	if (P) {
		P->Prev->Next = P->Next;
		P->Next->Prev = P->Prev;
		if (P == L)
			L = P->Next;
		free(P);
	}
}

void PrintAll(List L)
{
	Position P = L;
	do {
		printf("%d ", P->Data);
		P = P->Next;
	} while (P != L);
	printf("\n");
}

int main()
{
	int a, b, c;
	List L = (Node*)malloc(sizeof(Node));
	L->Next = L->Prev = NULL;
	while (scanf("%d", &a) != EOF)
	{
		switch (a) {
		case 0:PrintAll(L);
			break;
		case 1:scanf("%d %d", &b, &c);
			Insert(L, b, c);
			break;
		case 2:scanf("%d", &b);
			Delete(L, b);
			break;
		}
	}
}
