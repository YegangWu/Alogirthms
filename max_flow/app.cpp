#include "flow_graph.h"
#include "ford_fulkerson.h"

int main()
{
	FlowGraph g("data/input3.txt");
	g.print();
	FordFulkerson ff(g, 0, g.size()-1);
	ff.print(g);
	return 0;
}
