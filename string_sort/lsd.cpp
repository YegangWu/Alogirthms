#include "lsd.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <stdexcept>

LSD::LSD(const std::string& filename)
{
	std::ifstream infile(filename);
	std::string line;
	getline(infile, line);
	d_w = line.length();
	d_data.push_back(line);
	d_aux.push_back("");

	while(getline(infile, line))
	{
		if( line.length() != d_w )
		{
			throw std::runtime_error("Invalid input: "+line);
		}
		d_data.push_back(line);
		d_aux.push_back("");
	}
	d_N = d_data.size();
	for(int i = d_w-1; i >= 0; --i)
	{
		sort(i);
	}
}

int LSD::index(char c)
{
	return c - 97;
}

void LSD::sort(int d)
{
	int R = 26;
	int count[R+1];
	
	for(int i = 0; i < R+1; ++i)
	{
		count[i] = 0;
	}
	for(size_t i = 0; i < d_data.size(); ++i)
	{
		count[ index( d_data[i][d] )+1 ]++;
	}
	for(int i = 0; i < R; ++i)
	{
		count[i+1] += count[i];
	}
	for(int i = 0; i < d_data.size(); ++i)
	{
		d_aux[ count[index(d_data[i][d])]++ ] = d_data[i];		
	}
	d_data = d_aux;
}

void LSD::print()
{
	std::cout << "After lsd sorting: " << std::endl;
	for(int i = 0; i < d_N; ++i)
	{
		std::cout << d_data[i] << std::endl;
	}
}
