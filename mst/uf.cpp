#include "uf.h"

UF::UF(int N)
{
	d_N = N;
	for(int i = 0; i < d_N; ++i)
	{
		d_root.push_back(i);
		d_size.push_back(1);
	}
}

int UF::root(int p) const
{
	int pRoot = d_root[p];
	while(pRoot != d_root[pRoot])
	{
		pRoot = d_root[pRoot];
	}
	return pRoot;
}

void UF::connect(int p, int q)
{
	int pRoot = root(p);
	int qRoot = root(q);
	if(pRoot != qRoot)
	{
		if(d_size[pRoot] < d_size[qRoot])
		{
			d_root[pRoot] = qRoot;
			d_size[qRoot] += d_size[pRoot];
		}
		else
		{
			d_root[qRoot] = pRoot;
			d_size[pRoot] += d_size[qRoot];
		}
	}
}

bool UF::connected(int p, int q) const
{
	return root(p) == root(q);
}
