#ifndef GUIDE_CLASS_H
#define GUIDE_CLASS_H
#include "Guide_program.h"

class Guide
{
private:
	MGraph Graph;
	Table T[MaxVertexNum];
public:
	//返回图
	MGraph getGraph()
	{
		return Graph;
	};
	//初始化图
	void InitMGraph(int VertexNum)
	{
		Vertex V, W;

		Graph = (MGraph)malloc(sizeof(MNode));
		Graph->Nv = VertexNum;
		Graph->NewNv = VertexNum;

		for (V = 0; V < Graph->Nv; V++)
			for (W = 0; W < Graph->Nv; W++)
				Graph->Weight[V][W] = INFINITY;
	};
	//根据文件建立图
	void BuildMGraph()
	{
		char Name[200], Introduction[200];
		int Index, VertexNum;
		Vertex V, W;
		WeightType Weight;
		ifstream Path("D:\\Path.txt");
		Path >> VertexNum;
		InitMGraph(VertexNum);
		for (V = 0; V < VertexNum; V++)
		{
			for (W = 0; W < VertexNum; W++)
			{
				if (!Path.eof())
				{
					Path >> Weight;
					Graph->Weight[V][W] = Weight;
				}
			}
		}
		Path.close();
		ifstream file("D:\\Test.txt");
		while (!file.eof())
		{
			file >> Index;
			file >> Name;
			file >> Introduction;
			if (file.eof())
				break;
			strcpy(Graph->Data[Index - 1].Name, Name);
			strcpy(Graph->Data[Index - 1].Introduction, Introduction);
		}
		file.close();
	};
	//从图中查找某一景点，存在返回在图中的位置，否则返回-1
	Vertex Search(char *Name)
	{
		Vertex V;
		for (V = 0; V < Graph->Nv; V++)
		{
			if (strcmp(Graph->Data[V].Name, Name) == 0)
				return V;
		}
		return -1;
	};
	//增加结点信息
	int Add()
	{
		char Name[200], Introduction[200];
		Vertex V, W;
		WeightType Weight;
		int i;
		cout << "\t\t\t请输入地点名称：";
		cin >> Name;
		cout << "\t\t\t请输入地点简介：";
		cin >> Introduction;
		strcpy(Graph->Data[Graph->Nv].Name, Name);
		strcpy(Graph->Data[Graph->Nv].Introduction, Introduction);
		for (i = 0; i <= Graph->Nv; i++)
		{
			Graph->Weight[i][Graph->Nv] = 0;
			Graph->Weight[Graph->Nv][i] = 0;
		}

		cout << "\t\t\t请输入与该地点相邻的景点数：";
		cin >> i;
		while (i--)
		{
			cout << "\t\t\t请分别输入相邻景点的名称及距离：";
			cin >> Name;
			cin >> Weight;
			V = Search(Name);
			if (V == -1)
				return -1;
			Graph->Weight[Graph->Nv][V] = Weight;
			Graph->Weight[V][Graph->Nv] = Weight;
		}
		Graph->NewNv++;
		return 0;
	};
	//删除结点信息
	int Delete()
	{
		char Name[200];
		Vertex V, W;
		cout << "\t\t\t请输入待删除景点的名称：";
		cin >> Name;
		V = Search(Name);
		if (V == -1)
			return -1;
		for (W = 0; W < Graph->Nv; W++)
		{
			Graph->Weight[W][V] = 0;
			Graph->Weight[V][W] = 0;
		}
		strcpy(Graph->Data[V].Name, "Delete");
		Graph->NewNv--;
		return 0;
	};
	//初始化表格
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
	//Dijkstra查找最短距离
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
	//打印最短路径
	void PrintPath(Vertex V)
	{
		static int i = 0;
		if (T[V].Path != -1)
		{
			PrintPath(T[V].Path);
			cout << "-->";
		}
		cout << Graph->Data[V].Name << " ";
		i++;
		if (i % 4 == 0)
			cout << "\n\t\t   ";
	};
	//查找最短路径
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
	//最短路径函数
	void MinDist(Vertex Start,Vertex End)
	{
		InitTable(Start);
		Dijkstra();
		cout << "\n\t最短线路：";
		PrintPath(End);
		cout << endl;
	}
	//保存数据
	void SaveFile()
	{
		Vertex V, W;
		ofstream Path("D:\\Path.txt");
		Path << Graph->NewNv << endl;
		for (V = 0; V < Graph->NewNv; V++)
		{
			if (strcmp(Graph->Data[V].Name, "Delete") == 0)
				continue;
			for (W = 0; W < Graph->NewNv; W++)
			{
				if (strcmp(Graph->Data[W].Name, "Delete") == 0)
					continue;
				Path << Graph->Weight[V][W] << " ";
			}
			Path << endl;
		}
		Path.close();
		ofstream file("D:\\Test.txt");
		for (V = 0, W = 1; V < Graph->NewNv; V++)
		{
			if (strcmp(Graph->Data[V].Name, "Delete") == 0)
				continue;
			file << W << " ";
			file << Graph->Data[V].Name << " ";
			file << Graph->Data[V].Introduction << " " << endl;
			W++;
		}
		file.close();
	}
};

#endif 
