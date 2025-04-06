// Author: realyoavperetz@gmail.com

#include "../include/UnionFind.hpp"

using namespace graph;

// Constructor: initialize each element to be its own parent
UnionFind::UnionFind(int size) {
    this->size = size;
    parent = new int[size];
    rank = new int[size];

    for (int i = 0; i < size; ++i) {
        parent[i] = i;  // initially, each node is its own root
        rank[i] = 0;    // all trees start with depth 0
    }
}

// Destructor: free allocated memory
UnionFind::~UnionFind() {
    delete[] parent;
    delete[] rank;
}

// Find the root of x, with path compression optimization
int UnionFind::find(int x) {
    if (parent[x] != x) {
        parent[x] = find(parent[x]);  // flatten the tree
    }
    return parent[x];
}

// Union the sets of x and y by rank (attach smaller tree under larger)
void UnionFind::unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX == rootY) return;  // already connected

    // attach smaller tree under larger tree
    if (rank[rootX] < rank[rootY]) {
        parent[rootX] = rootY;
    } else if (rank[rootX] > rank[rootY]) {
        parent[rootY] = rootX;
    } else {
        parent[rootY] = rootX;
        rank[rootX]++;
    }
}

// Check if x and y are in the same set
bool UnionFind::connected(int x, int y) {
    return find(x) == find(y);
}