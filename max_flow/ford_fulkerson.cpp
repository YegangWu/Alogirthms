#include "ford_fulkerson.h"
#include <limits>
#include <algorithm>
#include <iostream>

FordFulkerson::FordFulkerson(FlowGraph& g, int s, int t)
{
	d_N = g.size();
	d_source = s;
	d_target = t;
	d_maxFlow = 0;
	for(int i = 0; i < d_N; ++i)
	{
		d_marked.push_back(false);
		d_pathTo.push_back(0);
	}

	while(hasResidualPath(g))
	{
		double newFlow = std::numeric_limits<double>::infinity();
		for(int w = t; w != s; w = d_pathTo[w]->other(w))
		{
			newFlow = std::min(newFlow, d_pathTo[w]->residualCapacityTo(w));	
		}
		for(int w = t; w != s; w = d_pathTo[w]->other(w))
		{
			d_pathTo[w]->addResidualFlowTo(w, newFlow);
		}	
		d_maxFlow += newFlow;
	}	
}

bool FordFulkerson::hasResidualPath(const FlowGraph& g)
{
	for(int i = 0; i < d_N; ++i)
	{
		d_marked[i] = false;
	}
	dfs(g, d_source);	
	return d_marked[d_target];
}

void FordFulkerson::dfs(const FlowGraph&g, int v)
{
	d_marked[v] = true;
	std::vector<Edge*> edges = g.edgeFrom(v);
	for(std::vector<Edge*>::const_iterator iter = edges.begin(); iter != edges.end(); ++iter)
	{
		Edge* edgeP = *iter;
		int w = edgeP->other(v);
		if(!d_marked[w] && edgeP->residualCapacityTo(w) > 0)
		{
			d_marked[w] = true;
			d_pathTo[w] = edgeP;
			dfs(g, w);
		}
	} 
}

void FordFulkerson::print(const FlowGraph& g) const
{
	std::cout << "The max flow is " << d_maxFlow << ", and the residual graph is: " << std::endl;
	g.print();	
}
