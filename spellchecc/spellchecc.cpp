// spellchecc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "trie.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::string letters = "abcdefghijklmnopqrstuvxyz";

// converts a given string to its lowercase form
std::string to_lowercase(std::string s)
{
	std::string lower;
	for (char c : s)
	{
		if (c >= 'A' && c <= 'Z') lower.push_back(c + 32);
		else lower.push_back(c);
	}

	return lower;
}

bool loadDictionary(Trie *dict) {
	std::ifstream dictionary;
	dictionary.open("dictionary10KR.txt");

	std::string word;
	while (dictionary.good()) {
		getline(dictionary, word);
 		dict->insert(word);
	}

	return true;
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

void checkError(Trie* dict, std::string input)
{
	auto splits = getSplits(input);

	// create all possible corrections (for deletion and transposition error)
	std::vector<std::string> possibleCorrections;
	for (std::pair<std::string, std::string> p : splits)
	{
		// deletion
		for (char c : letters)
		{ possibleCorrections.push_back(p.first + c + p.second); }

		// transposition
		if ((p.second).length() > 1)
		{
			possibleCorrections.push_back(
				p.first + p.second[1] + p.second[0] + (p.second).substr(2)
			);
		}
	}

	// create all possible corrections (for substitution & insertion error)
	for (int i = 0; i < input.length(); i++)
	{
		for (char c : letters)
		{
			// substitution
			possibleCorrections.push_back(input.substr(0, i) + c + input.substr(i + 1));

			// insertion
			possibleCorrections.push_back(input.substr(0, i) + input.substr(i + 1));
		}
	}



	// check all possible corrections against dictionary and appends to results vector
	std::vector<std::string> results;
	for (std::string s : possibleCorrections)
	{

		if (dict->search(s))
		{
			if ((std::find(results.begin(), results.end(), s) == results.end())) {
				results.push_back(s);
			}

		}
	}

	// prints results 
	if (results.size() == 0) {
		std::cout << "not found :-(" << std::endl << std::endl;
	}
	else if (results.size() == 1) {
		std::cout << "Did you mean " << results[0] << "?" << std::endl << std::endl;
	}
	else {
		std::cout << "Did you mean " << results[0];
		for (int i = 1; i < results.size(); i++) {
			if (i == 4) { break; }
			std::cout << ", " << results[i];
		}
		if (results.size() > 4) { std::cout << " or " << results[5] << "?" << std::endl << std::endl; }
		else{ std::cout << " or " << results[results.size() - 1] << "?" << std::endl << std::endl; }
		
	}
}

void checkFile(Trie* dict, std::string path)
{
	std::ifstream file;
	file.open(path);

	std::cout << "Listing wrongly spelled words..." << std::endl;

	std::string word;
	while (!file.eof()) {
		std::getline(file, word);
		
		if (!dict->search(word)) {
			std::cout << word << " - Perhaps you meant: ";
			checkError(dict, word);
		}
	}

	std::cout << std::endl;


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
		std::cout << "Enter your option: ";
		std::cin >> option;

		if (option == 0){
			return false;
		}
		else if (option == 1) {
			std::cout << "Word to check: ";
			std::cin.ignore();

			getline(std::cin, input);

			bool found = dict->search(to_lowercase(input));
			if (found) { std::cout << "found!" << std::endl; }
			else
			{ checkError(dict, to_lowercase(input)); }
		}
		else if (option == 2) {
			std::cout << "Input the filepath to spellcheck: ";
			std::cin >> input;
			checkFile(dict, input);
		}
		else if (option == 3) {
			std::cout << "What's the word?" << std::endl;
			std::cin >> input;
			addNewWord(to_lowercase(input));
			std::cout << "Added!" << std::endl;
		}
		else if (option == 4){
			std::cout << "Prefix to search for: ";
			std::cin >> input;
			Trie* n = dict->traverse(to_lowercase(input));
			if (n == nullptr)
			{ std::cout << "Nothing found :-(" << std::endl; }
			else
			{ dict->searchPrefix(n, to_lowercase(input)); }
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
