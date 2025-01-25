# Define the top-level directory for libpng
LIBPNG=./libpng-1.6.45

# Compiler and flags
CXX=g++
CXXFLAGS=-Wall -I$(LIBPNG) -L$(LIBPNG) -lpng

# Source and object files
SRCS=fernPNG.cpp pngWriter.cpp point.cpp transform.cpp
OBJS=$(SRCS:.cpp=.o)

# Target executable
TARGET=fernPNG

# Default target
all: $(TARGET)

# Rule to build the executable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Rule for building object files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean target to remove generated files
clean:
	rm -f $(OBJS) $(TARGET)

# Phony targets
.PHONY: all clean

