#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>

const int ALPHABET_SIZE = 26;

// node attributes
struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];

	// true if node represents the end of a word
	bool isEndOfWord;
};

class Trie 
{
private:
	TrieNode * root;
public:
	Trie();

	void insert(std::string str);
	bool search(std::string str);
};