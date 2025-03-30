// Author: realyoavperetz@gmail.com

#include "../include/Algorithms.hpp"
#include "../include/Queue.hpp"
#include "../include/PriorityQueue.hpp"
#include "../include/UnionFind.hpp"
#include <limits>
#include <stdexcept>
#include <iostream>

using namespace graph;

/*
BFS:  is a graph traversal algorithm that explores all vertices at the current 
depth before moving to the next level, using a queue to visit neighbors in order.

Returns a BFS tree
*/
Graph Algorithms::bfs(const Graph& g, int source) {
    g.validateVertex(source);
    int n = g.getNumVertices();
    bool* visited = new bool[n]();
    Queue q(n);
    Graph tree(n);

    visited[source] = true;
    q.enqueue(source);

    while (!q.isEmpty()) {
        int u = q.dequeue();
        Neighbor* neighbors = g.getNeighbors(u);

        while (neighbors != nullptr) {
            int v = neighbors->vertex;
            int w = neighbors->weight;

            if (!visited[v]) {
                visited[v] = true;
                q.enqueue(v);
                tree.addEdge(u, v, w);
            }
            
            neighbors = neighbors->next;
        }
    }

    delete[] visited;
    return tree;
}

// Internal recursive DFS function
void dfsHelper(const Graph& g, Graph& tree, int u, bool* visited) {
  visited[u] = true;

  Neighbor* neighbors = g.getNeighbors(u);
  while (neighbors != nullptr) {
      int v = neighbors->vertex;
      if (!visited[v]) {
          // Add tree edge to DFS tree
          tree.addEdge(u, v, neighbors->weight);
          dfsHelper(g, tree, v, visited);
      }
      neighbors = neighbors->next;
  }
}
Graph Algorithms::dfs(const Graph& g, int source) {
  int n = g.getNumVertices();

  // Input validation
  g.validateVertex(source);
  Graph tree(n);
  bool* visited = new bool[n];
  for (int i = 0; i < n; ++i)
      visited[i] = false;

  // Call recursive helper
  dfsHelper(g, tree, source, visited);

  delete[] visited;
  return tree;
}

// Dijkstra: compute the shortest path tree from a given source
Graph Algorithms::dijkstra(const Graph& g, int source) {
    g.validateVertex(source);  // Ensure source is valid
    int n = g.getNumVertices();

    // Initialize distances to all vertices as infinity
    int* dist = new int[n];
    for (int i = 0; i < n; ++i)
        dist[i] = std::numeric_limits<int>::max();
    dist[source] = 0;

    // Track the parent of each node in the shortest path
    int* prev = new int[n];
    for (int i = 0; i < n; ++i)
        prev[i] = -1;

    // Track visited vertices
    bool* visited = new bool[n]();

    // Create a priority queue and insert all vertices
    PriorityQueue pq(n);
    for (int i = 0; i < n; ++i)
        pq.insert(i, dist[i]);

    // Main Dijkstra loop
    while (!pq.isEmpty()) {
        int u = pq.extractMin();
        visited[u] = true;

        Neighbor* neighbors = g.getNeighbors(u);
        while (neighbors != nullptr) {
            int v = neighbors->vertex;
            int weight = neighbors->weight;

            // Dijkstra doesn't support negative weights
            if (weight < 0) {
                delete[] dist;
                delete[] prev;
                delete[] visited;
                throw "Graph contains a negative weight edge – Dijkstra is not allowed";
            }

            if (!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                prev[v] = u;
                pq.updateDistance(v, dist[v]);
            }

            neighbors = neighbors->next;
        }
    }

    // Build the shortest path tree graph
    Graph tree(n);
    for (int v = 0; v < n; ++v) {
        if (prev[v] != -1 && dist[v] != std::numeric_limits<int>::max()) {
            Neighbor* neighbor = g.getNeighbors(prev[v]);
            while (neighbor != nullptr) {
                if (neighbor->vertex == v) {
                    tree.addDirectedEdge(prev[v], v, neighbor->weight);
                    break;
                }
                neighbor = neighbor->next;
            }
        }
    }

    delete[] dist;
    delete[] prev;
    delete[] visited;

    return tree;
}
Graph Algorithms::prim(const Graph& g) {
  int n = g.getNumVertices();

  // Arrays for MST logic
  bool* inTree = new bool[n];             // whether a node is in the MST
  int* minWeight = new int[n];            // min edge weight to reach a node
  int* parent = new int[n];               // parent node in the MST

  for (int i = 0; i < n; ++i) {
      inTree[i] = false;
      minWeight[i] = std::numeric_limits<int>::max();
      parent[i] = -1;
  }

  // Start from node 0
  minWeight[0] = 0;

  PriorityQueue pq(n);
  for (int i = 0; i < n; ++i)
      pq.insert(i, minWeight[i]);

  while (!pq.isEmpty()) {
      int u = pq.extractMin();
      inTree[u] = true;

      Neighbor* neighbors = g.getNeighbors(u);
      while (neighbors != nullptr) {
          int v = neighbors->vertex;
          int weight = neighbors->weight;

          // Update v if this edge is better and v not in MST yet
          if (!inTree[v] && weight < minWeight[v]) {
              minWeight[v] = weight;
              parent[v] = u;
              pq.updateDistance(v, weight);
          }

          neighbors = neighbors->next;
      }
  }

  // Build MST from parent array
  Graph mst(n);
  for (int v = 1; v < n; ++v) {
      if (parent[v] != -1) {
          Neighbor* neighbor = g.getNeighbors(v);
          while (neighbor != nullptr) {
              if (neighbor->vertex == parent[v]) {
                  mst.addEdge(v, parent[v], neighbor->weight);
                  break;
              }
              neighbor = neighbor->next;
          }
      }
  }

  // Clean up
  delete[] inTree;
  delete[] minWeight;
  delete[] parent;

  return mst;
}

Graph Algorithms::kruskal(const Graph& g) {
  int n = g.getNumVertices();

  // Step 1: collect all edges
  const int MAX_EDGES = n * n; // upper bound (dense)
  struct Edge {
      int u, v, weight;
  };
  Edge* edges = new Edge[MAX_EDGES];
  int edgeCount = 0;

  for (int u = 0; u < n; ++u) {
      Neighbor* curr = g.getNeighbors(u);
      while (curr != nullptr) {
          int v = curr->vertex;
          if (u < v) { // to avoid duplicate undirected edges
              edges[edgeCount++] = {u, v, curr->weight};
          }
          curr = curr->next;
      }
  }

  // Step 2: sort edges by weight (selection sort)
  for (int i = 0; i < edgeCount - 1; ++i) {
      int minIdx = i;
      for (int j = i + 1; j < edgeCount; ++j) {
          if (edges[j].weight < edges[minIdx].weight)
              minIdx = j;
      }
      if (minIdx != i) {
          Edge temp = edges[i];
          edges[i] = edges[minIdx];
          edges[minIdx] = temp;
      }
  }

  // Step 3: Kruskal using Union-Find
  UnionFind uf(n);
  Graph mst(n);

  for (int i = 0; i < edgeCount; ++i) {
      int u = edges[i].u;
      int v = edges[i].v;
      int w = edges[i].weight;

      if (!uf.connected(u, v)) {
          uf.unite(u, v);
          mst.addEdge(u, v, w);
      }
  }

  delete[] edges;
  return mst;
}
