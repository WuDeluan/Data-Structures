#include <stdio.h>
#include <string.h>
#define LeftChild(i)(2 * (i) + 1)

//插入排序
void InsertionSort(char(*A)[20], int N)
{
	int j, P;

	char Tmp[20], *p;
	for (P = 1; P < N; P++)
	{
		strcpy(Tmp, *(A + P));
		for (j = P; j > 0 && strcmp(Tmp, *(A + j - 1)) < 0; j--)
			strcpy(*(A + j), *(A + j - 1));
		strcpy(*(A + j), Tmp);
	}
}

//堆排序
void PercDown(char(*A)[20], int i, int N)
{
	int Child;
	char Tmp[20];

	for (strcpy(Tmp, *(A + i)); LeftChild(i) < N; i = Child)
	{
		Child = LeftChild(i);
		if (Child != N - 1 && strcmp(*(A + Child + 1), *(A + Child)) > 0)
			Child++;
		if (strcmp(Tmp, *(A + Child)) < 0)
			strcpy(*(A + i), *(A + Child));
		else
			break;
	}
	strcpy(*(A + i), Tmp);
}

void HeapSort(char(*A)[20], int N)
{
	int i;
	char Tmp[20];
	for (i = N / 2; i >= 0; i--)
		PercDown(A, i, N);
	for (i = N - 1; i > 0; i--)
	{
		strcpy(Tmp, *A);
		strcpy(*A, *(A + i));
		strcpy(*(A + i), Tmp);
		PercDown(A, 0, i);
	}
}

//希尔排序
void ShellSort(char (*A)[20], int N)
{
	int i, j, k, Increment;
	char Tmp[20];
	for (Increment = N / 2; Increment > 0; Increment /= 2)
		for (i = Increment; i < N; i++)
		{
			strcpy(Tmp, *(A + i));
			for (j = i; j >= Increment; j -= Increment)
				if (strcmp(Tmp, *(A + j - Increment)) < 0)
					strcpy(*(A + j), *(A + j - Increment));
				else

					break;
			strcpy(*(A + j), Tmp);
		}
}

void Merge(char (*A)[20],char (*Tmp)[20],int Lpos,int Rpos,int RightEnd)
{
	int i,LeftEnd,NumElements,TmpPos;

	LeftEnd = Rpos - 1;
	TmpPos = Lpos;
	NumElements = RightEnd - Lpos + 1;

	while(Lpos <= LeftEnd && Rpos <= RightEnd)
	{
		if(strcmp(*(A + Lpos),*(A + Rpos)) == 0 || strcmp(*(A + Lpos),*(A + Rpos)) < 0)
			strcpy(*(Tmp + TmpPos++),*(A + Lpos++));
		else
			strcpy(*(Tmp + TmpPos++),*(A + Rpos++));
	}

	while(Lpos <= LeftEnd)
		strcpy(*(Tmp + TmpPos++),*(A + Lpos++));
	while(Rpos <= RightEnd)
		strcpy(*(Tmp + TmpPos++),*(A + Rpos++));

	for(i = 0;i < NumElements;i++,RightEnd--)
		strcpy(*(A + RightEnd),*(Tmp + RightEnd));
}

//归并排序
void MSort(char (*A)[20],char (*Tmp)[20],int Left,int Right)
{
	int Center;

	if(Left < Right)
	{
		Center = (Left + Right) / 2;
		MSort(A,Tmp,Left,Center);
		MSort(A,Tmp,Center + 1,Right);
		Merge(A,Tmp,Left,Center + 1,Right);
	}
}

void MergeSort(char (*A)[20],int N)
{
	char (*Tmp)[20];

	Tmp = (char (*)[20])malloc(sizeof(char (*)[20]) * N);
	if(Tmp != NULL)
	{
		MSort(A,Tmp,0,N - 1);
		free(Tmp);
	}
}

int main()
{
	char a[][20] = { "while","if","else","do","for" ,"switch","case"};
	InsertionSort(a, 7);
	return 0;
}
