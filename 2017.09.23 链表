#include <stdio.h>
#include <stdlib.h>

struct Node;
typedef struct Node *PtrToNode;
typedef PtrToNode List;
typedef PtrToNode Position;

struct Node
{
	int Element;
	Position Next;
};

void Delete(int X, List L)
{
	Position P, TmpCell;

	P = L->Next;
	while (P->Next != NULL && P->Next->Element != X)
		P = P->Next;

	if (P->Next)
	{
		TmpCell = P->Next;
		P->Next = TmpCell->Next;
		free(TmpCell);
	}

}

int CreatList(List &L, int a[], int n)
{
	L = (Node*)malloc(sizeof(Node));
	L->Next = NULL;
	Position P, TmpCell;
	P = L;
	for (int i = 0; i < n; i++)
	{
		TmpCell = (Node*)malloc(sizeof(Node));
		TmpCell->Next = NULL;
		TmpCell->Element = a[i];
		P->Next = TmpCell;	
		P = TmpCell;
	}
	if (L->Next)
		return 0;
	else
		return -1;
}

void PrintLots(List L, List P)
{
	Position K1,K2;
	for (K1 = P->Next; K1; K1 = K1->Next)
	{
		int i = 0;
		for (K2 = L->Next; K2; K2 = K2->Next)
		{
			i++;
			if (i == K1->Element)
			{
				printf("%d ", K2->Element);
				break;
			}
		}
	}
}

void Insert(List L, int X)
{
	Position TmpCell = (Node*)malloc(sizeof(Node));
	TmpCell->Element = X;
	TmpCell->Next = NULL;
	Position P = L;
	while (P->Next)
		P = P->Next;
	P->Next = TmpCell;
}

List Union(List L1, List L2)
{
	List L3;
	L3 = (Node*)malloc(sizeof(Node));
	L3->Next = NULL;
	Position P1, P2;
	P1 = L1->Next;
	P2 = L2->Next;
	while (P1 != NULL && P2 != NULL)
	{
		if (P1->Element <= P2->Element)
		{
			Insert(L3, P1->Element);
			P1 = P1->Next;
		}
		else if (P1->Element > P2->Element)
		{
			Insert(L3, P2->Element);
			P2 = P2->Next;
		}
	}
	while (P1)
	{
		Insert(L3, P1->Element);
		P1 = P1->Next;
	}
	while (P2)
	{
		Insert(L3, P2->Element);
		P2 = P2->Next;
	}
	return L3;
}

List Intersection(List L1, List L2)
{

	List L3;
	L3 = (Node*)malloc(sizeof(Node));
	L3->Next = NULL;
	Position P1, P2;
	for (P1 = L1->Next; P1; P1 = P1->Next)
		for (P2 = L2->Next; P2; P2 = P2->Next)
			if (P1->Element == P2->Element)
				Insert(L3, P1->Element);
	return L3;
}


int main()
{
	List L,P;
	int a[5] = { 2,4,6,8,10 };
	int b[10] = { 1,2,3,4,5,6,7,8,9,10};
	printf("%d\n", CreatList(P, b, 10));
	printf("%d\n", CreatList(L, a, 5));
/*	List K = Intersection(L, P);
	Position T;
	for (T = K->Next; T; T = T->Next)
		printf("%d ", T->Element);	*/
	List K = Union(L, P);
	/*Position T;
	for (T = K->Next; T; T = T->Next)
		printf("%d ", T->Element);*/
	return 0;
}
