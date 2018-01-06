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
		char Name[200], Introduction[200];  //存储景点名字、简介
		int Index, VertexNum;  //存储景点编号、景点总数
		Vertex V, W;
		WeightType Weight; //存储道路长度
		ifstream Path("D:\\Path.txt"); //打开存储道路信息的文本文档
		Path >> VertexNum;  //读入景点总数
		InitMGraph(VertexNum); //初始化一个有VertexNum个结点的图
		for (V = 0; V < VertexNum; V++) //读入所有道路长度，并将信息存入图中
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
		ifstream file("D:\\Points.txt"); //打开存储景点信息的文本文档
		while (!file.eof())
		{
			file >> Index; //读入景点编号
			file >> Name; //读入景点名称
			file >> Introduction; //读入景点简介
			if (file.eof())
				break;
			//将信息存入图中
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
	//增加景点信息
	int AddPoint()
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
		//初始化该景点在邻接矩阵中的权值
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
			//更改邻接矩阵对应的权值，即道路长度
			Graph->Weight[Graph->Nv][V] = Weight;
			Graph->Weight[V][Graph->Nv] = Weight;
		}
		Graph->NewNv++;
		return 0;
	};
	//删除景点信息
	int DeletePoint()
	{
		char Name[200];
		Vertex V, W;
		cout << "\t\t\t请输入待删除景点的名称：";
		cin >> Name;
		V = Search(Name);
		if (V == -1)
			return -1;
		//将该景点所有道路置零
		for (W = 0; W < Graph->Nv; W++)
		{
			Graph->Weight[W][V] = 0;
			Graph->Weight[V][W] = 0;
		}
		strcpy(Graph->Data[V].Name, "Delete"); //标记该景点为Delete
		Graph->NewNv--;
		return 0;
	};
	//增加道路信息
	int AddLoad()
	{
		char Name1[200], Name2[200];
		Vertex V, W;
		WeightType Weight;
		int i;
		cout << "\t\t\t请输入道路两端的景点名称：";
		cin >> Name1;
		cin >> Name2;
		cout << "\t\t\t请输入道路长度：";
		cin >> Weight;
		V = Search(Name1);
		W = Search(Name2);
		if (V != -1 && W != -1)//输入的两个景点存在
		{
				Graph->Weight[V][W] = Weight; //保存道路信息
				Graph->Weight[W][V] = Weight;
				return 0;
		}
		return -1;
	};
	//删除道路信息
	int DeleteLoad()
	{
		char Name1[200], Name2[200];
		Vertex V, W;
		WeightType Weight;
		int i;
		cout << "\t\t\t请输入道路两端的景点名称：";
		cin >> Name1;
		cin >> Name2;
		V = Search(Name1);
		W = Search(Name2);
		if (V != -1 && W != -1)//输入的两个景点存在
		{
			Graph->Weight[V][W] = 0; //删除道路信息
			Graph->Weight[W][V] = 0;
			return 0;
		}
		return -1;
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
			V = FindMinDist(); //找到图中位置结点的最小距离
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
	void MinDist(Vertex Start, Vertex End)
	{
		InitTable(Start);
		Dijkstra();
		cout << "\n\t最短线路：";
		PrintPath(End);
		cout << endl;
	}
	//若Mark为-1，输出所有路径，否则，输出经过编号为Mark的景点的路径
	void AllRoad(Vertex Start, MGraph G, Vertex Final, Vertex Mark) {
		Vertex V, Q, X;                                   //操纵变量
		int k, y, i = 0, t, num = 0;
		stack<Vertex>SAll;
		//输出路径辅助变量
		int Visit[1000] = { 0 };                               //访问标记
		int loop[10000] = { 0 };                               //两点通路
		int load[100] = { 0 };                                 //输出路径
		V = Start;
		SAll.push(V);                                  //起点入栈
		load[i++] = V;                                 //记录首节点
		Visit[Start] = 1;                              //起点节点访问标记
		while (!SAll.empty()) {                        //栈为空时循环结束
			V = SAll.top();                            //栈顶元素开始遍历
			for (Q = 0; Q < G->Nv; Q++) {                //遍历节点
				if (G->Weight[V][Q] != 0 && Visit[Q] == 0 && loop[V * 100 + Q] == 0) {
					SAll.push(Q);
					Visit[Q] = 1;
					loop[V * 100 + Q] = 1;
					V = Q;                             //访问节点变换
					load[i++] = V;                     //记录节点
					Q = 0;                             //归为首节点
				}
				if (V == Final)                        //访问至目标节点，遍历中断
					break;
			}
			if (V == Final)
			{  //输出路径
				if (Mark != -1)
				{
					for (k = 0; k < i; k++)
					{
						if (load[k] == Mark)
						{
							t = 1;
							break;
						}
					}
					if (t == 1)
					{
						cout << ++num << " ";
						for (k = 0; k < i; k++)
							cout << G->Data[load[k]].Name << " ";
						cout << endl;
					}
					t = 0;
				}
				else
				{
					cout << ++num << " ";
					for (k = 0; k < i; k++)
						cout << G->Data[load[k]].Name << " ";
					cout << endl;
				}
				Visit[V] = 0;
				SAll.pop();                           ////输出路径或该节点找不到下一个符合条件节点，访问上一个节点
				i--;
			}
			else {
				X = SAll.top();
				if (X != Start) {
					SAll.pop();
					Visit[X] = 0;
					for (y = 0; y < G->Nv; y++) {
						if (y != load[i - 3])
							loop[X * 100 + y] = 0;
					}
					i--;
				}
				else {
					SAll.pop();
					Visit[X] = 0;
					i--;
				}
			}
		}
	}
	//保存数据
	void SaveFile()
	{
		Vertex V, W;
		ofstream Path("D:\\Path.txt"); //打开存储路径的文档，写入信息
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
		ofstream file("D:\\Points.txt"); //打开存储景点信息的文档，写入信息
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
