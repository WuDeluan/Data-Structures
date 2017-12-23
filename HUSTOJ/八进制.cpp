/*
输入

输入包含若干十进制正整数。
输出

输出相应的八进制数，每个占一行。
样例输入

1
2
3
7
8
9
19
10020345
样例输出

1
2
3
7
10
11
23
46162771
提示
*/
#include <stdio.h>

void convertion(int Num)
{
	int e;
	int S[100], Top = -1;
	while (Num)
	{
		S[++Top] = Num % 8;
		Num /= 8;
	}
	while (Top != -1)
	{
		e = S[Top--];
		printf("%d", e);
	}
	printf("\n");
}

int main()
{
	int Num;
	while (scanf("%d", &Num) != EOF)
	   convertion(Num);
}
