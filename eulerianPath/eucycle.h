#ifndef INCLUDE_EUCYCLE_H
#define INCLUDE_EUCYCLE_H

#include "node.h"
#include "graph.h"
#include <vector>

class EuCycle
{
	public:
		EuCycle(Graph& g);
		void findCycle(Graph& g, int v);
		void test_findFirstCycle(Graph& g, int v);
	private:
		int d_N;
		std::vector<bool> d_marked;
		Node* d_visitedCycle;
		Node* d_currentPath;	
		int d_origin;
		void dfs(Graph& g, int v);
		void throwOnNull(Node* p, const std::string& errorMsg);
		void combineVisitedCycles();
		bool findNewOrigin(Graph& g);
		void printCurrentCycle();
};

#endif
