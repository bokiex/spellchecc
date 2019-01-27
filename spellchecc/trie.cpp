#include "stdafx.h"
#include "trie.h"
#include <string>

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

	for (int i = 0; i < key.length(); i++)
	{
		if (node->children[key[i]] == nullptr)
		{
			node->children[key[i]] = new Trie();
		}

		node = node->children[key[i]];
	}

	// mark last node as leaf
	node->isEndOfWord = true;
}

bool Trie::search(std::string key)
{
	Trie *node = this;

	for (int i = 0; i < key.length(); i++)
	{
		node = node->children[key[i]];

		if (node == nullptr) return false;
	}

	return node->isEndOfWord;
}

Trie* Trie::traverse(std::string key)
{
	Trie *node = this;

	for (int i = 0; i < key.length(); i++)
	{
		node = node->children[key[i]];
	}

	return node;
}

bool Trie::isLastNode(Trie* t)
{
	for (Trie* c : t->children)
	{
		if (c) return false;
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
		if (t->children[i])
		{
			key.push_back((char)i);

			searchPrefix(t->children[i], key);
			key.pop_back();
		}
	}
}
