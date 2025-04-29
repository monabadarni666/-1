# Makefile for Square Matrix implementation
# Email: <your email here>

# Compiler settings
CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra -pedantic -g

# Source files
MAIN_SRC = Main.cpp SquareMat.cpp
TEST_SRC = Test.cpp SquareMat.cpp

# Object files
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Executable targets
MAIN_TARGET = SquareMatDemo
TEST_TARGET = SquareMatTest

# Default target
all: $(MAIN_TARGET) $(TEST_TARGET)

# Main program
$(MAIN_TARGET): $(MAIN_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Test program
$(TEST_TARGET): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Compile source files
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Run the main program
Main: $(MAIN_TARGET)
	./$(MAIN_TARGET)

# Run the tests
test: $(TEST_TARGET)
	./$(TEST_TARGET)

# Check for memory leaks
valgrind: $(MAIN_TARGET)
	valgrind --leak-check=full --show-leak-kinds=all ./$(MAIN_TARGET)

# Clean up
clean:
	rm -f *.o $(MAIN_TARGET) $(TEST_TARGET)

.PHONY: all Main test valgrind clean
