#include "uf.h"
#include <iostream>

UF::UF(int N): d_N(N)
{
	for(int i = 0; i < d_N; ++i)
	{
		d_A.push_back(i);
		d_removed.push_back(false);
	}
}

int UF::root(int p)
{
	int i = p;
	while(d_A[i] != i)
	{
		i = d_A[i];
	}
	int j = p;
	while(d_A[j] != j)
	{
		j = d_A[j];
		d_A[j] = i;
	}
	return i;
}

void UF::remove(int p)
{
	std::cout << "remove " << p << "; ";
	if(p == d_N-1) 
	{
		d_removed[p] = true;
	}
	else
	{
		int i = root(p);
		int j = root(p+1);
		if(i != j)
		{
			d_A[i] = j;	
			d_removed[p] = true;
		}
	}	
	std::cout << p << "'s successor is " << successor(p) << std::endl;
}

int UF::successor(int p)
{
	int i = root(p);
	if(!d_removed[i])
	{
		return i;
	}
	return -1;
}
