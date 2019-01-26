// spellchecc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "trie.h"
#include <iostream>
#include <fstream>
#include <string>

bool loadDictionary(Trie *dict) {
	std::ifstream dictionary;
	dictionary.open("RandomWords100.txt");

	if (!dictionary) {
		return false;
	}

	std::string word;
	while (!dictionary.eof()) {
		getline(dictionary, word);
 		dict->insert(word);
	}

	return true;
}

void checkFile(Trie* dict, std::string path)
{
	std::ifstream file;
	file.open(path);

	std::string line;
	while (!file.eof())
	{
		getline(file, line);
		if (!dict->search(line))
		{
			std::cout << line << " wasn't found in the dictionary!" << std::endl;
		}
	}
}

void addNewWord(std::string str)
{
	std::ofstream dictionary;
	dictionary.open("RandomWords100.txt", std::ios_base::app);

	dictionary << str << std::endl;
}

bool menu(Trie* dict) {

	while (true) {
		std::cout << "------- Main Menu -------" << std::endl;
		std::cout << "[1] Spell check a word" << std::endl;
		std::cout << "[2] Spellcheck a file" << std::endl;
		std::cout << "[3] Add a new word" << std::endl;
		std::cout << "[4] Search with a prefix" << std::endl;
		std::cout << "[0] Quit" << std::endl;

		int option;
		std::string input;
		std::cin >> option;

		if (option == 0){
			return false;
		}
		else if (option == 1) {
			std::cout << "Word to check: ";
			std::cin >> input;
			std::cout << (dict->search(input) ? "found!" : "not found :-(")
				<< std::endl;
			break;
		}
		else if (option == 2) {
			std::cout << "Input the filepath to spellcheck: ";
			std::cin >> input;
			checkFile(dict, input);
			break;
		}
		else if (option == 3) {
			std::cout << "What's the word?" << std::endl;
			std::cin >> input;
			addNewWord(input);
			std::cout << "Added!" << std::endl;
			break;
		}
		else if (option == 4){
			std::cout << "Prefix to search for: ";
			std::cin >> input;
			Trie* n = dict->traverse(input);
			if (n == nullptr)
			{
				std::cout << "Nothing found :-(" << std::endl;
			}
			else
			{
				dict->searchPrefix(n, input);
			}
			break;
		}
		else{
			std::cout << "bAd oPtIoN" << std::endl;
			return false;
		}
	}
}

int main()
{
	// Create a trie (named dict) to hold the words
	Trie* dict = new Trie;

	// Load the words into dict
	loadDictionary(dict);

	// Display the menu
	menu(dict);
}
