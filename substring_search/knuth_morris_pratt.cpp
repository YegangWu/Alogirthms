#include "knuth_morris_pratt.h"
#include <iostream>

KMP::KMP(const std::string& target, const std::string& pattern)
{
	d_n = pattern.length();
	d_R = 26;
	for(int i = 0; i < d_R; ++i)
	{
		std::vector<int> tmp;
		for(int j = 0; j < d_n; ++j)
		{
			tmp.push_back(0);
		}
		d_dict.push_back(tmp);
	}

	d_dict[toInt(pattern[0])][0] = 1;
	int X = 0;

	for(int i = 1; i < d_n; ++i)
	{
		for(int j = 0; j < d_R; ++j)
		{
			d_dict[j][i] = d_dict[j][X];
		}
		d_dict[toInt(pattern[i])][i] = i+1;
		X = d_dict[toInt(pattern[i])][X];
	}	

	int s = 0;
	int L = target.length();
	int i;
	for(i = 0; i < L && s < d_n; ++i)
	{
		s = d_dict[toInt(target[i])][s];
	}
	if(s == d_n)
	{
		d_found = true;
		d_start = i - d_n;
	}
	else
	{
		d_found = false;
	}
}

int KMP::toInt(char c)
{
	return c - 97;
}

void KMP::print()
{
	if(d_found)
	{
		std::cout << "found a match, starts at " << d_start << std::endl;
	}
}
