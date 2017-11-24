/*
题目描述

将一个长度最多为30位数字的十进制非负整数转换为二进制数输出。
输入

多组数据，每行为一个长度不超过30位的十进制非负整数。
（注意是10进制数字的个数可能有30个，而非30bits的整数）
输出

每行输出对应的二进制数*/

#include <stdio.h>
#include <stdlib.h>
#define MaxSize 30

int main()
{
	char c[30];
	int i,j,k,n;
	while (scanf("%s", &c) != EOF) {
		int a[30], b[200];
		for (i = 0; i < 200; i++)
			b[i] = 0;
		char *p;
		for (p = c,i = 0; *p != '\0'; p++)
		{
			a[i++] = *p - '0';
		}
		k = 0;
		while (1) {
			b[k++] = a[i - 1] % 2;
			if (k == 200)
				break;
			for (j = 0; j < i; j++)
			{
				int t = a[j];
				a[j] = t / 2;
				a[j + 1] += (t % 2) * 10;
			}
		}

		while (b[k - 1] == 0) {
			k--;
		}
		for (j = k - 1; j >= 0; j--)
			printf("%d", b[j]);
		printf("\n");
	}
}
