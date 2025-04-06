# Author: realyoavperetz@gmail.com

# Default build: compile both targets
.PHONY: all
all: Main test

# Compile and run Main
.PHONY: main
main: Main
	./Main

Main: Main.cpp \
	source/Graph.cpp source/Algorithms.cpp source/Queue.cpp \
	source/PriorityQueue.cpp source/UnionFind.cpp
	g++ -Wall -Wextra -std=c++17 -Iinclude \
	Main.cpp \
	source/Graph.cpp source/Algorithms.cpp source/Queue.cpp \
	source/PriorityQueue.cpp source/UnionFind.cpp \
	-o Main

# Compile and run test
.PHONY: test
test: test.exe
	./test.exe

test.exe: tests/test.cpp \
	source/Graph.cpp source/Algorithms.cpp source/Queue.cpp \
	source/PriorityQueue.cpp source/UnionFind.cpp
	g++ -Wall -Wextra -std=c++17 -Iinclude \
	tests/test.cpp \
	source/Graph.cpp source/Algorithms.cpp source/Queue.cpp \
	source/PriorityQueue.cpp source/UnionFind.cpp \
	-o test.exe

# Run valgrind on tests
.PHONY: valgrind
valgrind: test.exe
	valgrind ./test.exe

# Clean build files
.PHONY: clean
clean:
	rm -f Main test.exe source/*.o