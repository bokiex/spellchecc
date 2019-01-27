#include "stdafx.h"
#include "trie.h"
#include <string>

const std::string LETTERS = "abcdefghijklmnopqrstuvwxyz";

Trie::Trie(){
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		children[i] = nullptr;
	}
}

// loops through key and checks each 
// value to see if it exists
// if it doesnt, create a new node 
// else, node.isEndOfWord = true
void Trie::insert(std::string key){
	Trie* node = this;

	int index;
	for (int i = 0; i < key.length(); i++)
	{
		index = key[i] - 'a';

		if (node->children[index] == nullptr)
		{
			node->children[index] = new Trie;
		}

		node = node->children[index];
	}

	// mark last node as leaf
	node->isEndOfWord = true;
}

bool Trie::search(std::string key)
{
	Trie *node = this;

	int index;
	for (int i = 0; i < key.length(); i++)
	{
		index = key[i] - 'a';
		node = node->children[index];

		if (node == nullptr) return false;
	}

	return node->isEndOfWord;
}

Trie* Trie::traverse(std::string key)
{
	Trie *node = this;

	int index;
	for (int i = 0; i < key.length(); i++)
	{
		index = key[i] - 'a';
		node = node->children[index];
	}

	return node;
}

bool Trie::isLastNode(Trie* t)
{
	for (int i = 0; i < ALPHABET_SIZE; i++)
	{
		if (t->children[i] != nullptr) return false;
	}

	return true;
}

void Trie::searchPrefix(Trie* t, std::string key)
{
	// word found! print!
	if (t->isEndOfWord)
	{
		std::cout << key << std::endl;
	}

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
