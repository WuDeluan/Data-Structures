/*
输入

输入数据只有一组，有很多行。每行的格式可能是下列一种：
insert a name
delete name
show
search name
其中 a 是一个整数，代表在第a个名字前插入名字。name是一个姓名，只包含英文字母的大小写，每个名字不超过30个字符。
输入保证不会插入列表中已经存在的姓名，不会删除列表中不存在的姓名，也不会搜索列表中不存在的姓名。
输出

起始时，列表是空的。只输出show和search name 的结果。show将列表中的姓名全部输出，search只输出找到该名字的序号（从1开始）。每次输出占一行，姓名间用空格隔开。如果列表中没有名字了，show时也要输出一个空行。
样例输入
*/
insert 1 Stuart
insert 2 Bernadette
show
search Stuart
delete Stuart
show
insert 2 Stuart
show
insert 1 Amy
insert 2 Leslie
insert 3 Stephanie
show
delete Leslie
show
search Stuart
样例输出

Stuart Bernadette
1
Bernadette
Bernadette Stuart
Amy Leslie Stephanie Bernadette Stuart
Amy Stephanie Bernadette Stuart
4
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct Node
{
	char name[20];
	struct Node *Next;
}*List, *Position;

int Search(List L, char* s)
{
	Position P;
	int i;
	for (i = 0, P = L->Next; P; P = P->Next)
	{
		i++;
		if (strcmp(P->name,s) == 0)
			return i;
	}
	return -1;
}

int Delete(List L, char* s)
{
	Position P, Q;

	for (P = L; P->Next; P = P->Next)
	{
		if (strcmp(P->Next->name,s) == 0)
		{
			Q = P->Next;
			P->Next = Q->Next;
			free(Q);
			return 1;
		}
	}
	return -1;
}

int Insert(List L, int a, char* s)
{
	Position P;
	Position Tmp = (Node*)malloc(sizeof(Node));
	strcpy(Tmp->name, s);
	Tmp->Next = NULL;
	int i;
	for (i = 0, P = L; P; P = P->Next)
	{
		if (i == a - 1)
		{
			Tmp->Next = P->Next;
			P->Next = Tmp;
			return 1;
		}
		i++;
	}
	return -1;
}

void Print(List L)
{
	Position P;
	if (L->Next)
	{
		for (P = L->Next; P; P = P->Next)
		{
			if (P->Next)
				printf("%s ", P->name);
			else
				printf("%s\n", P->name);
		}
	}
	else
		printf("\n");
}

int main()
{
	List L = (Node*)malloc(sizeof(Node));
	L->Next = NULL;
	char s[20];
	int a, m;
	while (scanf("%s",s) != EOF)
	{
		if (strcmp(s , "insert") == 0)
		{
			scanf("%d %s", &a, s);
			Insert(L, a, s);
		}
		else if (strcmp(s , "delete") == 0)
		{
			scanf("%s", s);
			Delete(L, s);
		}
		else if (strcmp(s , "search") == 0)
		{
			scanf("%s", s);
			m = Search(L, s);
			if (m != -1)
				printf("%d\n", m);
		}
		else if (strcmp(s , "show") == 0 )
			Print(L);
	}
}
