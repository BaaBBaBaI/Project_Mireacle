# Makefile for contest1

# Compiler
CXX = g++

# Source files
SOURCES = basic.cpp nonbsic.cpp verynobasic.cpp

# Executables
EXECUTABLES = basic nonbsic verynobasic

# Default target
all: $(EXECUTABLES)

# Rule to compile each source file into an executable
%: %.cpp
	$(CXX) -o $@ $<

# Clean up generated files
clean:
	rm -f $(EXECUTABLES)
