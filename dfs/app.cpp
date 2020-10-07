#include "dfs.h"
#include "bfs.h"
#include "graph_basic.h"
#include "ccomponents.h"
#include "bipartite.h"

int main()
{
	Graph g("input_bipartite.txt");
	g.print();

	DFS dfs(g.size());
	dfs.dfs(g, 4);
	dfs.printPath();

	BFS bfs(g.size());
	bfs.bfs(g, 4);
	bfs.print();

	CC cc(g);
	cc.printInfo();

	Graph gb("input_bipartite.txt");
	BP bp(gb);
	bp.report();
	
	Graph gb2("input_bipartite2.txt");
	BP bp2(gb2);
	bp2.report();

	//Graph gb3("input_bipartite3.txt");
	BP bp3(gb3);
	bp3.report();

	return 0;
}
