// spellchecc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "trie.h"
#include <iostream>
#include <fstream>
#include <vector>

const std::string letters = "abcdefghijklmnopqrstuvxyz";

bool loadDictionary(Trie *dict) {
	std::ifstream dictionary;
	dictionary.open("RandomWords100.txt");

	if (!dictionary) {
		return false;
	}

	std::string word;
	while (dictionary.good()) {
		getline(dictionary, word);
 		dict->insert(word);
	}

	return true;
}

void checkFile(Trie* dict, std::string path)
{
	std::ifstream file;
	file.open(path, std::ios::binary);

	std::string line;
	while (file.good())
	{
		getline(file, line);
		if (!dict->search(line))
		{ std::cout << line << " wasn't found in the dictionary!" << std::endl; }
	}
}

void addNewWord(std::string str)
{
	std::ofstream dictionary;
	dictionary.open("RandomWords100.txt", std::ios_base::app);

	dictionary << str << std::endl;
}

// returns all possible splits of the input
std::vector<std::pair<std::string, std::string>> getSplits(std::string input)
{
	auto splits = std::vector<std::pair<std::string, std::string>>();
	for (int i = 0; i <= input.length(); i++)
	{
		splits.push_back(*new std::pair<std::string, std::string>(
					input.substr(0, i),
					input.substr(i)			
			));
	}

	return splits;	
}

void checkDeletion(Trie* dict, std::string input)
{
	auto splits = getSplits(input);

	// create all possible corrections (for a deletion error)
	std::vector<std::string> results;
	for (std::pair<std::string, std::string> p : splits)
	{
		for (char c : letters)
		{ results.push_back(p.first + c + p.second); }
	}

	// check all possible corrections against dictionary
	for (std::string s : results)
	{
		if (dict->search(s))
		{
			std::cout << "Did you mean " << s << "?" << std::endl;
			break;
		}
	}
}

void checkSubstitution(Trie* dict, std::string input)
{
	auto splits = getSplits(input);

	// create all possible corrections (for a substitution error)
	std::vector<std::string> results;
	for (int i = 0; i < input.length(); i++)
	{
		for (char c : letters)
		{
			results.push_back(input.substr(0, i) + c + input.substr(i+1));
		}
	}

	// check all possible corrections against the dictionary
	for (std::string s : results)
	{
		if (dict->search(s))
		{
			std::cout << "Did you mean " << s << "?" << std::endl;
			break;
		}
	}
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

		switch (option) {
		case 0:
			return false;
		case 1:
		{
			std::cout << "Word to check: ";
			std::cin >> input;
			bool found = dict->search(input);
			if (found) std::cout << "found!" << std::endl;
			else
			{
				// check for deletion error
				checkDeletion(dict, input);

				// check for substitution error
				checkSubstitution(dict, input);
			}
			break;
		}
		case 2:
			std::cout << "Input the filepath to spellcheck: ";
			std::cin >> input;
			checkFile(dict, input);
			break;
		case 3:
			std::cout << "What's the word?" << std::endl;
			std::cin >> input;
			addNewWord(input);
			std::cout << "Added!" << std::endl;
			break;
		case 4:
		{
			std::cout << "Prefix to search for: ";
			std::cin >> input;
			Trie* n = dict->traverse(input);
			if (n == nullptr)
			{ std::cout << "Nothing found :-(" << std::endl; }
			else
			{ dict->searchPrefix(n, input); }
			break;
		}
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

	// Display the menu
	menu(dict);
}
