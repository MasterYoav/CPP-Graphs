// Author: realyoavperetz@gmail.com

#pragma once

namespace graph {

// Disjoint Set Union (Union-Find) with path compression and union by rank
class UnionFind {
private:
    int* parent; // parent[i] = parent of node i
    int* rank;   // rank[i] = depth estimate of the tree rooted at i
    int size;    // total number of elements

public:
    // Constructor: initializes n disjoint sets (0 to n-1)
    UnionFind(int size);

    // Destructor: free internal arrays
    ~UnionFind();

    // Find the root of the set containing x
    int find(int x);

    // Merge sets containing x and y
    void unite(int x, int y);

    // Check if x and y are in the same set
    bool connected(int x, int y);
};

}