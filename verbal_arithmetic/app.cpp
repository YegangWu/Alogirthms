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
	words.push_back("TEE");
	result = "FUNNY";
}	

void case4(std::vector<std::string>& words, std::string& result)
{
	words.push_back("LEET");
	words.push_back("CODE");
	result = "POINT";
}	


void case5(std::vector<std::string>& words, std::string& result)
{
	words.push_back("SO");
	words.push_back("MANY");
	words.push_back("MORE");
	words.push_back("MEN");
	words.push_back("SEEM");
	words.push_back("TO");
	words.push_back("SAY");
	words.push_back("THAT");
	words.push_back("THEY");
	words.push_back("MAY");
	words.push_back("SOON");
	words.push_back("TRY");
	words.push_back("TO");
	words.push_back("STAY");
	words.push_back("AT");
	words.push_back("HOME");
	words.push_back("SO");
	words.push_back("AS");
	words.push_back("TO");
	words.push_back("SEE");
	words.push_back("OR");
	words.push_back("HEAR");
	words.push_back("THE");
	words.push_back("SAME");
	words.push_back("ONE");
	words.push_back("MAN");
	words.push_back("TRY");
	words.push_back("TO");
	words.push_back("MEET");
	words.push_back("THE");
	words.push_back("TEAM");
	words.push_back("ON");
	words.push_back("THE");
	words.push_back("MOON");
	words.push_back("AS");
	words.push_back("HE");
	words.push_back("HAS");
	words.push_back("AT");
	words.push_back("THE");
	words.push_back("OTHER");
	words.push_back("TEN");
	result = "TESTS";
}	

int main()
{
	std::vector<std::string> words;
	std::string result;
	case5(words, result);

	VerbalArithmetic va(words, result);
	va.searchSolution();
	va.printResult();
	return 0;
}
