#pragma once

namespace graph{
  struct Neighbor{
    int vertex; //Neighbor vertex
    int weight; //edge weight
    Neighbor* next;  //pointer to next neighbor

    Neighbor(int vertex, int weight, Neighbor* next = nullptr) : vertex(vertex), weight(weight), next(next) {};
  };

  class Graph{
  private:
    int numVertices;
    Neighbor** adjList;
  public:
    Graph(int numVertices); //constructor
    ~Graph(); //destructor

    
    void validateVertex(int v) const;
    void addEdge(int src, int dest, int weight);
    void removeEdge(int src, int dest);
    void printGraph()const;
    int getNumVertices()const;
    Neighbor* getNeighbors(int vertex)const;
  };
  
}
