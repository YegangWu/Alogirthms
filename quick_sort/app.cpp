#include "quick_sort.h"

int main()
{
	std::vector<int> list;
	int N = 20;
	int maxV = 100;
	for(int i = 0; i < N; ++i)
	{
		list.push_back(rand()%(maxV+1));
	}	
	QuickSort qs(list);
}
