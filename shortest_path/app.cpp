#include "graph.h"
#include "dijkstra.h"
#include "topological_sort.h"
#include "bellman_ford.h"

int main()
{
	Graph g("data/input_diag.txt");
	Dijkstra dk(g, 0);
	dk.print();

	TopologicalSort ts(g, 0);
	ts.print();

	Graph gNC("data/input_negative_cycle.txt");
	BellmanFord bf(gNC, 0);
	bf.print();

	return 0;
}
