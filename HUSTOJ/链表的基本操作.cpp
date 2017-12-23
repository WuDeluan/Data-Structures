/*
输入

输入数据只有一组，第一行有n+1个整数，第一个整数是这行余下的整数数目n，后面是n个整数。这一行整数是用来初始化列表的，并且输入的顺序与列表中的顺序相反，也就是说如果列表中是1、2、3那么输入的顺序是3、2、1。
第二行有一个整数m，代表下面还有m行。每行有一个字符串，字符串是“get”，“insert”，“delete”，“show”中的一种。如果是“get”或者“delete”，则其后跟着一个整数a，代表获得或者删除第a个元素；如果是“insert”，则其后跟着两个整数a和e，代表在第a个位置前面插入e；“show”之后没有整数。
输出

如果获取成功，则输出该元素；如果删除成功则输出“delete OK”；如果获取失败或者删除失败，则输出“get fail”以及“delete fail”。如果插入成功则输出“insert OK”，否则输出“insert fail”。如果是“show”则输出列表中的所有元素，如果列表是空的，则输出“Link list is empty”。注：所有的双引号均不输出。
样例输入

3 3 2 1
21
show
delete 1
show
delete 2
show
delete 1
show
delete 2
insert 2 5
show
insert 1 5
show
insert 1 7
show
insert 2 5
show
insert 3 6
show
insert 1 8
show
get 2
样例输出

1 2 3
delete OK
2 3
delete OK
2
delete OK
Link list is empty
delete fail
insert fail
Link list is empty
insert OK
5
insert OK
7 5
insert OK
7 5 5
insert OK
7 5 6 5
insert OK
8 7 5 6 5
7
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	int Number;
	struct Node *Next;
}*List,*Position;

void Add(List L, int X)
{
	Position P = L;
	Position Tmp = (Node*)malloc(sizeof(Node));
	Tmp->Number = X;
	Tmp->Next = L->Next;
	L->Next = Tmp;
}

int Get(List L, int a)
{
	Position P;
	int i;
	for (i = 0, P = L->Next; P; P = P->Next)
	{
		i++;
		if (i == a)
			return P->Number;
	}
	return -1;
}

int Delete(List L, int a)
{
	Position P, Q;
	int i;

	for (i = 0, P = L; P->Next; P = P->Next)
	{
		if (i == a - 1)
		{
			Q = P->Next;
			P->Next = Q->Next;
			free(Q);
			return 1;
	    }
		i++;
	}
	return -1;
}

int Insert(List L, int a, int e)
{
	Position P;
	Position Tmp = (Node*)malloc(sizeof(Node));
	Tmp->Number = e;
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

int Print(List L)
{
	Position P;
	if (L->Next)
	{
		for (P = L->Next; P; P = P->Next)
		{
			if (P->Next)
				printf("%d ", P->Number);
			else
				printf("%d\n", P->Number);
		}
		return 1;
	}
	else
		return -1;
}

int main()
{
	List L = (Node*)malloc(sizeof(Node));
	L->Next = NULL;
	int n, m, a, e;
	char s[10];
	scanf("%d", &n);
	while (n--)
	{
		scanf("%d", &m);
		Add(L, m);
	}
	scanf("%d", &n);
	while (n--)
	{
		scanf("%s", s);
		if (strcmp(s, "insert") == 0)
		{
			scanf("%d %d", &a, &e);
			m = Insert(L, a, e);
			(m == 1) ? printf("insert OK\n") : printf("insert fail\n");
		}
		else if (strcmp(s, "delete") == 0)
		{
			scanf("%d", &a);
			m = Delete(L, a);
			(m == 1) ? printf("delete OK\n") : printf("delete fail\n");
		}
		else if (strcmp(s, "get") == 0)
		{
			scanf("%d", &a);
			m = Get(L, a);
			(m != -1) ? printf("%d\n",m) : printf("get fail\n");
		}
		else if (strcmp(s, "show") == 0)
		{
			m = Print(L);
			if (m == -1)
				printf("Link list is empty\n");
		}
	}
}
