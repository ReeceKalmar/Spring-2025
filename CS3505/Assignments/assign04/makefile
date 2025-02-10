#Makefile for assignment 4.

#By Reece Kalmar
#02/07/2025


CXX = g++
CXXFLAGS = -Wall -fsanitize=address,undefined -g

TARGET = trieTest

SRCS = trie.cpp trieTest.cpp
HEADERS = trie.h

OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TARGET)
	./$(TARGET) words.txt queries.txt output.txt

clean:
	rm -f $(TARGET) *.o
