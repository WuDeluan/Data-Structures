/*
有一个 10 x 10 的迷宫，起点是‘S’，终点是‘E’，墙是‘#’，道路是空格。
一个机器人从起点走到终点。当机器人走到一个通道块，前面已经没有路可走时，
它会转向到当前面向的右手方向继续走。如果机器人能够过，则留下足迹‘*’，
如果走不通，则留下标记‘!’。
typedef struct{
int r, c;      // 以行号和列号作为“坐标位置”类型
}PosType;
typedef struct{
int ord;       // 通道块在路径上的序号
PosType seat; // 通道块在迷宫中的“坐标位置”
int di;            // 从此通道块走向下一通道块的“方向”
}SElemType;           // 定义堆栈元素的类型
typedef struct{
char arr[10][11];
}MazeType; // 定义迷宫类型（二维字符数组）
*/
#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
typedef struct 
{
	int r, c;
}PosType;

typedef struct {
	int ord;
	PosType seat;
	int di;
}SElemType;

typedef struct {
	char arr[10][10];
}MazeType;

typedef struct {
	int Top;
	SElemType Data[MaxSize];
}*Stack;

void InitStack(Stack S)
{
	S->Top = -1;
}

int StackEmpty(Stack S)
{
	return S->Top == -1;
}

int Push(Stack S, SElemType X)
{
	if (S->Top + 1 == MaxSize)
		return -1;
	S->Data[++S->Top] = X;
}

int Pop(Stack S,SElemType &X)
{
	if (S->Top == -1)
		return -1;
	X = S->Data[S->Top--];
}

int Pass(MazeType maze, PosType curpos)
{
	if (maze.arr[curpos.r][curpos.c] == ' '|| maze.arr[curpos.r][curpos.c] == 'S' || maze.arr[curpos.r][curpos.c] == 'E')
		return 1;
	else
		return 0;
}

int FootPrint(MazeType &maze, PosType &curpos)
{
	maze.arr[curpos.r][curpos.c] = '*';
	return 0;
}

PosType NextPos(PosType curpos, int i)
{
	switch (i) {
	case 1:
		curpos.c++;break;
	case 2:
		curpos.r++; break;
	case 3:
		curpos.c--; break;
	case 4:
		curpos.r--; break;
	}
	return curpos;
}

void MakePrint(MazeType &maze, PosType seat)
{
	maze.arr[seat.r][seat.c] = '!';
}

int MazePath(MazeType &maze, PosType start, PosType end)
{
	Stack S;
	S = (Stack)malloc(sizeof(Stack));
	PosType curpos;
	int curstep;
	SElemType e;
 	InitStack(S);
	curpos = start;
	curstep = 1;
	do {
		if (Pass(maze, curpos)) {
			FootPrint(maze, curpos);
			e.di = 1;
			e.ord = curstep;
			e.seat = curpos;
			Push(S, e);
			if (curpos.r == end.r && curpos.c == end.c)
				return 1;
			curpos = NextPos(curpos, e.di);
			curstep++;
		}
		else
		{
			if (!StackEmpty(S))
			{
				Pop(S, e);
				while (e.di == 4 && !StackEmpty(S))
				{
					MakePrint(maze, e.seat);
					Pop(S, e);
				}
				if (e.di < 4)
				{
					e.di++;
					Push(S, e);
					curpos = NextPos(e.seat, e.di);
				}
			}
		}
	} while (!StackEmpty(S));
	return 0;
}

int main()
{
	MazeType maze;
	PosType start, end;
	int i, j;
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			scanf("%c", &maze.arr[i][j]);
			if (maze.arr[i][j] == 'S')
			{
				start.r = i;
				start.c = j;
			}
			else if (maze.arr[i][j] == 'E')
			{
				end.r = i;
				end.c = j;
			}
		}
		getchar();
	}

	MazePath(maze, start, end);
	for (i = 0; i < 10; i++)
	{
		for (j = 0; j < 10; j++)
		{
			printf("%c", maze.arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}
