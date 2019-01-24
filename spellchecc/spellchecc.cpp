// spellchecc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "trie.h"
#include <fstream>

bool loadDictionary(Trie *dict) {
	std::ifstream dictionary;
	dictionary.open("RandomWords100.txt");

	if (!dictionary) {
		return false;
	}

	std::string word;
	while (!dictionary.eof()) {
		getline(dictionary, word);
 		// dict->insert(word);
	}

	return true;
}

void addNewWord(std::string str)
{
	std::ofstream dictionary;
	dictionary.open("RandomWords100.txt", std::ios_base::app);

	dictionary << str << std::endl;
}

bool menu() {

	while (true) {
		std::cout << "------- Main Menu -------" << std::endl;
		std::cout << "[1] Spell check a word" << std::endl;
		std::cout << "[2] Spellcheck a file" << std::endl;
		std::cout << "[3] Add a new word" << std::endl;
		std::cout << "[4] Search with a prefix" << std::endl;
		std::cout << "[0] Quit" << std::endl;

		int option;
		std::string word;
		std::cin >> option;

		switch (option) {
		case 0:
			return false;
		case 1:
			break;
		case 3:
			std::cout << "What's the word?" << std::endl;
			std::cin >> word;
			addNewWord(word);
			std::cout << "Added!" << std::endl;
		default:
			std::cout << "bAd oPtIoN" << std::endl;
			break;
		}
	}
}

int main()
{
	// Create a trie (named dict) to hold the words
	Trie* dict = new Trie;

	// Load the words into dict
	loadDictionary(dict);

	std::cout << "HEllo" << std::endl;

	// Display the menu
	menu();
}
