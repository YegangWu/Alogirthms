#include "uf.h"
#include <random>

int main()
{
	int N = 20;
	UF uf(N);
	
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> uni(0, N-1);
	for(int i = 0; i < 3*N; ++i)
	{
		int random_integer = uni(rng);
		uf.remove(random_integer);
	}
	return 0;
}
