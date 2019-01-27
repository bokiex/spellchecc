#include "stdafx.h"
#include <string>

const int ALPHABET_SIZE = 26;
const std::string LETTERS = "abcdefghijklmnopqrstuvwxyz";

class Trie 
{
private:
	Trie* children[ALPHABET_SIZE];

	// true if node represents the end of a word
	bool isEndOfWord = false;

	int getIndex(std::string s);
public:

	Trie();

	void insert(std::string key);

	bool search(std::string key);

	Trie* traverse(std::string key);

	bool isLastNode(Trie* t);

	void searchPrefix(Trie* t, std::string key);
};
