#ifndef INCLUDE_DIGRAPH_H
#define INCLUDE_DIGRAPH_H

#include <string>
#include <vector>

class Digraph
{
	public:
		Digraph(int N);
		void addEdge(int w, int v);
		void search(std::vector<int>& pc, int source);
		void search(std::vector<int>& pc, const std::vector<int>& match);
		void print() const;
	private:
		int d_N;
		std::vector<std::vector<int> > d_edges;
		std::vector<bool> d_mark;
		void dfs(int source);
		void getEdges(std::vector<int>& edges, int w);
};

#endif
