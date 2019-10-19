#ifndef INCLUDE_UF_H
#define INCLUDE_UF_H

#include <vector>

class UF
{
	public:
		UF(int N);
		void connect(int p, int q);
		bool connected(int p, int q) const;
	private:
		int d_N;
		std::vector<int> d_root;	
		std::vector<int> d_size;

		int root(int p) const;
};

#endif
