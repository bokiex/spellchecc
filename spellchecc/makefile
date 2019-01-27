# the compiler- $(CC) for c++
CC = g++

# compiler flags:
#  -g		adds debugging information to the executable file
#  -Wall	turns on most compiler warnings
CFLAGS = -g -Wall

# the build target executable
TARGET = spellchecc

# relevant object files to go into the executable
OBJS = spellchecc.o trie.o help.o

$(TARGET): $(OBJS)
	$(CC) -std=c++17 $(CFLAGS) $(OBJS) -o $(TARGET)

spellchecc.o: spellchecc.cpp
	$(CC) -std=c++17 -c spellchecc.cpp

trie.o: trie.cpp trie.h
	$(CC) -std=c++17 -c trie.cpp

help.o: help.cpp help.h
	$(CC) -std=c++17 -c help.cpp

clean:
	rm *.o spellchecc
