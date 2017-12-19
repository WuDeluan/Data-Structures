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
typedef int WeightType;     //weigh of edges
typedef char DataType;      //store data

//defination of edge
typedef struct ENode
{
	Vertex V1, V2;       //two vertices of each edge
	WeightType Weight;   //weight of edge
}*Edge;

//defination of adjacency-matrix-graph node
typedef struct MNode
{
	int Nv;         //number of vertices
	int Ne;         //number of edges
	WeightType Weight[MaxVertexNum][MaxVertexNum];   //adjacency matrix
}*MGraph;

//defination of adjacency node
typedef struct AdjVNode
{
	Vertex AdjV;           //index of vertex
	WeightType Weight;     //weight of edge
	struct AdjVNode *Next; //pointer points to next node
}*PtrToAdjVNode;


typedef struct VNode
{
	PtrToAdjVNode FirstEdge;   
}AdjList[MaxVertexNum];       

//defination of adjacency-matrix-graph node
typedef struct LNode
{
	int Nv;     //number of vertices
	int Ne;     //number of edges
	AdjList List;  //adjacency list
}*LGraph;       

//creat a adjacency-list-graph
LGraph CreateLGraph(int VertexNum)
{
	Vertex V;
	LGraph Graph;

	Graph = (LGraph)malloc(sizeof(LNode));
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	//creat a head of list
	for (V = 0; V < Graph->Nv; V++)
		Graph->List[V].FirstEdge = NULL;

	return Graph;
}


//creat a adjacency-matrix-graph
MGraph CreateMGraph(int VertexNum)
{
	//create a graph with numbers of vertexNum nodes and without edge
	Vertex V, W;
	MGraph Graph;

	Graph = (MGraph)malloc(sizeof(MNode));  //build graph
	Graph->Nv = VertexNum;
	Graph->Ne = 0;

	for (V = 0; V < Graph->Nv; V++)
		for (W = 0; W < Graph->Nv; W++)
			Graph->Weight[V][W] = INFINITY;

	return Graph;
}

//matrix graph to adjacency-list-graph
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
				//insert newnode to head of list
				NewNode->Next = L->List[V].FirstEdge;
				L->List[V].FirstEdge = NewNode;
			}
		}
	}
}

//DFS
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

//BFS
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

//print adjacency-matrix-graph
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

//print adjacenccy-list-graph
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
