#ifndef INCLUDE_DIJKSTRA_H
#define INCLUDE_DIJKSTRA_H

#include "graph.h"
#include "edge.h"
#include <queue>
#include <vector>
#include <stack>

struct Node
{
	Node(int v, double dist);
	int d_v;
	double d_dist;
};

struct greaterByDist
{
	bool operator()(const Node& lhs, const Node& rhs)
	{
		return lhs.d_dist > rhs.d_dist;
	}
};

class Dijkstra
{
	public:
		Dijkstra(const Graph& g, int s);
		void print() const;
	private:
		std::vector<double> d_distTo;
		std::vector<Edge> d_pathTo;	
		std::vector<bool> d_marked;
		std::priority_queue<Node, std::vector<Node>, greaterByDist > d_pq;
		int d_N;
		int d_source;

		void relax(const Edge& edge);
		std::stack<Edge> getPathTo(int w) const;
};

inline
Node::Node(int v, double dist): d_v(v), d_dist(dist)
{
}

#endif
