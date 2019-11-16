#include "longest_palindrom.h"
#include "knuth_morris_pratt.h"

int main()
{
	KMP kmp("aabacaababacaa", "ababac");
	kmp.print();
	return 0;
}
