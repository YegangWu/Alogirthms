#ifndef INCLUDE_LONGEST_PALINDROM_H
#define INCLUDE_LONGEST_PALINDROM_H

#include <string>

class LongestPalindrom
{
	public:
		LongestPalindrom(const std::string& str);
		void printOutput();
	private:
		std::string longestPalind;
	 	std::string search(const std::string& str, int lo, int hi);
		std::string searchOnShortStr(const std::string& str, int lo, int hi);
		std::string searchOnLength2(const std::string& str, int n);
		std::string longestOf3(const std::string& one, const std::string& two, const std::string& three);
};

#endif
