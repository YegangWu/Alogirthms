#include "longest_palindrom.h"
#include "knuth_morris_pratt.h"
#include "regx_nfa.h"

int main()
{
	KMP kmp("aabacaababacaa", "ababac");
	kmp.print();

	NFA nfa("(A*B|AC)D");
	nfa.recognize("AABD");
	nfa.recognize("ACD");
	nfa.recognize("BD");
	nfa.recognize("AAAAAABD");
	nfa.recognize("BD");
	nfa.recognize("BCD");

	NFA nfa2("AB*(C|D)");
	nfa2.recognize("AC");
	nfa2.recognize("ABC");
	nfa2.recognize("ABD");
	nfa2.recognize("ABBC");
	nfa2.recognize("AD");
	nfa2.recognize("AAD");

	return 0;
}
