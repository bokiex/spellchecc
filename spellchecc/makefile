# the compiler- g++ for c++
CC = g++

# compiler flags:
#  -g		adds debugging information to the executable file
#  -Wall	turns on most compiler warnings
CFLAGS = -g -Wall

# the build target executable
TARGET = spellchecc

# relevant object files to go into the executable
OBJS = spellchecc.o trie.o


all: $(TARGET) 

$(TARGET): $(OBJS)
	g++ --std=c++11 -o $(TARGET) $(OBJS)

spellchecc.o: spellchecc.cpp
	g++ --std=c++11 spellchecc.cpp -o spellchecc.o

trie.o: trie.cpp trie.h
	g++ --std=c++11 trie.cpp -c -o trie.o
