// Author: realyoavperetz@gmail.com
#include "include/Graph.hpp"
#include "include/Algorithms.hpp"
#include <iostream>

using namespace graph;
using namespace std;

int main() {
    // Create a graph with 5 vertices
    Graph g(5);

    // Add edges with weights
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(3, 4, 3);

    // Print original graph
    cout << "Original Graph:" << endl;
    g.printGraph();
    cout << "------------------------\n";

    // Run BFS
    cout << "BFS Tree from vertex 0:" << endl;
    Graph bfsTree = Algorithms::bfs(g, 0);
    bfsTree.printGraph();
    cout << "------------------------\n";

    // Run DFS
    cout << "DFS Tree from vertex 0:" << endl;
    Graph dfsTree = Algorithms::dfs(g, 0);
    dfsTree.printGraph();
    cout << "------------------------\n";

    // Run Dijkstra
    cout << "Dijkstra Tree from vertex 0:" << endl;
    Graph dijkstraTree = Algorithms::dijkstra(g, 0);
    dijkstraTree.printGraph();
    cout << "------------------------\n";

    // Run Prim
    cout << "Prim's MST:" << endl;
    Graph primTree = Algorithms::prim(g);
    primTree.printGraph();
    cout << "------------------------\n";

    // Run Kruskal
    cout << "Kruskal's MST:" << endl;
    Graph kruskalTree = Algorithms::kruskal(g);
    kruskalTree.printGraph();
    cout << "------------------------\n";

    // Remove an edge and show graph
    cout << "Removing edge (1, 2):" << endl;
    g.removeEdge(1, 2);
    g.printGraph();
    cout << "------------------------\n";

    return 0;
}
