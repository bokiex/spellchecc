#include "trie.h"
#include <string>

const int ALPHABET_SIZE = 26;

// node attributes
struct TrieNode 
{
	struct TrieNode *children[ALPHABET_SIZE];

	// true if node represents the end of a word
	bool isEndOfWord;
};

// returns new trie node and initialises 26 null children
struct TrieNode *getNode(void) 
{
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

// loops through key and checks each 
// value to see if it exists
// if it doesnt, create a new node 
// else, node.isEndOfWord = true
void insert(struct TrieNode *root, std::string key) 
{
	struct TrieNode *node = root;

	for (auto i : key) {
		auto index = i - 'a';
		if (!node->children[index])
			node->children[index] = getNode();

		node = node->children[index];
	}

	// mark last node as leaf
	node->isEndOfWord = true;
}

bool search(struct TrieNode *root, std::string key) 
{
	struct TrieNode *node = root;

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