/*
题目描述

稀疏矩阵的存储不宜用二维数组存储每个元素，那样的话会浪费很多的存储空间。所以可以使用一个一维数组存储其中的非零元素。这个一维数组的元素类型是一个三元组，由非零元素在该稀疏矩阵中的位置（行号和列号对）以及该元组的值构成。
而矩阵转置就是将矩阵行和列上的元素对换。参考算法5.1中的具体做法，令mu和nu分别代表稀疏矩阵的行数和列数，不难发现其时间复杂度为O(mu×nu)。而当非零元的个数tu与mu×nu同数量级时，算法5.1的时间复杂度将上升至O(mu×nu2)。因此，需要采用快速的稀疏矩阵转置算法。
现在就请你实现一个快速的对稀疏矩阵进行转置的算法。以下是稀疏矩阵快速转置的算法描述：

输入

输入的第一行是两个整数r和c（r<200, c<200, r*c <= 12500），分别表示一个包含很多0的稀疏矩阵的行数和列数。接下来有r行，每行有c个整数，用空格隔开，表示这个稀疏矩阵的各个元素。
输出

输出为读入的稀疏矩阵的转置矩阵。输出共有c行，每行有r个整数，每个整数后输出一个空格。请注意行尾输出换行。
样例输入

6 7
0 12 9 0 0 0 0
0 0 0 0 0 0 0
-3 0 0 0 0 14 0
0 0 24 0 0 0 0
0 18 0 0 0 0 0
15 0 0 -7 0 0 0
样例输出

0 0 -3 0 0 15 
12 0 0 0 18 0 
9 0 0 24 0 0 
0 0 0 0 0 -7 
0 0 0 0 0 0 
0 0 14 0 0 0 
0 0 0 0 0 0 
*/

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
