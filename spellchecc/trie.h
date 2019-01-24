#include "stdafx.h"
#include <iostream>

const int ALPHABET_SIZE = 128;

class Trie 
{
private:
	Trie* children[ALPHABET_SIZE];

	// true if node represents the end of a word
	bool isEndOfWord = false;
public:
	Trie() 
	{ 
		for (int i = 0; i < ALPHABET_SIZE; i++)
		{ children[i] = nullptr; }
       	}

	// loops through key and checks each 
	// value to see if it exists
	// if it doesnt, create a new node 
	// else, node.isEndOfWord = true
	void insert(std::string key)
	{
		Trie* node = this;

		for (int i = 0; i < key.length(); i++) {
			// ignore if i = \n
			if (!isalpha(key[i])) continue;

			if (node->children[key[i]] == nullptr)
			{
				node->children[key[i]] = new Trie();
			}
			node = node->children[key[i]];
		}

		// mark last node as leaf
		node->isEndOfWord = true;
	}

	bool search(std::string key)
	{
		Trie *node = this;

		for (int i = 0; i < key.length(); i++) 
		{
			node = node->children[key[i]];

			if (node == nullptr) return false;
		}

		return node->isEndOfWord;
	}
};
