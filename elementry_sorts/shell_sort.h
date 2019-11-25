#ifndef INCLUDE_SHELL_SORT_H
#define INCLUDE_SHELL_SORT_H

#include "insertion.h"

template<class T, class G>
class ShellSort : public InsertionSort<T, G>
{
	public:
		ShellSort(std::vector<T>& list, G compare);
		void sort();
};

template<class T, class G>
ShellSort<T, G>::ShellSort(std::vector<T>& list, G compare) : InsertionSort<T, G>(list, compare)
{
}

template<class T, class G>
void ShellSort<T, G>::sort()
{
	std::clock_t start = std::clock();

	int L = this->d_list.size();
	int h = 1;
	while(h < L)
	{
		h = 3*h + 1;	
	}
	h = (h-1)/3;

	while(h >= 1)
	{
		for(int i = h; i < L; ++i)
		{
			int j = i;
			while(j >= h && this->d_compare(this->d_list[j], this->d_list[j-h]))
			{
				//std::cout << "swap " << this->d_list[j] << " with " << this->d_list[j-h] << std::endl;
				this->swap(this->d_list[j], this->d_list[j-h]);
				j -= h;
			}
		}
		h = (h-1)/3;
	}
	std::cout << "In shellsort, time elapsed: " << (std::clock() - start)*1.0/CLOCKS_PER_SEC << std::endl;
	
	//this->print();
}

#endif
