// Author: realyoavperetz@gmail.com

#pragma once

#include "Graph.hpp"
#include "../include/Queue.hpp"

namespace graph {

class Algorithms {
public:
    /*
    BFS:  is a graph traversal algorithm that explores all vertices at the current 
    depth before moving to the next level, using a queue to visit neighbors in order.
    
    returns a BFS tree
    */
    static Graph bfs(const Graph& g, int source);

    /*
    DFS: gets a graph and a source vertex, returns a graph (tree or forest)
    that contains only tree edges according to a DFS traversal.

    returns a DFS tree
    */ 
    static Graph dfs(const Graph& g, int source);

    /*
    Dijkstra: 
    Use a min-priority queue to always process the vertex with the current
    shortest known distance.

    returns the shortest path tree
    */ 
    static Graph dijkstra(const Graph& g, int source);

    /*
    Prim : 
    Starting from any vertex, grow a Minimum Spanning Tree (MST) by adding
    the lightest edge that connects the growing tree to a new vertex.

    returns the minimum spanning tree (only for connected graphs)
    */
    static Graph prim(const Graph& g);

    /*
    Kruskal: Greedily adds the lightest edges to the MST, as long as they don’t form a cycle.

    returns the minimum spanning tree (for any graph)
    */ 
    static Graph kruskal(const Graph& g);
};

}