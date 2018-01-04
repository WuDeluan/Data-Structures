#include "Guide_class.h"
#include "Menu.h"

int main()
{
	Guide G;
	G.BuildMGraph();
	MenuC(G);

	return 0;
}
