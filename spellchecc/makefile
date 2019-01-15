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

$(TARGET): $(OBJS)
	g++ -std=c++11 $(CFLAGS) $(OBJS) -o $(TARGET)

spellchecc.o: spellchecc.cpp
	g++ -std=c++11 -c spellchecc.cpp

trie.o: trie.cpp trie.h
	g++ -std=c++11 -c trie.cpp

clean:
	rm *.o spellchecc
