#include "graph.h"
#include "edge.h"
#include <fstream>
#include <sstream>

Graph::Graph(const std::string& filename) 
{
	std::ifstream infile(filename);
	std::string line;
	getline(infile, line);
	std::stringstream ss(line);
	ss >> d_N;
	for(int i = 0; i < d_N; ++i)
	{
		std::vector<Edge> tmp;
		d_edgeList.push_back(tmp);
	}	

	while(getline(infile, line))
	{
		std::stringstream ss(line);
		int v, w;
		double weight;
		ss >> v >> w >> weight;
		Edge edge(v, w, weight);
		d_edgeList[v].push_back(edge);
		d_edgeList[w].push_back(edge);	
	}
}

 bool Graph::edgeFrom(std::vector<Edge>& edges, int v) const
{
	if(v < 0 || v >= d_N)
	{
		return false;
	}
	edges = d_edgeList[v];
	return true;
}

int Graph::size() const
{
	return d_N;
}


