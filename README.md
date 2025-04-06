# Graph Algorithms Project – System Programming 2

Author: [realyoavperetz@gmail.com]  
Course: System Programming 2  
Topic: Graphs

---

##  Project Description

This project implements an undirected graph using an **adjacency list**, and includes classical graph algorithms such as:

- **BFS** – Breadth-First Search
- **DFS** – Depth-First Search
- **Dijkstra** – Single-source shortest paths
- **Prim** – Minimum Spanning Tree (greedy)
- **Kruskal** – Minimum Spanning Tree using Union-Find

All code is written in **C++** using only **raw arrays and pointers**, without any use of STL containers like `vector`, `queue`, or `set`.

- **Unit Testing:** Built with doctest
- **Memory Management:** Fully manual (`new`, `delete`), validated with **Valgrind**
- **No STL:** All data structures (queue, priority queue, union-find, sorting) are implemented manually
---

##  Folder Structure
```plaintext
.
├── include/          # Header files (.h/.hpp)
│   ├── Graph.hpp
│   ├── Algorithms.hpp
│   ├── Queue.hpp
│   ├── PriorityQueue.hpp
│   └── UnionFind.hpp
│
├── source/              # Implementation files (.cpp)
│   ├── Graph.cpp
│   ├── Algorithms.cpp
│   ├── Queue.cpp
│   ├── PriorityQueue.cpp
│   └── UnionFind.cpp
│
├── tests/            # Unit test file (doctest-based)
│   └── test.cpp
│
├── Main.cpp          # Interactive demo
├── Makefile          # Program builder 
└── README.md         # This file
```
---

##  Build Instructions

###  Build the main demo
To compile and run the main program:
```bash
make
./Main
```

###  Run tests
To compile and run the unit tests:
```bash
make test
./test
```

###  Run memory checks with Valgrind
To check for memory leaks:
```bash
make valgrind
```

###  Clean build files
To remove all executables and object files:
```bash
make clean
```



