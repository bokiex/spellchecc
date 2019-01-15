all: spellchecc

spellchecc: spellchecc.o trie.o
	g++ --std=c++11 -o spellchecc spellchecc.o trie.o

spellcheck.o: spellchecc.cpp
	g++ --std=c++11 spellchecc.cpp -o spellchecc.o

trie.o: trie.cpp trie.h
	g++ --std=c++11 trie.cpp -c -o trie.o
