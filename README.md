# Graph Algorithms Project – System Programming 2

📧 Author: [your_email@example.com]  
📁 Course: System Programming 2  
📚 Topic: Graph algorithms using adjacency list, no STL

---

## 🧠 Project Description

This project implements an undirected graph using an **adjacency list**, and includes classical graph algorithms such as:

- **BFS** – Breadth-First Search
- **DFS** – Depth-First Search
- **Dijkstra** – Single-source shortest paths
- **Prim** – Minimum Spanning Tree (greedy)
- **Kruskal** – Minimum Spanning Tree using Union-Find

All code is written in **modern C++ (C++17)** using only **raw arrays and pointers**, without any use of STL containers like `vector`, `queue`, or `set`.

Memory management is done manually using `new` and `delete`, and verified using Valgrind.

---

## 📁 Folder Structure
.
├── include/             # H++ Header files
├── src/                 # C++ implementations
├── tests/               # Unit tests (doctest-based)
├── Main.cpp             # Manual demo and integration test
├── Makefile              # Makefile system builder
├── README.md            # This file

---

## ⚙️ Build Instructions

### 🔨 Build the main demo
To compile and run the main program:
make
./Main

### ✅ Run unit tests
To compile and run the unit tests:
make test
./test

### 🧪 Run memory check with Valgrind
To check for memory leaks:
make valgrind

### 🧹 Clean build artifacts
To remove all executables and object files: