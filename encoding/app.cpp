#include "huffman.h"
#include <iostream>
int main()
{
	HuffMan hm("data/input.txt");
	hm.encode();

	HuffMan hm2("data/encode.txt");
	hm2.decode();

	return 0;
}
