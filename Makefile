# Author: realyoavperetz@gmail.com
# Makefile for Graph Algorithms Project (System Programming 2)

# Build the Main demo program
Main:
	g++ -Wall -Wextra -std=c++17 -Iinclude \
		Main.cpp \
	src/Graph.cpp \
	src/Algorithms.cpp \
	src/Queue.cpp \
	src/PriorityQueue.cpp \
	src/UnionFind.cpp \
	-o Main

# Build and run unit tests using doctest
Test:
	g++ -Wall -Wextra -std=c++17 -Iinclude \
	tests/test.cpp \
	src/Graph.cpp \
	src/Algorithms.cpp \
	src/Queue.cpp \
	src/PriorityQueue.cpp \
	src/UnionFind.cpp \
	-o test

# Run tests
.PHONY: test

test: Test
	./test

# Run valgrind on tests
.PHONY: valgrind

valgrind: Test
	valgrind ./test

# Clean all build artifacts
.PHONY: clean

clean:
	rm -f Main test src/*.o
