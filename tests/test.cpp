// Author: realyoavperetz@gmail.com
// Unit tests for the Graph project using doctest
// Includes core functionality + edge cases for robustness

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../include/doctest.h"
#include "../include/Graph.hpp"
#include "../include/Algorithms.hpp"

using namespace graph;

// ----------------------------------------------------------
// Basic Functionality Tests for Graph
// ----------------------------------------------------------

// Check basic edge addition and neighbor retrieval
TEST_CASE("Graph addEdge and getNeighbors") {
    Graph g(3);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, 2);

    Neighbor* n0 = g.getNeighbors(0);
    CHECK(n0 != nullptr);
    CHECK(n0->vertex == 1);
    CHECK(n0->weight == 5);

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

// Ensure removeEdge removes from both sides
TEST_CASE("Graph removeEdge") {
    Graph g(3);
    g.addEdge(0, 1, 5);
    g.addEdge(1, 2, 2);
    g.removeEdge(0, 1);

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

// Check that invalid vertex access throws exception
TEST_CASE("Graph invalid vertex access") {
    Graph g(2);
    CHECK_THROWS(g.addEdge(0, 3, 1));
    CHECK_THROWS(g.removeEdge(0, 3));
    CHECK_THROWS(g.getNeighbors(3));
}

// ----------------------------------------------------------
// Algorithm Functional Tests
// ----------------------------------------------------------

// BFS should build tree in level-order
TEST_CASE("BFS correctness") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);

    Graph bfsTree = Algorithms::bfs(g, 0);
    CHECK(bfsTree.getNumVertices() == 4);

    Neighbor* n = bfsTree.getNeighbors(2);
    bool connectedTo1 = false;
    while (n) {
        if (n->vertex == 1) connectedTo1 = true;
        n = n->next;
    }
    CHECK(connectedTo1);
}

// DFS should connect in deep-first tree order
TEST_CASE("DFS correctness") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 1);

    Graph dfsTree = Algorithms::dfs(g, 0);
    CHECK(dfsTree.getNumVertices() == 4);

    Neighbor* n = dfsTree.getNeighbors(3);
    bool from2 = false;
    while (n) {
        if (n->vertex == 2) from2 = true;
        n = n->next;
    }
    CHECK(from2);
}

// Dijkstra should choose the lighter indirect path
TEST_CASE("Dijkstra path choice") {
    Graph g(4);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(0, 2, 10);
    g.addEdge(2, 3, 1);

    Graph tree = Algorithms::dijkstra(g, 0);
    CHECK(tree.getNumVertices() == 4);

    // Instead of checking tree.getNeighbors(2), we check from 1 → 2
    Neighbor* m = tree.getNeighbors(1);
    bool hasEdgeTo2 = false;
    while (m) {
        if (m->vertex == 2) hasEdgeTo2 = true;
        m = m->next;
    }
    CHECK(hasEdgeTo2);
}

// Prim should return MST with minimum weight
TEST_CASE("Prim MST") {
    Graph g(4);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 2);

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
    CHECK(totalWeight / 2 == 6);
}

// Kruskal should match Prim for connected graph
TEST_CASE("Kruskal MST") {
    Graph g(4);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 3);
    g.addEdge(1, 2, 1);
    g.addEdge(2, 3, 2);

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
    CHECK(totalWeight / 2 == 6);
}

// ----------------------------------------------------------
// Edge Case Tests
// ----------------------------------------------------------

// Vertex that has no neighbors
TEST_CASE("Isolated vertex") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    Neighbor* n = g.getNeighbors(2);
    CHECK(n == nullptr);
}

// Graph with no edges at all
TEST_CASE("Graph with no edges") {
    Graph g(3);
    for (int i = 0; i < 3; ++i)
        CHECK(g.getNeighbors(i) == nullptr);
}

// Add an edge that loops to itself
TEST_CASE("Self-loop edge") {
    Graph g(2);
    g.addEdge(1, 1, 9);
    Neighbor* n = g.getNeighbors(1);
    bool hasSelf = false;
    while (n) {
        if (n->vertex == 1 && n->weight == 9) hasSelf = true;
        n = n->next;
    }
    CHECK(hasSelf);
}

// Dijkstra should not link unreachable nodes
TEST_CASE("Disconnected graph - Dijkstra should not link components") {
    Graph g(4);
    g.addEdge(0, 1, 1);       // First connected component
    g.addEdge(2, 3, 1);       // Second disconnected component

    Graph tree = Algorithms::dijkstra(g, 0);

    // Check if there is any edge to node 2 (it should not be in the tree)
    bool edgeTo2 = false;
    for (int u = 0; u < tree.getNumVertices(); ++u) {
        Neighbor* n = tree.getNeighbors(u);
        while (n) {
            if (n->vertex == 2) {
                edgeTo2 = true;
                break;
            }
            n = n->next;
        }
    }

    CHECK(edgeTo2 == false);  // 2 must remain unreachable
}
// Dijkstra should throw when encountering a negative weight edge
TEST_CASE("Dijkstra throws on negative edge") {
    Graph g(3);
    g.addEdge(0, 1, 2);
    g.addEdge(1, 2, -5); // Invalid negative weight

    CHECK_THROWS_WITH(Algorithms::dijkstra(g, 0),
                      "Graph contains a negative weight edge – Dijkstra is not allowed");
}
// Algorithms on graph with a single node
TEST_CASE("Single vertex graph") {
    Graph g(1);
    CHECK_NOTHROW(Algorithms::bfs(g, 0));
    CHECK_NOTHROW(Algorithms::dfs(g, 0));
    CHECK_NOTHROW(Algorithms::dijkstra(g, 0));
}

// Algorithm called with invalid vertex
TEST_CASE("Invalid source vertex for BFS/DFS") {
    Graph g(3);
    CHECK_THROWS(Algorithms::bfs(g, 5));
    CHECK_THROWS(Algorithms::dfs(g, -1));
}
// Prim on disconnected graph should return incomplete MST
TEST_CASE("Prim on disconnected graph") {
    Graph g(5);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(3, 4, 3); // disconnected component

    Graph mst = Algorithms::prim(g);

    // Prim should not connect components
    int edgeCount = 0;
    for (int u = 0; u < mst.getNumVertices(); ++u) {
        Neighbor* n = mst.getNeighbors(u);
        while (n) {
            ++edgeCount;
            n = n->next;
        }
    }
    CHECK(edgeCount / 2 < 4); // less than n-1 edges for disconnected graph
}

// Loop edge should not appear in MST
TEST_CASE("Self-loop should be ignored in MST") {
    Graph g(3);
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 1, 9); // loop edge

    Graph mst = Algorithms::prim(g);

    // Check that node 1 does not have self-loop
    Neighbor* n = mst.getNeighbors(1);
    bool hasLoop = false;
    while (n) {
        if (n->vertex == 1) hasLoop = true;
        n = n->next;
    }
    CHECK(hasLoop == false);
}
// Kruskal with zero-weight edge should include it in MST
TEST_CASE("Kruskal includes zero-weight edge") {
    Graph g(4);
    g.addEdge(0, 1, 0);  // zero-weight edge
    g.addEdge(1, 2, 2);
    g.addEdge(2, 3, 3);

    Graph mst = Algorithms::kruskal(g);

    // Check that 0-1 with weight 0 appears in the MST
    Neighbor* n = mst.getNeighbors(0);
    bool found = false;
    while (n) {
        if (n->vertex == 1 && n->weight == 0)
            found = true;
        n = n->next;
    }
    CHECK(found);
}
//Prim should build an MST with the lightest possible edges
TEST_CASE("Prim builds correct minimum spanning tree") {
    Graph g(5);
    /*
        Lightest MST edges should be: (0,1), (1,2), (1,3), (3,4)
    */
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(3, 4, 7);

    // Heavy edges
    g.addEdge(0, 3, 10);
    g.addEdge(2, 3, 20);
    g.addEdge(0, 4, 30);

    Graph mst = Algorithms::prim(g);

    int totalWeight = 0;
    for (int i = 0; i < mst.getNumVertices(); ++i) {
        Neighbor* n = mst.getNeighbors(i);
        while (n) {
            totalWeight += n->weight;
            n = n->next;
        }
    }

    CHECK(totalWeight / 2 == 15);
}
//Kruskal should always pick the lightest possible edges for MST
TEST_CASE("Kruskal picks minimal weight edges for MST") {
    Graph g(5);
    /*
        The lightest edges that should be picked in the MST:
        (0,1), (1,2), (1,3), (3,4)
        We'll also add heavier edges to ensure Kruskal ignores them.
    */
    g.addEdge(0, 1, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 4);
    g.addEdge(3, 4, 6);

    // Heavy edges
    g.addEdge(0, 3, 10);
    g.addEdge(2, 3, 20);
    g.addEdge(0, 4, 30);

    Graph mst = Algorithms::kruskal(g);

    // Calculate total weight of the MST
    int totalWeight = 0;
    for (int i = 0; i < mst.getNumVertices(); ++i) {
        Neighbor* n = mst.getNeighbors(i);
        while (n) {
            totalWeight += n->weight;
            n = n->next;
        }
    }

    // Since edges are undirected and stored twice, divide by 2
    CHECK(totalWeight / 2 == 13);
}
