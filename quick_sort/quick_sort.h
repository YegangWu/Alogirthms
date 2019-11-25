#ifndef INCLDUE_QUICK_SORT_H
#define INCLDUE_QUICK_SORT_H

#include <vector>

class QuickSort
{
	public:
		QuickSort(std::vector<int>& list);
	private:
		std::vector<int>& d_list;
		void sort(std::vector<int>& list, int lo, int hi);
		void sortBy3Way(std::vector<int>& list, int lo, int hi);
		int partition(std::vector<int>&list, int lo, int hi);
		void threeWayPartition(std::vector<int>& list, int lo, int hi, int& eqS, int& eqE);
		void swap(std::vector<int>& list, int i, int j);
		void randShuffle();
		void print(int lo, int hi);
};

#endif
