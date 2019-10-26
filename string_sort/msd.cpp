#include "msd.h"
#include <fstream>
#include <sstream>
#include <iostream>

MSD::MSD(const std::string& filename)
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

int MSD::index(char c)
{
	return c - 97;
}

void MSD::sort(int lo, int hi, int d)
{
	if(lo >= hi) return;
	int R = 26;
	int count[R+1];
	for(int i = 0; i < R+1; ++i)
	{
		count[i] = 0;
	}	

	std::string d_aux[hi-lo+1];
	int offset = 0;
	for(int i = lo; i <= hi; ++i)
	{
		if ( d >= d_data[i].length() )
		{
			d_aux[offset++] = d_data[i];
			continue;
		}
		count[ index(d_data[i][d])+1 ]++;
	}
	for(int i = 0; i < R; ++i)
	{
		count[i+1] += count[i];
	}
	for(int i = lo; i <= hi; ++i)
	{
		if( d < d_data[i].length())
		{
			d_aux[ offset + count[index(d_data[i][d])]++ ] = d_data[i];
		}
	}
	for(int i = 0; i < hi-lo+1; ++i)
	{
		d_data[i+lo] = d_aux[i];
	}
	
	lo += offset;
	sort(lo, lo+count[0]-1, d+1);
	for(int i = 1; i < R; ++i)
	{
		sort(lo+count[i-1], lo+count[i]-1, d+1);
	}
}

void MSD::print()
{
	std::cout << "After MSD sort: " << std::endl;
	for(int i = 0; i < d_N; ++i)
	{
		std::cout << d_data[i] << std::endl;
	}
}
