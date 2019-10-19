#include "diag.h"
#include "graph_basic.h"
#include "scc.h"

int main()
{
	Graph g("input4.txt");
	DIAG diag(g);
	diag.printDiagOrder();

	SCC scc(g);
	scc.print();
	return 0;
}
