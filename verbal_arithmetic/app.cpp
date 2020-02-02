#include "verbal_arithmetic.h"
#include <string>
#include <vector>

void case1(std::vector<std::string>& words, std::string& result)
{
	words.push_back("SEND");
	words.push_back("MORE");
	result = "MONEY";
}	

void case2(std::vector<std::string>& words, std::string& result)
{
	words.push_back("SIX");
	words.push_back("SEVEN");
	words.push_back("SEVEN");
	result = "TWENTY";
}	

void case3(std::vector<std::string>& words, std::string& result)
{
	words.push_back("THIS");
	words.push_back("IS");
	words.push_back("TOO");
	result = "FUNNY";
}	

void case4(std::vector<std::string>& words, std::string& result)
{
	words.push_back("LEET");
	words.push_back("CODE");
	result = "POINT";
}	
int main()
{
	std::vector<std::string> words;
	std::string result;
	case4(words, result);

	VerbalArithmetic va(words, result);
	va.searchSolution();
	va.printResult();
	return 0;
}
