#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
typedef int ElementType;


typedef struct List
{
	ElementType Data[MaxSize];
	int Length;
};

void CreatList(List *&L, ElementType a[], int n)
{
	int i;
	L = (List*)malloc(sizeof(List));
	for (i = 0; i < n; i++)
		L->Data[i] = a[i];
	L->Length = n;
}

void Insert(List *L, ElementType X)
{
	int i;
	for (i = L->Length - 1; i > 0; i--)
		L->Data[i] = L->Data[i - 1];
	L->Data[0] = X;
}


int Find(List *L, int i,ElementType &X)
{
	int j;
	if (i < 0 || i > L->Length)
		return 0;
	X = L->Data[i - 1];
	for (j = i - 1; j > 0; j--)
		L->Data[j] = L->Data[j - 1];
	L->Data[0] = X;
}

int main()
{
	List *L;
	int a[5] = { 1,2,3,4,5 },X;
	CreatList(L, a, 5);
	Find(L, 2, X);
	Insert(L, 6);
	for (int i = 0; i < 5; i++)
		printf("%d ", L->Data[i]);
}

/*
#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node 
{
	ElementType Element;
	struct Node *Next;
}*PtrToNode;

typedef PtrToNode List;
typedef PtrToNode Position;

void CreatList(List L, ElementType a[], int n)
{
	int i;
	Position P, TmpCell;
	L->Next = NULL;
 	P = L;
	for (i = 0; i < n; i++)
	{
		TmpCell = (PtrToNode)malloc(sizeof(Node));
		TmpCell->Element = a[i];
		TmpCell->Next = NULL;
		P->Next = TmpCell;
		P = TmpCell;
	}
}
void Insert(List L, ElementType X)
{
	Position TmpCell;
	TmpCell = (PtrToNode)malloc(sizeof(Node));
	TmpCell->Element = X;
	TmpCell->Next = L->Next;
	L->Next = TmpCell;
}

void Find(List L, int i,ElementType &X)
{
	int k = 0;
	Position P, TmpCell;
	for (P = L->Next; P; P = P->Next)
	{
		k++;
		if (k == i - 1)
		{
		    X = P->Next->Element;
			TmpCell = P->Next;
			break;
		}		
	}
	P->Next = P->Next->Next;
	TmpCell->Next = L->Next;
	L->Next = TmpCell;
}

int main()
{
	int a[5] = { 1,2,3,4,5 }, X;
	List L = (PtrToNode)malloc(sizeof(Node));
	CreatList(L, a, 5);
	Find(L, 2, X);
	Insert(L, 6);
	Position P;
	for (P = L->Next; P; P = P->Next)
		printf("%d ", P->Element);
}
*/
