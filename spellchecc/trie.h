/*
* trie.h
*
* Version: 1.1
* Authors: Sim Sheline (S0177516E) & Koh Bok Yan (S10179233J)
* URL: https://github.com/shleen, https://github.com/bokiex
*/

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
