CXX=g++
CXXFLAGS=-std=c++20 -Wall -Wextra -pedantic -Iinclude

Main: main.cpp include/ac/MyContainer.hpp
	$(CXX) $(CXXFLAGS) -o main main.cpp

test: tests.cpp include/ac/MyContainer.hpp
	$(CXX) $(CXXFLAGS) -o test tests.cpp
	./test

valgrind: Main
	valgrind --leak-check=full ./main

clean:
	rm -f main test *.o
