#ifndef GUIDE_CLASS_H
#define GUIDE_CLASS_H
#include "Guide_program.h"

class Guide
{
private:
	MGraph Graph;
	Table T[MaxVertexNum];
public:
	void InitMGraph(int VertexNum)
	{
		Vertex V, W;

		Graph = (MGraph)malloc(sizeof(MNode));
		Graph->Nv = VertexNum;

		for (V = 0; V < Graph->Nv; V++)
			for (W = 0; W < Graph->Nv; W++)
				Graph->Weight[V][W] = INFINITY;
	};

	void BuildMGraph(int VertexNum)
	{
		char Name[200], Introduction[200];
		int Index;
		InitMGraph(VertexNum);
		int Matrix[MaxVertexNum][MaxVertexNum] = {
			{ 0,5,0,7,0,4 },
		{ 5,4,0,0,0,0 },
		{ 0,4,0,3,0,0 },
		{ 7,0,3,0,4,1 },
		{ 0,0,0,4,0,2 },
		{ 4,0,0,1,2,0 } };
		ifstream file("D:\\aaa.txt");
		while (!file.eof()) 
		{
			file >> Index;
			file >> Name;
			file >> Introduction;
			strcpy(Graph->Data[Index - 1].Name, Name);
			strcpy(Graph->Data[Index - 1].Introduction, Introduction);
		}
		file.close();
		Vertex V, W;
		for (V = 0; V < VertexNum; V++)
		{
			for (W = 0; W < VertexNum; W++)
			{
				Graph->Weight[V][W] = Matrix[V][W];
			}
		}
	};

	Vertex Search(char *Name)
	{
		Vertex V;
		for (V = 0; V < Graph->Nv; V++)
		{
			if (strcmp(Graph->Data[V].Name, Name) == 0)
				return V;
		}
	};

	void Introduction()
	{
		char Name[20];
		cout << "请输入要查询的景点名称：";
		cin >> Name;
		Vertex V = Search(Name);
		cout << Graph->Data[V].Introduction << endl;
	};

	void Add()
	{
		char Name[200], Introduction[200];
		Vertex V, W;
		WeightType Weight;
		int i;
		cout << "请输入地点名称：";
		cin >> Name;
		cout << "请输入地点简介：";
		cin >> Introduction;
		strcpy(Graph->Data[Graph->Nv].Name, Name);
		strcpy(Graph->Data[Graph->Nv].Introduction, Introduction);
		for (i = 0; i <= Graph->Nv; i++)
		{
			Graph->Weight[i][Graph->Nv] = 0;
			Graph->Weight[Graph->Nv][i] = 0;
		}

		cout << "请输入与该地点相邻的景点数：";
		cin >> i;
		while (i--)
		{
			cout << "请分别输入相邻景点的名称及距离：";
			cin >> Name;
			cin >> Weight;
			V = Search(Name);
			Graph->Weight[Graph->Nv][V] = Weight;
			Graph->Weight[V][Graph->Nv] = Weight;
		}
		Graph->Nv++;
	};

	void Delete()
	{
		char Name[200];
		Vertex V, W;
		cout << "请输入待删除景点的名称：";
		cin >> Name;
		V = Search(Name);
		for (W = 0; W < Graph->Nv; W++)
		{
			Graph->Weight[W][V] = 0;
			Graph->Weight[V][W] = 0;
		}
		strcpy(Graph->Data[V].Name, "Delete");
	};

	void InitTable(Vertex Start)
	{
		int i;
		for (i = 0; i < Graph->Nv; i++)
		{
			T[i].Distence = INFINITY;
			T[i].Known = 0;
			T[i].Path = -1;
		}
		T[Start].Distence = 0;
	};

	Vertex FindMinDist()
	{
		Vertex MinV, V;
		int MinDist = INFINITY;

		for (V = 0; V < Graph->Nv; V++)
		{
			if (T[V].Known == 0 && T[V].Distence < MinDist)
			{
				MinDist = T[V].Distence;
				MinV = V;
			}
		}
		if (MinDist < INFINITY)
			return MinV;
		else
			return -1;
	}

	void PrintPath(Vertex V)
	{
		if (T[V].Path != -1)
		{
			PrintPath(T[V].Path);
			cout << "to ";
		}
		cout << Graph->Data[V].Name << " ";
	};

	void Dijkstra()
	{
		Vertex V, W;
		for (;;)
		{
			V = FindMinDist();
			if (V == -1)
				break;
			T[V].Known = 1;
			for (W = 0; W < Graph->Nv; W++)
			{
				if (Graph->Weight[V][W] != 0 && T[W].Known == 0)
					if (T[V].Distence + Graph->Weight[V][W] < T[W].Distence)
					{
						T[W].Distence = T[V].Distence + Graph->Weight[V][W];
						T[W].Path = V;
					}
			}
		}
	};

	void MinDis()
	{
		Vertex Start, V;
		char Name[200];
		cout << "请输入您的当前位置：";
		cin >> Name;
		Start = Search(Name);
		cout << "请输入您想要到达的景点：";
		cin >> Name;
		V = Search(Name);
		InitTable(Start);
		Dijkstra();
		PrintPath(V);
		cout << endl;
	};

	void PrintMGraph()
	{
		Vertex V, W;
		cout << "有向图G的邻接矩阵:" << endl;
		for (V = 0; V < Graph->Nv; V++)
		{
			for (W = 0; W < Graph->Nv; W++)
				cout << Graph->Weight[V][W] << "  ";
			cout << endl;
		}
	};//测试用
};

#endif 
