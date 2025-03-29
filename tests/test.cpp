// Author: realyoavperetz@gmail.com
// This file contains unit tests for the Graph project using doctest
// Each test case checks the correctness and robustness of Graph methods and algorithms

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/Graph.hpp"
#include "../include/Algorithms.hpp"

using namespace graph;

TEST_CASE("Graph addEdge and getNeighbors") {
    Graph g(3);

    // Add edges to the graph
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, 2);

    // Check neighbors of vertex 0
    Neighbor* n0 = g.getNeighbors(0);
    CHECK(n0 != nullptr);
    CHECK(n0->vertex == 1);
    CHECK(n0->weight == 5);

    // Check neighbors of vertex 1 for both connections
    Neighbor* n1 = g.getNeighbors(1);
    bool found0 = false, found2 = false;
    while (n1) {
        if (n1->vertex == 0 && n1->weight == 5) found0 = true;
        if (n1->vertex == 2 && n1->weight == 2) found2 = true;
        n1 = n1->next;
    }
    CHECK(found0);
    CHECK(found2);
}

TEST_CASE("Graph removeEdge") {
    Graph g(3);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, 2);

    // Remove edge (0, 1)
    g.removeEdge(0, 1);

    // Check that edge was removed from both sides
    Neighbor* n0 = g.getNeighbors(0);
    while (n0) {
        CHECK(n0->vertex != 1);
        n0 = n0->next;
    }

    Neighbor* n1 = g.getNeighbors(1);
    while (n1) {
        CHECK(n1->vertex != 0);
        n1 = n1->next;
    }
}

TEST_CASE("Graph invalid edge operations") {
    Graph g(2);

    // Test adding/removing edges with invalid indices
    CHECK_THROWS(g.addEdge(0, 3, 1));
    CHECK_THROWS(g.removeEdge(0, 3));
    CHECK_THROWS(g.getNeighbors(3));
}

TEST_CASE("BFS correctness") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);

    // Run BFS and check structure
    Graph bfsTree = Algorithms::bfs(g, 0);
    CHECK(bfsTree.getNumVertices() == 4);

    // Check that 2 is connected to 1 (shortest path)
    Neighbor* n = bfsTree.getNeighbors(2);
    bool validParent = false;
    while (n) {
        if (n->vertex == 1) validParent = true;
        n = n->next;
    }
    CHECK(validParent);
}

TEST_CASE("DFS correctness") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);

    // Run DFS and check structure
    Graph dfsTree = Algorithms::dfs(g, 0);
    CHECK(dfsTree.getNumVertices() == 4);

    // Check that 3 is reachable through a tree edge from 2
    Neighbor* n = dfsTree.getNeighbors(3);
    bool connected = false;
    while (n) {
        if (n->vertex == 2) connected = true;
        n = n->next;
    }
    CHECK(connected);
}

TEST_CASE("Dijkstra shortest path tree") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 10);
    g.addEdge(2, 3, 1);

    // Run Dijkstra from vertex 0
    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    CHECK(dijkstraTree.getNumVertices() == 4);

    // Check that 2 was reached through 1 (cheapest path)
    Neighbor* n = dijkstraTree.getNeighbors(2);
    bool from1 = false;
    while (n) {
        if (n->vertex == 1) from1 = true;
        n = n->next;
    }
    CHECK(from1);
}

TEST_CASE("Prim MST") {
    Graph g(4);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 2);

    // Run Prim and check MST weight
    Graph mst = Algorithms::prim(g);
    CHECK(mst.getNumVertices() == 4);

    int totalWeight = 0;
    for (int i = 0; i < 4; ++i) {
        Neighbor* n = mst.getNeighbors(i);
        while (n) {
            totalWeight += n->weight;
            n = n->next;
        }
    }
    CHECK(totalWeight / 2 == 6); // edges are undirected
}

TEST_CASE("Kruskal MST") {
    Graph g(4);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 2);

    // Run Kruskal and check MST weight
    Graph mst = Algorithms::kruskal(g);
    CHECK(mst.getNumVertices() == 4);

    int totalWeight = 0;
    for (int i = 0; i < 4; ++i) {
        Neighbor* n = mst.getNeighbors(i);
        while (n) {
            totalWeight += n->weight;
            n = n->next;
        }
    }
    CHECK(totalWeight / 2 == 6); // edges are undirected
}