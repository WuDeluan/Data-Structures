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
