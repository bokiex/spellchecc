#pragma once
#include <iostream>
#include <vector>
#include <string>

class Trie 
{
private:
	TrieNode * root;
public:
	Trie();

	void insert(std::string str);
	bool search(std::string str);
};