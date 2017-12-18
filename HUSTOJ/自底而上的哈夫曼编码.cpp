/*
在通讯领域，经常需要将需要传送的文字转换成由二进制字符组成的字符串。在实际应用中，由于总是希望被传送的内容总长尽可能的短，如果对每个字符设计长度不等的编码，且让内容中出现次数较多的字符采用尽可能短的编码，则整个内容的总长便可以减少。另外，需要保证任何一个字符的编码都不是另一个字符的编码前缀，这种编码成为前缀编码。
而赫夫曼编码就是一种二进制前缀编码，其从叶子到根（自底向上）逆向求出每个字符的算法可以表示如下：

在本题中，读入n个字符所对应的权值，生成赫夫曼编码，并依次输出计算出的每一个赫夫曼编码。

输入

输入的第一行包含一个正整数n，表示共有n个字符需要编码。其中n不超过100。
第二行中有n个用空格隔开的正整数，分别表示n个字符的权值。
输出

共n行，每行一个字符串，表示对应字符的赫夫曼编码。
样例输入

8
5 29 7 8 14 23 3 11
样例输出

0110
10
1110
1111
110
00
0111
010
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	unsigned int weight;
	unsigned int parent, lchild, rchild;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;

void Select(HuffmanTree *HT, int n, int &s1, int &s2)
{
	int m1, m2, j;
	m1 = m2 = 20000;     /* m1、m2中存放两个无父结点且结点权值最小的两个结点 */
	/* 找出所有结点中权值最小、无父结点的两个结点，并合并之为一颗二叉树 */
	for (j = 1; j <= n; j++)
	{
		if ((*HT)[j].weight < m1 && (*HT)[j].parent == 0)
		{
			m2 = m1;
			s2 = s1;
			m1 = (*HT)[j].weight;
			s1 = j;
		}
		else if ((*HT)[j].weight < m2 && (*HT)[j].parent == 0)
		{
			m2 = (*HT)[j].weight;
			s2 = j;
		}
	}
 }

void HuffumanCoding(HuffmanTree *HT, HuffmanCode *HC, int *w, int n)
{
	int m, i, s1, s2, start, c, f;
	HuffmanTree p;
	
	if (n <= 1)
		return;
	m = 2 * n - 1;
	*HT = (HuffmanTree)malloc(sizeof(HTNode) * (m + 1));
	for (p = *HT + 1, i = 1; i <= n; ++i, ++p, ++w)
	{
		(*p).weight = *w;
		(*p).parent = (*p).lchild = (*p).rchild = 0;
	}
	
	for (; i <= m; ++i, ++p)
		(*p).parent = 0;
	for (i = n + 1; i <= m; ++i)
	{
		Select(HT, i - 1, s1, s2);
		(*HT)[s1].parent = (*HT)[s2].parent = i;
		(*HT)[i].lchild = s1; 
		(*HT)[i].rchild = s2;
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
	}
	*HC = (HuffmanCode)malloc(sizeof(char*) * (n - 1));
	char * cd = (char*)malloc(sizeof(char) * n);
	cd[n - 1] = '\0';
	for (i = 1; i <= n; i++)
	{
		start = n - 1;
		for (c = i, f = (*HT)[i].parent; f != 0; c = f, f = (*HT)[f].parent)
		{
			if ((*HT)[f].lchild == c)
				cd[--start] = '0';
			else
				cd[--start] = '1';
		}
		(*HC)[i] = (char*)malloc(sizeof(char) * (n - start));
		strcpy((*HC)[i], &cd[start]);
	}
	free(cd);
}

int main()
{
	int n, m, w[105], k = 0, i;
	HuffmanTree HT = (HuffmanTree)malloc(sizeof(HTNode));
	HuffmanCode HC = (HuffmanCode)malloc(sizeof(char*));
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d", &m);
		w[k++] = m;
	}
	HuffumanCoding(&HT, &HC, w, k);
	for(i = 1;i <= k;i++)
	   printf("%s ", *(HC + i));
	return 0;
}
