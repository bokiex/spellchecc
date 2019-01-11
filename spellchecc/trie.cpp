#include "trie.h"

const int ALPHABET_SIZE = 26;

// node attributes
struct TrieNode {
	struct TrieNode *children[ALPHABET_SIZE];

	// true if node represents the end of a word
	bool isEndOfWord;
};

// returns new trie node and initialises 26 null children
struct TrieNode *getNode(void) {
	
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

// 
