#include "stdafx.h"
#include <iostream>
#include <string>

const int ALPHABET_SIZE = 26;

class Trie 
{
private:
	Trie* children[ALPHABET_SIZE];

	// true if node represents the end of a word
	bool isEndOfWord = false;
public:

	Trie();

	void insert(std::string key);

	bool search(std::string key);

	Trie* traverse(std::string key);

	bool isLastNode(Trie* t);

	void searchPrefix(Trie* t, std::string key);
};
