#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 12500
typedef struct
{
	int i, j;
	int e;
}Triple;

typedef struct
{
	Triple data[MAXSIZE + 1];
	int mu, nu, tu;
}TSMatrix;

void FastTransposeMatrix(TSMatrix M, TSMatrix &T)
{
	int col, t, p, q;
	int num[200], cpot[200];
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	if (T.tu)
	{
		for (col = 1; col <= M.nu; ++col)
			num[col] = 0;
		for (t = 1; t <= M.tu; ++t)
			++num[M.data[t].j];
		cpot[1] = 1;
		for (col = 2; col <= M.nu; ++col)
			cpot[col] = cpot[col - 1] + num[col - 1];
		for (p = 1; p <= M.tu; ++p)
		{
			col = M.data[p].j;
			q = cpot[col];
			T.data[q].i = M.data[p].j;
			T.data[q].j = M.data[p].i;
			T.data[q].e = M.data[p].e;
			++cpot[col];
		}
	}
}

int main()
{
	int mu, nu;
	int i, j, e, k = 1;
	TSMatrix M, T;
	scanf("%d %d", &nu, &mu);
	M.mu = mu;
	M.nu = nu;
	M.tu = 0;
	for (i = 1; i <= nu; i++)
	{
		for (j = 1; j <= mu; j++)
		{
			scanf("%d", &e);
			if (e != 0)
			{
				M.data[k].i = i;
				M.data[k].j = j;
				M.data[k].e = e;
				M.tu++;
				k++;
			}				
		}
	}
	FastTransposeMatrix(M, T);
	k = 1;
	for (i = 1; i <= T.nu; i++)
	{	
		for (j = 1; j <= T.mu; j++)
		{
			if (T.data[k].i == i && T.data[k].j == j)
			{
				printf("%d ", T.data[k].e);
				k++;
			}
			else
				printf("0 ");
		}
		printf("\n");
	}
}
