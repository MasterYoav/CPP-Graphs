//Author: realyoavperetz@gmail.com

#include <iostream> 
#include "../include/Graph.hpp" 

using namespace graph; 

//Construct graph with fixed number of vertices
Graph::Graph(int numVertices) : numVertices(numVertices){ 
  
  adjList = new Neighbor*[numVertices]; //Memory allocation
  for (int i = 0; i < numVertices; i++)
  {
    adjList[i] = nullptr; //initialize all vertices to nullptr
  }
}

//Destructor function to free memory
Graph::~Graph(){
  for (int i = 0; i < numVertices; i++){
    Neighbor* current = adjList[i];
    while (current != nullptr){
      Neighbor* temp = current;
      current = current->next;
      delete temp; //delete the neighbor
    }
  }
  delete[] adjList; //delete the pointers list
}
//Function to check vertices index validity
void Graph::validateVertex(int v) const {
    if (v < 0 || v >= numVertices) {
        throw "Invalid vertex index";
    }
}
//Function to add an edge between two vertices
void Graph::addEdge(int source, int dest, int weight){
  validateVertex(source);
  validateVertex(dest);
  Neighbor* newVertex = new Neighbor(dest, weight, adjList[source]);
        adjList[source] = newVertex; //add the neighbor to the list of the source vertex
    
        newVertex = new Neighbor(source, weight, adjList[dest]);
        adjList[dest] = newVertex; //add the neighbor to the list of the destination vertex
}

//Helper function to remove a vertex v from neighbors list
void removeNeighbor(Neighbor* &head, int v){
  if (head == nullptr) return;

  if (head->vertex == v){
    Neighbor* temp = head;
    head = head->next;
    delete temp;
    return;
  }
  Neighbor* current = head;
  while (current->next && current->next->vertex != v){
    current = current->next;
  }
    if (current->next && current->next->vertex == v){
      Neighbor* temp = current->next;
      current->next = temp->next;
      delete temp;
    }
}

//Method to remove an edge between vertices
void Graph::removeEdge(int source,int dest){
  validateVertex(source);
  validateVertex(dest);
  bool isEdge = false;
  Neighbor* current = adjList[source];
  while (current){ //searching the edge
    if (current->vertex == dest){
      isEdge = true;
      break;
    }
    current = current->next;
  }
  if (!isEdge) return; //edge does not exist

  removeNeighbor(adjList[source], dest); //remove the destination vertex from the source neighbors list
  removeNeighbor(adjList[dest], source); //removing vertex from the destination neighbors list
}

//Graph printing method
void Graph::printGraph() const {
  std::cout << "Adjacency List:" << std::endl;
  for (int i = 0; i < numVertices; ++i) {
      std::cout << "  [" << i << "] --> ";
      Neighbor* current = adjList[i];
      if (!current) {
          std::cout << "(none)";
      }
      while (current) {
          std::cout << current->vertex << " (w:" << current->weight << ")";
          if (current->next)
              std::cout << " -> ";
          current = current->next;
      }
      std::cout << std::endl;
  }
}

//Method that returns the vertices number of the graph
int Graph::getNumVertices() const {
  return numVertices;
}

//Method to get the neighbor list of a vertex
Neighbor* Graph::getNeighbors(int vertex) const {
  validateVertex(vertex);
  return adjList[vertex];
}
