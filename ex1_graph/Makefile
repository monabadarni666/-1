# Makefile for Graph Assignment

CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes

# Source files
MAIN_SRC = main.cpp
TEST_SRC = tests.cpp
GRAPH_SRC = Graph.cpp
ALGO_SRC = Algorithms.cpp

# Header files
HEADERS = Graph.hpp Algorithms.hpp Utils.hpp

# Executables
MAIN_EXEC = main
TEST_EXEC = tests

# Default target
all: Main test

# Compile the main program
Main: $(MAIN_SRC) $(GRAPH_SRC) $(ALGO_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(MAIN_EXEC) $(MAIN_SRC) $(GRAPH_SRC) $(ALGO_SRC)
	./$(MAIN_EXEC)

# Compile the test program
test: $(TEST_SRC) $(GRAPH_SRC) $(ALGO_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_SRC) $(GRAPH_SRC) $(ALGO_SRC)
	./$(TEST_EXEC)

# Build main without running it (for valgrind)
build-main: $(MAIN_SRC) $(GRAPH_SRC) $(ALGO_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(MAIN_EXEC) $(MAIN_SRC) $(GRAPH_SRC) $(ALGO_SRC)

# Build tests without running them (for valgrind)
build-test: $(TEST_SRC) $(GRAPH_SRC) $(ALGO_SRC) $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $(TEST_EXEC) $(TEST_SRC) $(GRAPH_SRC) $(ALGO_SRC)

# Run valgrind on the main program
valgrind: build-main
	$(VALGRIND) ./$(MAIN_EXEC)

# Run valgrind on the test program
valgrind-test: build-test
	$(VALGRIND) ./$(TEST_EXEC)

# Clean up
clean:
	rm -f $(MAIN_EXEC) $(TEST_EXEC)

.PHONY: all Main test build-main build-test valgrind valgrind-test clean