#include "trie.h"
#include <iostream>

std::string check(bool flag)
{
	return flag ? "yes" : "no";
}

int main()
{
	Trie trie("data/input.txt");
	
	std::cout << "file contains by? " << check( trie.contains("by") ) << std::endl;
	std::cout << "file contains sells? " << check( trie.contains("sells") ) << std::endl;
	std::cout << "file contains sell? " << check( trie.contains("sell") ) << std::endl;
	std::cout << "file contains shore? " << check( trie.contains("shore") ) << std::endl;
	std::cout << "file contains the? " << check( trie.contains("the") ) << std::endl;
	std::cout << "file contains abc? " << check( trie.contains("abc") ) << std::endl;
	std::cout << "file contains sea? " << check( trie.contains("sea") ) << std::endl;


	trie.deleteKey("sells");
	std::cout << "file contains sells? " << check( trie.contains("sells") ) << std::endl;
	std::cout << "file contains sea? " << check( trie.contains("sea") ) << std::endl;

	trie.deleteKey("by");
	std::cout << "file contains sells? " << check( trie.contains("sells") ) << std::endl;
	std::cout << "file contains sea? " << check( trie.contains("sea") ) << std::endl;
	std::cout << "file contains by? " << check( trie.contains("by") ) << std::endl;
	std::cout << "file contains bye? " << check( trie.contains("bye") ) << std::endl;
	
	std::vector<std::string> keys = trie.getKeys();
	for(size_t i = 0; i < keys.size(); ++i)
	{
		std::cout << keys[i] << std::endl;
	}

	const std::string str = "select";
	std::cout << " The longest prefix of " << str << " is " << trie.longestPrefix(str) << std::endl;
	trie.addKey("sells", 1);
	std::cout << " The longest prefix of " << str << " is " << trie.longestPrefix(str) << std::endl;
	
	return 0;
}
