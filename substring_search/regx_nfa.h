#ifndef INCLUDE_REGX_NFA_H
#define INCLUDE_REGX_NFA_H

#include <string>
#include "digraph.h"

class NFA
{
	public:
		NFA(const std::string& pattern);
		void buildEpsilonGraph();
		bool recognize(const std::string& input);
	private:
		int d_N;
		std::string d_pattern;
		Digraph d_graph;
};

#endif
