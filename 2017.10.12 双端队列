#include <stdio.h>
#include <stdlib.h>
#define MaxSize 5
struct DequeRecord;
typedef struct DequeRecord *Deque;
typedef int ElementType;

struct DequeRecord
{
	int Front;
	int Rear;
	ElementType Data[MaxSize];
};

void MakeEmpty(Deque D)
{
	D->Front = -1;
	D->Rear = MaxSize;
}

int Push(ElementType X, Deque D)
{
	if (D->Front + 1 == D->Rear)
		return -1;
	D->Data[++D->Front] = X;
	return 0;
}

int Pop(Deque D)
{
	if (D->Front == -1)
		return -1;
	D->Front--;
}

int Inject(ElementType X, Deque D)
{
	if (D->Rear - 1 == D->Front)
		return -1;
	D->Data[--D->Rear] = X;
	return 0;
}

int Eject(Deque D)
{
	if (D->Rear == MaxSize)
		return -1;
	D->Rear++;
}

int main()
{
	Deque D;
	D = (Deque)malloc(sizeof(DequeRecord));
	MakeEmpty(D);
	Push(1, D);
	Push(2, D);
	Inject(3, D);
	Inject(4, D);
	Push(5, D);
	Push(6, D);
	Pop(D);
	Pop(D);
	Pop(D);
	Pop(D);
	Push(7, D);
	Eject(D);
	Eject(D);
	Eject(D);
	Eject(D);
	Inject(8, D);
}

