#include "quick_sort.h"
#include <ctime>
#include <iostream>

QuickSort::QuickSort(std::vector<int>& list): d_list(list)
{
	std::srand(std::time(0));
	randShuffle();
	print(0, d_list.size()-1);
	sort(d_list, 0, d_list.size()-1);
	//sortBy3Way(d_list, 0, d_list.size()-1);
	print(0, d_list.size()-1);
}

int QuickSort::partition(std::vector<int>& list, int lo, int hi)
{
	int i = lo+1;
	int j = hi;
	int v = list[lo];
	while(j >= i)
	{
		while(list[i] < v)
		{
			++i;
			if(i >= hi)
			{
				break;
			}
		}
		while(list[j] > v)
		{
			--j;
			if(j <= lo)
			{
				break;
			}
		}
		if(j <= i)
		{
			break;
		}
		swap(list, i, j);
	}
	swap(list, lo, j);
	return j;
}

void QuickSort::sort(std::vector<int>& list, int lo, int hi)
{
	if(lo >= hi) return;
	int mid = partition(list, lo, hi);
	sort(list, lo, mid-1);
	sort(list, mid+1, hi);
}

void QuickSort::sortBy3Way(std::vector<int>& list, int lo, int hi)
{
	if(lo >= hi) return;
	int eqS, eqE;
	threeWayPartition(list, lo, hi, eqS, eqE);
	sortBy3Way(list, lo, eqS-1);
	sortBy3Way(list, eqE+1, hi);
}

void QuickSort::swap(std::vector<int>& list, int i, int j)
{
	int tmp = list[i];
	list[i] = list[j];
	list[j] = tmp;
}

void QuickSort::randShuffle()
{
	for(int i = 1; i < d_list.size(); ++i)
	{
		int j = rand()%(i+1);
		swap(d_list, i, j);
	}
}

void QuickSort::print(int lo, int hi)
{
	for(int i = lo; i <= hi; ++i)
	{
		std::cout << d_list[i] << ", ";
	}
	std::cout << std::endl;
}

void QuickSort::threeWayPartition(std::vector<int>& list, int lo, int hi, int& eqS, int& eqE)
{
	int i = lo+1;
	int k = i;
	int j = hi;
	int v = list[lo];
	while( j >= i )
	{
		if(list[i] < v)
		{
			swap(list, i, k);
			++k;
			++i;
		}	
		else if(list[i] > v)
		{
			swap(list, i, j);
			--j;
		}
		else
		{
			++i;
		}
	}
	swap(list, k-1, lo);
	eqS = k-1;
	eqE = j;
}
