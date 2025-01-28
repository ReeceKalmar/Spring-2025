# Define the top-level directory for libpng
LIBPNG=./libpng-1.6.45

# Compiler and flags
CXX=g++
CXXFLAGS=-Wall -I$(LIBPNG) -Iinclude -L$(LIBPNG) -lpng

# Source and object files
SRCS=$(wildcard src/*.cpp)
OBJS=$(SRCS:src/%.cpp=build/%.o)

# Target executable
TARGET=build/fernPNG

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule for building object files
build/%.o: src/%.cpp
	@mkdir -p build
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -rf build/

# Phony targets
.PHONY: all clean

