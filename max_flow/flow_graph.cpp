#include "flow_graph.h"

#include <fstream>
#include <sstream>
#include <stdexcept>
#include <iostream>

FlowGraph::FlowGraph(const std::string& filename)
{
	std::fstream infile(filename);
	std::string line;
	getline(infile, line);
	if(line.empty())
	{
		throw std::runtime_error("FlowGraph: Empty file!");
	}
	std::stringstream ss(line);
	ss >> d_N;
	std::vector<Edge*> tmp;
	for(int i = 0; i < d_N; ++i)
	{
		d_edgeList.push_back(tmp);
	}

	while(getline(infile, line))
	{
		std::stringstream ss(line);
		int v, w;
		double capacity;
		ss >> v >> w >> capacity;
		Edge* edgeP = new Edge(v, w, capacity);
		d_edgeList[v].push_back(edgeP);	
		d_edgeList[w].push_back(edgeP);
	}
}

std::vector<Edge*> FlowGraph::edgeFrom(int v) const
{
	if(v < 0 || v >= d_N)
	{
		throw std::runtime_error("FlowGraph::edgeFrom: Invalid vertex id");
	}
	return d_edgeList[v];
}

int FlowGraph::size() const
{
	return d_N;
}

void FlowGraph::print() const
{
	for(int i = 0; i < d_N; ++i)
	{
		for(size_t j = 0; j < d_edgeList[i].size(); ++j)
		{
			const Edge* edgeP = d_edgeList[i][j];
			std::cout << edgeP->from() << "->" << edgeP->to() << "(" << edgeP->flow() << "/" << edgeP->capacity() << "), ";
		}
		std::cout << std::endl;
	}
}
