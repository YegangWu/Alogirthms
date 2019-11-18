#include "regx_nfa.h"
#include <stack>
#include <iostream>

NFA::NFA(const std::string& pattern): d_N(pattern.length()), d_pattern(pattern), d_graph(Digraph(d_N+1)) 
{
	//embrace with parenthesis if not so 
	if(d_pattern[0] != '(' || d_pattern[d_N-1] != ')')
	{
		d_pattern = "(" + d_pattern + ")";
		d_N = d_pattern.length();
		d_graph = Digraph(d_N+1);
	}
	buildEpsilonGraph();
}

void NFA::buildEpsilonGraph()
{
	std::stack<int> st;
	for(size_t i = 0; i < d_pattern.size(); ++i)
	{
		int lp = i;
		if(d_pattern[i] == '(' || d_pattern[i] == '|')
		{
			st.push(i);
		}	
		else if(d_pattern[i] == ')')
		{
			int p = st.top();
			st.pop();
			if(d_pattern[p] == '|')
			{
				lp = st.top();
				st.pop();
				d_graph.addEdge(lp, p+1);
				d_graph.addEdge(p, i);
			}
			else
			{
				lp = p;
			}
		}
		if(i < d_N-1 && d_pattern[i+1] == '*')
		{
			d_graph.addEdge(lp, i+1);
			d_graph.addEdge(i+1, lp);
		}

		if(d_pattern[i] == '(' || d_pattern[i] == '*' || d_pattern[i] == ')')
		{
			d_graph.addEdge(i, i+1);
		}
	}
	//d_graph.print();
}

bool NFA::recognize(const std::string& input)
{
	std::vector<int> pc;
	d_graph.search(pc, 0);
	for(size_t i = 0, L = input.length(); i < L; ++i)
	{
		std::vector<int> match;
		for(int j = 0, N = pc.size(); j < N; ++j)
		{
			if(pc[j] == d_N)
			{
				continue;
			}

			if(input[i] == d_pattern[pc[j]])
			{
				match.push_back(pc[j]+1);
			}	
		}	
		pc.clear();
		d_graph.search(pc, match);
	} 
	for(size_t j = 0, N = pc.size(); j < N; ++j)
	{
		if(pc[j] == d_N)
		{
			std::cout << input << " matches " << d_pattern << std::endl;
			return true;
		}
	}
	std::cout << input << " doesn't match " << d_pattern << std::endl;
	return false;
}
