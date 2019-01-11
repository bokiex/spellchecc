#pragma once
#include <iostream>
#include <vector>
#include <string>

const int ALPHABET_SIZE = 26;

struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];

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