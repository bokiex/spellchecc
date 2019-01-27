// spellchecc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "trie.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const std::string LETTERS = "abcdefghijklmnopqrstuvxyz";
const std::string DICTIONARY = "dictionary10KR.txt";

/*
Takes in a trie node and appends the dictionary into the node
*/
void loadDictionary(Trie* dict)
{
	std::ifstream dictionary;
	dictionary.open(DICTIONARY);

	std::string word;
	while (dictionary.good()) {
		getline(dictionary, word);
 		dict->insert(word);
	}
}

/*
Takes in a string
Returns the given string as its lowercase form

*/
std::string to_lowercase(std::string s)
{
	std::string lower;
	for (char c : s)
		(c >= 'A' && c <= 'Z') ? lower.push_back(c + 32) : lower.push_back(c);

	return lower;
}

/* 
Takes in a string
Returns all possible splits of the string
*/
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

/*
Checks the input string against the dictionary for the type of error. 
Prints out all possible words.
Takes in a trie node and a string
*/
void checkError(Trie* dict, std::string input)
{
	auto splits = getSplits(input);

	// create all possible corrections (for deletion and transposition error)
	std::vector<std::string> possibleCorrections;
	for (std::pair<std::string, std::string> p : splits)
	{
		// deletion
		for (char c : LETTERS)
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
		for (char c : LETTERS)
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
	else {
		std::cout << "Did you mean ";
		for (int i = 0; i < results.size(); i++) {
			std::cout << results[i];

			if (results.size() == 1) continue;
			else if (i == results.size()-2)
			{ std::cout << " or ";}
			else if (i == results.size()-1)
			{ std::cout << "?" << std::endl; }
			else 
			{ std::cout << ", "; }
		}
	}
}

/*
Check the file provided via string for errors against the dictionary trie. 
Prints out all error words
Takes in a trie node and a string
*/
void checkFile(Trie* dict, std::string path)
{
	std::ifstream file;
	file.open(path);

	if (file.fail()) {
		std::cout << "File not found!" << std::endl;
	}
	else {
		std::cout << "Listing wrongly spelled words..." << std::endl;

		std::string word;
		while (!file.eof()) {
			std::getline(file, word);

			if (!dict->search(word)) {
				std::cout << word << " - Perhaps you meant: ";
				checkError(dict, word);
			}
		}

		std::cout << "Thanks for using FileChecker2.0!" << std::endl;
	}
	
}

/*
Checks whether string already exists in dictionary, if it is, prints error message.
Appends new string into dictionary trie.
Takes in a trie node and a string
*/
void addNewWord(Trie* dict, std::string str)
{
	if (dict->search(str))
	{ std::cout << str << " is already in the dictionary!" << std::endl; }
	else
	{
		std::ofstream dictionary;
		dictionary.open(DICTIONARY, std::ios_base::app);

		dictionary << str << std::endl;
		dictionary.close();

		std::cout << str << " added to the dictionary!" << std::endl;
	}
}

int main()
{
	// Create a trie to hold the words
	Trie* dict = new Trie;

	// Load the words into dict
	loadDictionary(dict);

	while (true) {
		// Display the menu
		std::cout << "------- Main Menu -------" << "\n"
			  << "[1] Spell check a word" << "\n"
			  << "[2] Spell check a file" << "\n"
			  << "[3] Add a new word" << "\n"
			  << "[4] Save (& reload) the dictionary" << "\n"
			  << "[5] Search with a prefix" << "\n"
			  << "[0] Quit" << std::endl;

		// Get user input
		int option;
		std::string input;
		std::cout << "Enter your option: ";
		std::cin >> option;

		// Handle user input
		if (option == 0) return 0;
		else if (option == 1) 
		{
			std::cout << "Word to check: ";
			std::cin.ignore();

			getline(std::cin, input);

			bool found = dict->search(to_lowercase(input));
			if (found) { std::cout << "found!" << std::endl; }
			else
			{ checkError(dict, to_lowercase(input)); }
		}
		else if (option == 2) 
		{
			std::cout << "Input the filepath to spellcheck: ";
			std::cin >> input;

			checkFile(dict, input);
		}
		else if (option == 3) 
		{
			std::cout << "What's the word? ";
			std::cin >> input;

			addNewWord(dict, to_lowercase(input));
		}
		else if (option == 4) loadDictionary(dict);
		else if (option == 5) 
		{
			std::cout << "Prefix to search for: ";
			std::cin >> input;

			Trie* n = dict->traverse(to_lowercase(input));
			if (n == nullptr)
			{ std::cout << "Nothing found :-(" << std::endl; }
			else
			{ dict->searchPrefix(n, to_lowercase(input)); }
		}
		else 
		{
			std::cout << "bAd oPtIoN" << std::endl;
			return 0;
		}
	}
}
