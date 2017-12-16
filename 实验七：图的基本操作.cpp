/*
1）用邻接矩阵存储方式，表示下面的图，并输出。
2）由上面的邻接矩阵产生邻接表，并输出。
3）编程完成从顶点0开始的深度优先遍历和广度优先遍历。
*/
#include <stdio.h>
#include <stdlib.h>

#define MaxVertexNum 100
#define INFINITY 65535

typedef int Vertex;
typedef int WeightType;     //边的权值设为整数
typedef char DataType;      //顶点的数据存储

//边的定义
typedef struct ENode
{
	Vertex V1, V2;       //边的两个顶点
	WeightType Weight;   //边的权重
}*Edge;

//图的结点定义
typedef struct MNode
{
	int Nv;         //顶点数
	int Ne;         //边数
	WeightType Weight[MaxVertexNum][MaxVertexNum];   //邻接矩阵
}*MGraph;

//邻接点的定义
typedef struct AdjVNode
{
	Vertex AdjV;           //邻接点下标
	WeightType Weight;     //边权重
	struct AdjVNode *Next; //指向下一邻接点的指针
}*PtrToAdjVNode;

//顶点表头结点的定义
typedef struct VNode
{
	PtrToAdjVNode FirstEdge;   //边表头指针
}AdjList[MaxVertexNum];       

//图结点的定义
typedef struct LNode
{
	int Nv;     //顶点数
	int Ne;     //边数
	AdjList List;  //邻接表
}*LGraph;       //以邻接表方式存储图类型

//初始化邻接表图
LGraph CreateLGraph(int VertexNum)
{
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(LNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	//初始化邻接表表头
	for (V = 0; V < Graph->Nv; V++)
		Graph->List[V].FirstEdge = NULL;

	return Graph;
}


//初始化一个图
MGraph CreateMGraph(int VertexNum)
{
	//初始化一个有VertexNum个结点但没有边的图
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(MNode));  //建立图
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->Weight[V][W] = INFINITY;

	return Graph;
}

//将邻接矩阵转化成邻接表
void MGraphToLGraph(MGraph G,LGraph L)
{
	Vertex V, W;
	for (V = 0; V < G->Nv; V++)
	{
		for (W = 0; W < G->Nv; W++)
		{
			if (G->Weight[V][W] != 0)
			{
				PtrToAdjVNode NewNode = (PtrToAdjVNode)malloc(sizeof(AdjVNode));
				NewNode->AdjV = W;
				NewNode->Weight = G->Weight[V][W];
				//将V2插入V1的表头
				NewNode->Next = L->List[V].FirstEdge;
				L->List[V].FirstEdge = NewNode;
			}
		}
	}
}

//深度优先搜索
void DFS(Vertex Start, MGraph G,int Visit[])  
{
	Vertex V, W;
	V = Start;
	printf("%d  ", V);
	Visit[Start] = 1;
	for (W = 0; W < G->Nv; W++)
	{
		if (G->Weight[V][W] != 0 && Visit[W] == 0)
			DFS(W, G, Visit);
	}
}

//广度优先搜索
void BFS(Vertex Start, MGraph G)
{
	Vertex V, W;
	Vertex Queue[MaxVertexNum];
	int Visit[MaxVertexNum];
	int Rear = 0, Front = 0;
	Queue[Rear++] = Start;
	for (V = 0; V < G->Nv; V++)
		Visit[V] = 0;
	while (Rear != Front)
	{
		V = Queue[Front++];
		printf("%d  ", V);
		Visit[V] = 1;
		for (W = 0; W < G->Nv; W++)
		{
			if (G->Weight[V][W] != 0 && Visit[W] == 0)
			{
				Visit[W] = 1;
				Queue[Rear++] = W;
			}
		}
	}
}

//打印邻接矩阵
void PrintMGraph(MGraph G)
{
	Vertex V, W;
	printf("有向图G的邻接矩阵:\n");
	for (V = 0; V < G->Nv; V++)
	{
		for (W = 0; W < G->Nv; W++)
			printf("%d  ", G->Weight[V][W]);
		printf("\n");
	}
}

//打印邻接表
void PrintLGraph(LGraph L)
{
	PtrToAdjVNode P;
	Vertex V;
	for (V = 0; V < L->Nv; V++)
	{
		printf("%d:  ", V);
		for (P = L->List[V].FirstEdge; P; P = P->Next)
			printf("%d  ", P->AdjV);
		printf("\n");
	}
}

//主函数
int main()
{
	MGraph G = CreateMGraph(6);
	LGraph L = CreateLGraph(G->Nv);
	int A[MaxVertexNum][6] = {
    { 0,5,0,7,0,0 },
	{ 0,0,4,0,0,0 },
	{ 8,0,0,0,0,9 },
	{ 0,0,5,0,0,6 },
	{ 0,0,0,5,0,0 },
	{ 3,0,0,0,1,0 } };
	Vertex V, W;
	for (V = 0; V < 6; V++)
		for (W = 0; W < 6; W++)
			G->Weight[V][W] = A[V][W];

	PrintMGraph(G);
	MGraphToLGraph(G, L);
	PrintLGraph(L);
	int Visit[MaxVertexNum];
	for (V = 0; V < G->Nv; V++)
		Visit[V] = 0;
	printf("从顶点0开始的DFS:\n");
	DFS(0, G, Visit); printf("\n");
	printf("从顶点0开始的BFS:\n");
	BFS(0, G); printf("\n");
}
