# Author: realyoavperetz@gmail.com
# Makefile for Graph Algorithms Project (System Programming 2)

# Default build: compile both targets
.PHONY: all
all: Main test

# Compile and run Main
.PHONY: main
main: Main
	./Main

Main: Main.cpp \
	src/Graph.cpp src/Algorithms.cpp src/Queue.cpp \
	src/PriorityQueue.cpp src/UnionFind.cpp
	g++ -Wall -Wextra -std=c++17 -Iinclude \
	Main.cpp \
	src/Graph.cpp src/Algorithms.cpp src/Queue.cpp \
	src/PriorityQueue.cpp src/UnionFind.cpp \
	-o Main

# Compile and run test
.PHONY: test
test: test.exe
	./test.exe

test.exe: tests/test.cpp \
	src/Graph.cpp src/Algorithms.cpp src/Queue.cpp \
	src/PriorityQueue.cpp src/UnionFind.cpp
	g++ -Wall -Wextra -std=c++17 -Iinclude \
	tests/test.cpp \
	src/Graph.cpp src/Algorithms.cpp src/Queue.cpp \
	src/PriorityQueue.cpp src/UnionFind.cpp \
	-o test.exe

# Run valgrind on tests
.PHONY: valgrind
valgrind: test.exe
	valgrind ./test.exe

# Clean artifacts
.PHONY: clean
clean:
	rm -f Main test.exe src/*.o