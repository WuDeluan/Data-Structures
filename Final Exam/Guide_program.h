#ifndef GUIDE_PROGRAM_H
#define GUIDE_PROGRAM_H
#include <iostream>
#include <string>
#include <fstream>
#include <string.h>
#include <stdlib.h>

using namespace std;

#define MaxVertexNum 100
#define INFINITY 65535

typedef int Vertex;
typedef int WeightType;     //边的权值设为整数

typedef struct
{
	char Name[200];
	char Introduction[200];
}DataType;

//图的结点定义
typedef struct MNode
{
	int Nv;         //顶点数
	int NewNv;
	WeightType Weight[MaxVertexNum][MaxVertexNum];   //邻接矩阵
	DataType Data[MaxVertexNum];
}*MGraph;

typedef struct TableNode
{
	int Known;
	int Distence;
	Vertex Path;
}Table;

#endif // !GUIDE_PROGRAM
