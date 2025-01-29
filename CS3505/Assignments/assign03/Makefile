# Define the top-level directory for libpng
LIBPNG=../../../libpng-1.6.45

# Compiler and flags
CXX=g++
CXXFLAGS=-Wall -I$(LIBPNG) -Iinclude
LDFLAGS=-L$(LIBPNG) -lpng

# Source and object files
SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:src/%.cpp=%.o)

# Target executable
TARGET=fernPNG

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $@

# Rule for building object files
%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f *.o $(TARGET)

# Phony targets
.PHONY: all clean

