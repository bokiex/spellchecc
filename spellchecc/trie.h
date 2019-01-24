#include "stdafx.h"
#include <iostream>

const int ALPHABET_SIZE = 26;

// node attributes
struct TrieNode
{
	TrieNode* children[ALPHABET_SIZE];

	// true if node represents the end of a word
	bool isEndOfWord;
};

// returns new trie node and initialises 26 null children
struct TrieNode* getNode() 
{
	TrieNode* pNode = new TrieNode;

	for (TrieNode* n : pNode->children) { n = nullptr; }

	pNode->isEndOfWord = false;

	return pNode;
}

class Trie 
{
private:
	TrieNode* root;
public:
	Trie() { root = getNode(); }

	// loops through key and checks each 
	// value to see if it exists
	// if it doesnt, create a new node 
	// else, node.isEndOfWord = true
	void insert(std::string key)
	{
		TrieNode* node = root;

		for (int i = 0; i < key.length(); ++i) {
			// ignore if i = \n
			if (!isalpha(key[i])) continue;

			int index = key[i] - 'a';
			if (!node->children[index])
			{
				node->children[index] = getNode();
			} 

			node = node->children[index];
		}

		// mark last node as leaf
		node->isEndOfWord = true;
	}

	bool search(std::string key)
	{
		TrieNode *node = root;

		for (auto i : key) 
		{
			auto index = i - 'a';
			if (!node->children[index]) {
				return false;
			}
			node = node->children[index];
		}

		return (node != NULL && node->isEndOfWord);
	}
};
