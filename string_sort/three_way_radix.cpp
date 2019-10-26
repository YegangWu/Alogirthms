#include "three_way_radix.h"

#include <fstream>
#include <iostream>

ThreeWayRadix::ThreeWayRadix(const std::string& filename)
{
	std::ifstream infile(filename);
	std::string line;
	while(getline(infile, line))
	{
		d_data.push_back(line);
	}
	d_N = d_data.size();
	sort(0, d_N-1, 0);
}

void ThreeWayRadix::swap(std::string& lhs, std::string& rhs)
{
	std::swap(lhs, rhs);
}

void ThreeWayRadix::sort(int lo, int hi, int d)
{
	if(hi <= lo) return;
	int offset = lo;
	while(d >= d_data[offset].length())
	{
		offset++;
	}

	int i = offset;
	int j = offset+1;
	int k = offset+1;
	while(k <= hi)
	{
		if (d >= d_data[k].length())
		{
			swap(d_data[offset++], d_data[k]);
			swap(d_data[j++], d_data[k++]);
		}
		else if( d_data[k][d] < d_data[i][d] )
		{
			swap(d_data[i++], d_data[k]);
			swap(d_data[j++], d_data[k++]);
		}
		else if( d_data[k][d] == d_data[i][d] )
		{
			swap(d_data[j++], d_data[k++]);
		}
		else
		{
			k++;
		}
	}
	sort(offset, i-1, d);
	sort(i, j-1, d+1);
	sort(j, hi, d);
}

void ThreeWayRadix::print()
{
	std::cout << "After 3-way radix sort: " << std::endl;
	for(int i = 0; i < d_N; ++i)
	{
		std::cout << d_data[i] << std::endl;
	}
}
