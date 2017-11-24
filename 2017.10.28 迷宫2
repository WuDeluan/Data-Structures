/*
题目描述
小明置身于一个迷宫，请你帮小明找出从起点到终点的最短路程。
小明只能向上下左右四个方向移动。
输入包含多组测试数据。输入的第一行是一个整数T，表示有T组测试数据。
每组输入的第一行是两个整数N和M（1<=N,M<=100）。
接下来N行，每行输入M个字符，每个字符表示迷宫中的一个小方格。
字符的含义如下：
‘S’：起点
‘E’：终点
‘-’：空地，可以通过
‘#’：障碍，无法通过
输入数据保证有且仅有一个起点和终点。
输出
对于每组输入，输出从起点到终点的最短路程，如果不存在从起点到终点的路，则输出-1。*/
#include<stdio.h>  
#include<string.h>  
#include<queue>  
#include<iostream>  
using namespace std;

struct Node {
	int x;
	int y;
	int di;
	int step;
};

struct Maze {
	char arr[10][10];
};

Node NextPos(Node curpos)
{
	int i = curpos.di;
	switch (i) {
	case 1:curpos.x++; break;
	case 2:curpos.y++; break;
	case 3:curpos.x--; break;
	case 4:curpos.y--; break;
	};
	return curpos;
}

int Pass(Node curpos, Maze &maze)
{
	if (maze.arr[curpos.x][curpos.y] == '-' || maze.arr[curpos.x][curpos.y] == 'E')
	{
		maze.arr[curpos.x][curpos.y] = '#';
		return 1;
	}
	return 0;
}

int BFS(Maze maze, Node start, Node end)
{
	queue<Node> Q;
	Node curpos = start;
	Node nextpos;
	curpos.step = 0;
	curpos.di = 0;
	Q.push(curpos);
	while (!Q.empty()) {
		curpos = Q.front();
		curpos.di = 0;
		Q.pop();
		if (curpos.x == end.x && curpos.y == end.y)
			return curpos.step;
		else
		{
			curpos.step++;
			while (curpos.di < 4) {
				curpos.di++;
				nextpos = NextPos(curpos);
				if (Pass(nextpos, maze))
					Q.push(nextpos);
			}
		}
	}
	return -1;
}

int main()
{
	Maze maze;
	int i, j, k, n, m;
	Node start, end;
	scanf("%d", &k);
	while (k--)
	{
		scanf("%d %d", &n, &m);
		getchar();
		for (i = 0; i < n; i++)
		{
			for (j = 0; j < m; j++)
			{
				scanf("%c", &maze.arr[i][j]);
				if (maze.arr[i][j] == 'S')
				{
					start.x = i;
					start.y = j;
				}
				else if (maze.arr[i][j] == 'E')
				{
					end.x = i;
					end.y = j;
				}
			}
			getchar();
		}
		printf("%d\n", BFS(maze, start, end));
	}
}
