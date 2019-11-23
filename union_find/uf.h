#ifndef INCLUDE_UF_H
#define INCLUDE_UF_H

/*
Successor with delete. Given a set of NN integers S = \{ 0, 1, ... , N-1 \}S={0,1,...,N−1} and a sequence of requests of the following form:

Remove xx from SS
Find the successor of xx: the smallest yy in SS such that y \ge xy≥x.

design a data type so that all operations (except construction) should take logarithmic time or better.

Solution:
when delete i, connect i with i+1 by updating i's root to (i+1)'s root, and mark i as removed. 

when query successor of i,  return its root.

connect with path compression will make each query logarithmic time


*/

#include <vector>

class UF
{
	public:
		UF(int N);
		void remove(int p);
	private:
		int d_N;
		std::vector<int> d_A;
		std::vector<bool> d_removed;

		int root(int p);
		int successor(int p);
};

#endif
