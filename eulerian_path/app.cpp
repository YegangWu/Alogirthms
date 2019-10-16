#include "node.h"
#include "graph.h"
#include "eucycle.h"
#include <ctime>

int main()
{
	Graph g("input2.txt");
	g.print();

	EuCycle ec(g);
	std::srand(std::time(0));
	int origin = std::rand()%9;
	ec.findCycle(g, origin);
	return 0;
}
