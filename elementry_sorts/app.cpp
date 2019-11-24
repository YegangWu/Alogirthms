#include "insertion.h"
#include "shell_sort.h"
#include "convex_hull.h"
#include <cstdlib>
#include <ctime>

void sortTest()
{
	std::vector<int> listInt;
	std::vector<double> listDouble;
	std::srand(std::time(0));
	int N = 10000;
	for(int i = 0; i < N; ++i)
	{
		listInt.push_back(std::rand()%N);
		listDouble.push_back(std::rand()%N*0.1);	
	}	

	ComparePrimitive<int> cpint;
	InsertionSort<int, ComparePrimitive<int> > insort(listInt, cpint);
	insort.sort();

	ShellSort<int, ComparePrimitive<int> > shellinsort(listInt, cpint);
	shellinsort.sort();

	ComparePrimitive<double> cpdouble;
	InsertionSort<double, ComparePrimitive<double> > dbsort(listDouble, cpdouble);
	dbsort.sort();

	ShellSort<double, ComparePrimitive<double> > shelldbsort(listDouble, cpdouble);
	shelldbsort.sort();
}

int main()
{
	//sortTest();	
	ConvexHull ch("data/input.txt");
	ch.search();
	return 0;
}
