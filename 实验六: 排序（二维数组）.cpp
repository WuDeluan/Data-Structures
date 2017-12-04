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
		printf("%s ", (A + P));
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

int main()
{
	char a[][20] = { "while","if","else","do","for" ,"switch","case"};
	InsertionSort(a, 7);
	return 0;
}
