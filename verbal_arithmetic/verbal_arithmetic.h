#ifndef INCLUDE_VERBAL_ARITHMETIC_H
#define INCLUDE_VERBAL_ARITHMETIC_H

#include <vector>
#include <string>
#include <set>
#include <stack>
#include <unordered_map>

class VerbalArithmetic
{
	public:
		VerbalArithmetic(std::vector<std::string>& words, std::string& result);
		void searchSolution();
		void process();
		void printResult();
	private:
		int d_maxL;
		std::vector<std::string> d_words;
		std::string d_result;
		std::unordered_map<char, int> d_map;
		bool d_findSolution;
		void columnSearch(int& offset, std::set<int>& availableDigits, std::stack<std::stack<char> >& states, std::unordered_map<int, char>& resultAssignment, int& carryOn, bool& columnFinish);
		void initAllDigits(std::set<int>& availableDigits);
		int getMaxLength();
		void search(int& offset, std::stack<std::stack<char> >& states, std::set<int>& availableDigits, int& carryOn, bool& finish);
		void initNewColumn(int& offset, std::stack<std::stack<char> >& states, std::set<int>& availableDigits);
		void findNext(std::stack<std::stack<char> >& states, std::set<int>& availableDigits, int& offset, bool& finish);
};

#endif
