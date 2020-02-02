#include "verbal_arithmetic.h"
#include <unordered_map>
#include <iostream>
#include <algorithm>

VerbalArithmetic::VerbalArithmetic(std::vector<std::string>& words, std::string& result)
{
	d_findSolution = false;
	for(size_t i = 0; i < words.size(); ++i)
	{
		std::string word = words[i];
		std::reverse(word.begin(), word.end());
		d_words.push_back(word);
	}
	std::string word = result;
	std::reverse(word.begin(), word.end());
	d_result = word;

	d_maxL = getMaxLength();
	for(size_t i = 0; i < d_words.size(); ++i)
	{
		std::string word = d_words[i];
		for(int j = 0; j < word.length(); ++j)
		{
			char c = word[j];
			d_map[c] = -1;
		}
	}
	for(int j = 0; j < d_result.length(); ++j)
	{
		char c = d_result[j];
		d_map[c] = -1;
	}
}

void VerbalArithmetic::columnSearch(int& offset, std::set<int>& availableDigits, std::stack<std::stack<char> >& states, std::unordered_map<int, char>& resultAssignment, int& carryOn, bool& columnFinish)
{
	std::cout << "offset: " << offset << ", d_maxL: " << d_maxL << std::endl;
	if(offset >= d_result.length() || offset < 0)
	{
		return;
	}

	while(true)
	{
		int sum = 0;
		for(int i = 0; i < d_words.size(); ++i)
		{
			if(offset < d_words[i].length())
			{
				char c = d_words[i][offset];
				sum += d_map[c];
			}
		}
		sum += carryOn;
		int r = sum%10;
		int newCarryOn = sum/10;
		char c = d_result[offset];
		std::cout << "r: " << r << ", c: " << c << std::endl;
		if(offset != d_maxL -1 || newCarryOn == 0)
		{
			if(d_map[c] != -1)
			{
				if(sum%10 == d_map[c])
				{
					columnFinish = true;
					carryOn = newCarryOn;
					return;
				}
			}
			else 
			{
				if(offset != d_result.length() - 1 || r != 0)
				{
					auto iter = availableDigits.find(r);
					if(iter != availableDigits.end())
					{
						d_map[c] = *iter;
						availableDigits.erase(iter);
						resultAssignment[offset] = c;
						std::cout << "assign " << c << " to " << *iter << std::endl;
						columnFinish = true;
						carryOn = newCarryOn;
						return;
					}
				}
				else
				{
					std::cout << "right value " << r << " is taken" << std::endl;
				}
			}
		}
		
		std::cout << "need to bump up the latest character" << std::endl;
		auto riter = resultAssignment.find(offset);
		if(riter != resultAssignment.end())
		{
			int v = riter->first;
			char c = riter->second;
			d_map[c] = -1;
			availableDigits.insert(v);
			resultAssignment.erase(riter);
			std::cout << "unset result char " << c << std::endl;
		}

		std::stack<char>& state = states.top();
		while(!state.empty())
		{
			char c = state.top();
			state.pop();

			int v = d_map[c]; 
			availableDigits.insert(v);
			d_map[c] = -1;

			auto iter = availableDigits.find(v);
			++iter;
			if(iter != availableDigits.end())
			{
				d_map[c] = *iter;
				state.push(c);
				availableDigits.erase(iter);
				std::cout << "bump up " << c << " to " << *iter << std::endl;
				break;
			}
		}
		if(state.empty())
		{
			return;
		}	

		for(size_t i = 0; i < d_words.size(); ++i)
		{
			std::string word = d_words[i];
			if(offset < word.length())
			{
				char c = word[offset];
				if(d_map[c] == -1)
				{
					auto iter = availableDigits.begin();
					if(offset == word.length() - 1 && *iter == 0)
					{
						++iter;
					}
					d_map[c] = *iter;
					state.push(c);
					availableDigits.erase(iter);
					std::cout << "fill " << c << " to " << *iter << std::endl;
				}
			}
		}
	}
}

void VerbalArithmetic::initAllDigits(std::set<int>& availableDigits)
{
	availableDigits.clear();
	for(int i = 0; i <= 9; ++i)
	{
		availableDigits.insert(i);
	}
}

void VerbalArithmetic::searchSolution()
{
	std::set<int> availableDigits;
	initAllDigits(availableDigits);
	std::stack<std::stack<char> > states;
	std::unordered_map<int, char> resultAssignment;
	std::unordered_map<int, int> carryOnMap;
	carryOnMap[0] = 0;
	int offset = 0;
	int carryOn = 0;
	bool columnFinish = false;
	
	initNewColumn(offset, states, availableDigits);
	while(true)
	{
		columnFinish = false;
		columnSearch(offset, availableDigits, states, resultAssignment, carryOn, columnFinish);
		std::cout << "columnFinish search: " << (columnFinish ? "success" : "failuer") << std::endl;	

		if(columnFinish)
		{
			if(offset == d_maxL-1)
			{
				std::cout << "Find a solution!" << std::endl;
				d_findSolution = true;
				return;
			}
			++offset;
			carryOnMap[offset] = carryOn;
			initNewColumn(offset, states, availableDigits);
		}
		else
		{
			std::cout << "Column search failed, need to clean up the top stack" << std::endl;
			assert(resultAssignment.find(offset) == resultAssignment.end());
			std::stack<char> state = states.top();
			states.pop();
			while(!state.empty())
			{
				char c = state.top();
				state.pop();
				int v = d_map[c];
				availableDigits.insert(v);
				d_map[c] = -1;
				std::cout << "unset character " << c << std::endl;
			}
			
			--offset;
			std::cout << "offset equals " << offset << std::endl;
			while(!states.empty())
			{
				auto riter = resultAssignment.find(offset);
				if(riter != resultAssignment.end())
				{
					char c = riter->second;
					int v = d_map[c];
					availableDigits.insert(v);
					d_map[c] = -1;
					resultAssignment.erase(riter);
					std::cout << "unset result character " << c << std::endl;
				}

				std::stack<char> state = states.top();
				states.pop();
				while(!state.empty())
				{
					char c = state.top();
					state.pop();
					int v = d_map[c];
					d_map[c] = -1;
					availableDigits.insert(v);
					auto iter = availableDigits.find(v);
					++iter;
					if(iter != availableDigits.end())
					{
						d_map[c] = *iter;
						availableDigits.erase(iter);
						state.push(c);
						std::cout << "bump up character " << c << " to " << *iter << std::endl;
						for(size_t i = 0; i < d_words.size(); ++i)
						{
							std::string word = d_words[i];
							char c = word[offset];
							if(d_map[c] == -1)
							{
								auto iter = availableDigits.begin();
								d_map[c] = *iter;
								availableDigits.erase(iter);
								state.push(c);
								std::cout << "fill in character " << c << " with " << *iter << std::endl;
							}		
						}
						break;
					}
				}
				if(!state.empty())
				{
					states.push(state);
					carryOn = carryOnMap[offset];
					break;
				}
				else
				{
					--offset;
				}
			}
			if(states.empty())
			{
				d_findSolution = false;
				return;
			}
		}
	}	
}

void VerbalArithmetic::printResult()
{
	if(!d_findSolution)
	{
		std::cout << "Solution not found!" << std::endl;
		return ;
	}
	auto iter = d_map.begin();
	for(; iter != d_map.end(); ++iter)
	{
		if(iter->second != -1)
		{
			std::cout << iter->first << ": " << iter->second << std::endl;
		}
	}
}

void VerbalArithmetic::initNewColumn(int& offset, std::stack<std::stack<char> >& states, std::set<int>& availableDigits)
{
	std::stack<char> columnState;
	for(int i = 0; i < d_words.size(); ++i) 
	{
		std::string word = d_words[i];
		if(offset < word.length())
		{
			char c = word[offset];
			if(d_map[c] == -1)
			{
				auto iter = availableDigits.begin();
				if(offset == word.length() - 1 && *iter == 0)
				{
					++iter;
				}
				d_map[c] = *iter;
				std::cout << "assign " << *iter << " to " << c << ", and push it to stack with offset " << offset << std::endl;
				availableDigits.erase(iter);
				columnState.push(c);
			}
		}
	}
	states.push(columnState);
}

void VerbalArithmetic::process()
{
	std::set<int> availableDigits;
	for(int i = 0; i <= 9; ++i)
	{
		availableDigits.insert(i);
	}
	int offset = 0;
	int carryOn = 0;
	std::stack<std::stack<char> > states;
	bool finish = false;

	search(offset, states, availableDigits, carryOn, finish);
	if(!finish)
	{
		std::cout << "Couldn't find a solution!" << std::endl;
	}
	else
	{
		std::unordered_map<char, int>::const_iterator iter = d_map.begin();
		for(; iter != d_map.end(); ++iter)
		{
			std::cout << "(" << iter->first << ", " << iter->second << ")";
		}
		std::cout << std::endl;
	}
}

void VerbalArithmetic::search(int& offset, std::stack<std::stack<char> >& states, std::set<int>& availableDigits, int& carryOn, bool& finish)
{
	if(offset >= d_maxL) 
	{
		finish = true;
		return;
	}
	if(offset < 0)
	{
		finish = false;
		return;
	}
	if(offset >= states.size()-1)
	{
		initNewColumn(offset, states, availableDigits);	
	}
	bool columnFinish = false;
	std::unordered_map<int, char> resultAssignment;
	columnSearch(offset, availableDigits, states, resultAssignment, carryOn, columnFinish);
	if(!columnFinish)
	{
		return;
	}
	++offset;
	while(true)
	{
		search(offset, states, availableDigits, carryOn, finish);
		if(states.empty()) {
			finish = false;
			return;
		}
		if(finish)
		{
			return;
		}
		findNext(states, availableDigits, offset, finish);
	}
}

void VerbalArithmetic::findNext(std::stack<std::stack<char> >& states, std::set<int>& availableDigits, int& offset, bool& finish)
{
	while(!states.empty())
	{
		std::stack<char> state = states.top();
		states.pop();
		--offset;
		while(state.empty())
		{
			state = states.top();
			states.pop();
			--offset;
		}
		char c = state.top();
		state.pop();
		int v = d_map[c];
		availableDigits.insert(v);
		auto iter = availableDigits.find(v);
		++iter;
		if(iter != availableDigits.end())
		{
			d_map[c] = *iter;
			state.push(c);
			availableDigits.erase(iter);
			states.push(state);
			break;
		}
	}
	return;
}

int VerbalArithmetic::getMaxLength()
{
	int L = 0;
	for(int i = 0; i < d_words.size(); ++i)
	{
		L = (d_words[i].length() > L ? d_words[i].length() : L);
	}
	L = d_result.length() > L ? d_result.length(): L;
	std::cout << "max L is " << L << std::endl;
	return L;
}
