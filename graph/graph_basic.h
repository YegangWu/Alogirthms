#ifndef GRAPH_BASIC_H
#define GRAPH_BASIC_H

#include <vector>
#include <string>

class Graph
{
	private:
		int N;
		std::vector<int> vertices;
		std::vector<std::vector<int> > eglist;

		bool edgeInGraph(int v) const;
	public:
		Graph();
		Graph(const std::string& filename);
		void addEdge(int w, int v);	
		bool edgeFrom(std::vector<int>& edge, int v) const;
		int size() const;
		void print();
};

#endif
