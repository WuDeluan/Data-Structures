#include <stdio.h>
#include <stdlib.h>
#define MaxSize 5

typedef int ElementType;
struct QueueRecord
{
	int Front;
	int Rear;
	ElementType Data[MaxSize];
};
typedef struct QueueRecord *Queue;

void MakeEmpty(Queue Q)
{
	Q->Front = 0;
	Q->Rear = 0;
}

int Enqueue(Queue Q, ElementType X)
{
	if ((Q->Rear + 1) % MaxSize == Q->Front)
		return -1;
Q->Rear = (Q->Rear + 1) % MaxSize;
	Q->Data[Q->Rear] = X;
	return 0;
}

int Dequeue(Queue Q, ElementType &X)
{
	if (Q->Front == Q->Rear)
		return -1;
Q->Front = (Q->Front + 1) % MaxSize;
	X = Q->Data[Q->Front];
}

/*int main()
{
	Queue Q;
	int X;
	Q = (Queue)malloc(sizeof(QueueRecord));
	MakeEmpty(Q);
	Enqueue(Q, 1);
	Enqueue(Q, 2);
	Enqueue(Q, 3);
	Enqueue(Q, 4);
	Dequeue(Q, X);
	printf("%d\n", X);
	Dequeue(Q, X);
	printf("%d\n", X);
	Dequeue(Q, X);
	printf("%d\n", X);
	Enqueue(Q, 5);
}*/
