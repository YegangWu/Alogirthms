#include "longest_palindrom.h"
#include <iostream>

LongestPalindrom::LongestPalindrom(const std::string& str)
{
	int L = str.length();
	longestPalind = search(str, 0, L-1);	
}

std::string LongestPalindrom::search(const std::string& str, int lo, int hi)
{
	if(lo > hi) return ""; 
	if(hi - lo <= 2) return searchOnShortStr(str, lo, hi);

	int mid = (lo + hi)/2;
	std::string leftP = search(str, lo, mid);
	std::string rightP = search(str, mid+1, hi);

	int lN = leftP.length();
	int rN = rightP.length();
	std::string midP = search(str, mid-lN+1, mid+rN);

	return longestOf3(leftP, midP, rightP);
}

std::string LongestPalindrom::searchOnShortStr(const std::string& str, int lo, int hi)
{
	if(hi == lo) return str;
	if(hi-lo == 1) return searchOnLength2(str, lo);
	if(str[lo] == str[hi])
	{
		return str;
	}
	std::string lP = searchOnLength2(str, lo);
	std::string rP = searchOnLength2(str, lo+1);
	if(lP.length() >= rP.length()) return lP;
	return rP;
}

std::string LongestPalindrom::searchOnLength2(const std::string& str, int n)
{
	return str[n] == str[n+1] ? str: str.substr(n,1);
}

std::string LongestPalindrom::longestOf3(const std::string& one, const std::string& two, const std::string& three)
{
	if(one.length() >= two.length() && one.length() >= three.length()) return one;
	if(two.length() >= one.length() && two.length() >= three.length()) return two;
	return three;
}

void LongestPalindrom::printOutput()
{
	std::cout << longestPalind << std::endl;
}
