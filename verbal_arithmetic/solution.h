#ifndef INCLUDE_SOLUTION_H
#define INCLUDE_SOLUTION_H

#include <vector>
#include <string>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <iostream>

class Solution 
{
public:
	bool isSolvable(std::vector<std::string>& words, std::string result)
	{
		init(words, result);
		searchSolution();
		return d_findSolution;
	}
private:
	int d_maxL;
	std::vector<std::string> d_words;
	std::string d_result;
	std::unordered_map<char, int> d_map;
	std::unordered_set<char> d_initials;
	bool d_findSolution;
	void init(std::vector<std::string>& words, std::string& result)
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
				d_initials.insert(word[word.length()-1]);
			}
			for(int j = 0; j < d_result.length(); ++j)
			{
				char c = d_result[j];
				d_map[c] = -1;
			}
			d_initials.insert(d_result[d_result.length()-1]);
	}
	void searchSolution()
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

				if(columnFinish)
				{
					if(offset == d_maxL-1)
					{
						d_findSolution = true;
						return;
					}
					++offset;
					carryOnMap[offset] = carryOn;
					bool initSuccess = initNewColumn(offset, states, availableDigits);
					if(!initSuccess)
					{
						if(states.empty())
						{
							d_findSolution = false;
							return;
						}
						backTrace(offset, states, resultAssignment, availableDigits, carryOn, carryOnMap);	
					}
				}
				else
				{
						if(states.empty())
						{
							d_findSolution = false;
							return;
						}
					backTrace(offset, states, resultAssignment, availableDigits, carryOn, carryOnMap);
				}
			}	
	}
	void columnSearch(int& offset, std::set<int>& availableDigits, std::stack<std::stack<char> >& states, std::unordered_map<int, char>& resultAssignment, int& carryOn, bool& columnFinish)
	{
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
								columnFinish = true;
								carryOn = newCarryOn;
								return;
							}
						}
						else
						{
						}
					}
				}
				
				auto riter = resultAssignment.find(offset);
				if(riter != resultAssignment.end())
				{
					int v = riter->first;
					char c = riter->second;
					d_map[c] = -1;
					availableDigits.insert(v);
					resultAssignment.erase(riter);
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
							if(d_initials.find(c) != d_initials.end() && *iter == 0)
							{
								++iter;
								if(iter == availableDigits.end())
								{
									iter = availableDigits.begin();
								}
							}
							d_map[c] = *iter;
							state.push(c);
							availableDigits.erase(iter);
						}
					}
				}
			}
	}
	void initAllDigits(std::set<int>& availableDigits)
	{
			availableDigits.clear();
			for(int i = 0; i <= 9; ++i)
			{
				availableDigits.insert(i);
			}
	}
	int getMaxLength()
	{
			int L = 0;
			for(int i = 0; i < d_words.size(); ++i)
			{
				L = (d_words[i].length() > L ? d_words[i].length() : L);
			}
			L = d_result.length() > L ? d_result.length(): L;
			return L;
	}
	bool initNewColumn(int& offset, std::stack<std::stack<char> >& states, std::set<int>& availableDigits)
	{
			std::stack<char> columnState;
			while(true)
			{
				bool initSuccess = true;
				for(int i = 0; i < d_words.size(); ++i) 
				{
					std::string word = d_words[i];
					if(offset < word.length())
					{
						char c = word[offset];
						if(d_map[c] == -1)
						{
							auto iter = availableDigits.begin();
							if(d_initials.find(c) != d_initials.end() && *iter == 0)
							{
								++iter;
								if(iter == availableDigits.end())
								{
									initSuccess = false;
									break;
								}
							}
							d_map[c] = *iter;
							availableDigits.erase(iter);
							columnState.push(c);
						}
					}
				}
				if(initSuccess)
				{
					states.push(columnState);
					return true;
				}
				else
				{
					while(!columnState.empty())
					{
						char c = columnState.top();
						columnState.pop();
						int v = d_map[c];
						d_map[c] = -1;
						availableDigits.insert(v);
						auto iter = availableDigits.find(v);
						++iter;
						if(iter == availableDigits.end())
						{
							continue;
						}
						else
						{
							d_map[c] = *iter;
							availableDigits.erase(iter);
							columnState.push(c);
							break;
						}
					}
					if(columnState.empty())
					{
						states.push(columnState);
						return false;
					}
				}
			}
			return true;
	}
	void backTrace(int& offset, std::stack<std::stack<char> >& states, std::unordered_map<int, char>& resultAssignment, std::set<int>& availableDigits, int& carryOn, std::unordered_map<int, int>& carryOnMap)
	{
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
			}
				
			--offset;
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
						bool fillSuccess = true;
						for(size_t i = 0; i < d_words.size(); ++i)
						{
							std::string word = d_words[i];
							if(offset < word.length())
							{
								char c = word[offset];
								if(d_map[c] == -1)
								{
									auto iter = availableDigits.begin();
									if(d_initials.find(c) != d_initials.end() && *iter == 0)
									{
										++iter;
									}
									if(iter == availableDigits.end())
									{
										fillSuccess = false;
										break;
									}
									d_map[c] = *iter;
									availableDigits.erase(iter);
									state.push(c);
								}
							}		
						}
						if(fillSuccess)
						{
							break;
						}
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
};

#endif
