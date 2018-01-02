#include "Guide_class.h"

int main()
{
	Guide G;
	G.BuildMGraph(6);
	G.PrintMGraph();
	G.InitTable(1);
	G.MinDis();
	G.Add();
	G.PrintMGraph();
	G.Delete();
	G.PrintMGraph();
}
