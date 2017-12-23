/*
题目描述

计算两个矩阵的乘积，第一个是2*3矩阵，第二个是3*2矩阵，结果为一个2*2矩阵。
输入

输入包含多组数据，先输入一个2*3矩阵，再输入一个3*2矩阵。
输出

输出两个矩阵的乘积。
样例输入

1 1 1
1 1 1
1 1
1 1
1 1
样例输出

3 3
3 3
*/
#include <stdio.h>

int main()
{
	int a[2][3], b[3][2], c[2][2];
	int i, j, k;

	while (scanf("%d", &a[0][0]) != EOF)
	{
		for (i = 0; i < 2; i++)
			for (j = 0; j < 3; j++)
				if(i != 0 || j != 0)
				   scanf("%d", &a[i][j]);

		for (i = 0; i < 3; i++)
			for (j = 0; j < 2; j++)
				scanf("%d", &b[i][j]);

		for (i = 0; i < 2; i++)
			for (j = 0; j < 2; j++)
				c[i][j] = 0;

		for (i = 0; i < 2; i++)
			for (j = 0; j < 2; j++)
				for (k = 0; k < 3; k++)
					c[i][j] += a[i][k] * b[k][j];

		for (i = 0; i < 2; i++)
		{
			for (j = 0; j < 2; j++)
			{
				if (j < 1)
					printf("%d ", c[i][j]);
				else
					printf("%d\n", c[i][j]);
			}

		}
	}
}
