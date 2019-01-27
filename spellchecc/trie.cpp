#include "stdafx.h"
#include "trie.h"
#include "help.h"
#include <iostream>

// constructs the trie
// initialises all elements in children to nullptr
Trie::Trie()
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{ children[i] = nullptr; }
}

// inserts a user provided string to the trie
// key: the string to be inserted
void Trie::insert(std::string key){
	Trie* node = this;

	int index;
	for (int i = 0; i < key.length(); i++)
	{
		index = help::getIndex(key[i]);
		if (node->children[index] == nullptr)
			node->children[index] = new Trie;

		node = node->children[index];
	}

	// mark last node as leaf
	node->isEndOfWord = true;
}

// searches for a user provided string in the trie
// key: the string to search for
// 
// returns true if the string is found & false otherwise
bool Trie::search(std::string key)
{
	Trie *node = this;

	for (int i = 0; i < key.length(); i++)
	{
		node = node->children[help::getIndex(key[i])];

		if (node == nullptr) return false;
	}

	return node->isEndOfWord;
}

// returns a pointer to a trie node representative of the end of the user provided string
// key: the string to traverse through
//
// returns the requested pointer
Trie* Trie::traverse(std::string key)
{
	Trie *node = this;

	for (int i = 0; i < key.length(); i++)
		node = node->children[help::getIndex(key[i])];

	return node;
}

// checks if the provided node is a leaf node
// t: the trie node to check
//
// returns true if the provided node is a leaf node & false otherwise
bool Trie::isLastNode(Trie* t)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
		if (t->children[i] != nullptr) return false;

	return true;
}

// searches for all strings with the given string as prefix & prints them
// t: the starting point of the search
// key: the prefix to search for 
void Trie::searchPrefix(Trie* t, std::string key)
{
	// word found! print!
	if (t->isEndOfWord)
		std::cout << key << std::endl;

	// end of trie reached. return.
	if (isLastNode(t)) return;

	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (t->children[i] != nullptr)
		{
			key.push_back(LETTERS[i]);
	
			searchPrefix(t->children[i], key);
			key.pop_back();
		}
	}
}
