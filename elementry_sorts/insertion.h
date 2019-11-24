#ifndef INCLUDE_INSERTION_H
#define INCLUDE_INSERTION_H

#include <vector>
#include <iostream>
#include <ctime>
#include <cstdio>

template<class T, class G>
class InsertionSort
{
	public:
		InsertionSort(std::vector<T>& list, G compare);
		virtual void sort();
	
	protected:
		std::vector<T>& d_list;
		G d_compare;

		void swap(T& i, T& j);
		void print();
};

template<class T, class G>
InsertionSort<T, G>::InsertionSort(std::vector<T>& list, G compare): d_list(list), d_compare(compare) 
{
}

template<class T, class G>
void InsertionSort<T, G>::sort()
{
	std::clock_t start = std::clock();

	int L = d_list.size();
	for(int i = 1; i < L; ++i)
	{
		int j = i;
		while(j > 0 && d_compare(d_list[j], d_list[j-1]) )
		{
			swap(d_list[j], d_list[j-1]);
			j--;
		}
	}
	std::cout << "In insertion sort, time elapsed: " << (std::clock() - start)*1.0/CLOCKS_PER_SEC << std::endl;
	//print();
}

template<class T, class G>
void InsertionSort<T, G>::swap(T& i, T& j)
{
	T tmp = i;
	i = j;
	j = tmp;
}

template<class T, class G>
void InsertionSort<T, G>::print()
{
	for(size_t i = 0; i < d_list.size(); ++i)
	{
		std::cout << d_list[i] << ", ";
	}
	std::cout << std::endl;
}

template<class T>
struct ComparePrimitive
{
	bool operator()(T i, T j)
	{
		return i < j;
	}
};

#endif
