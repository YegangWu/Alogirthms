#include "graph.h"
#include "kruskal.h"
#include "prim.h"
#include <iostream>

int main()
{
	Graph g("input.txt");
	Kruskal kk(g);
	kk.print();

	Prim pm(g);
	pm.print();

	return 0;
}
