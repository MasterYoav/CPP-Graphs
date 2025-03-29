//Author: realyoavperetz@gmail.com

#include <iostream> // for std::cout
#include "../include/Graph.hpp" 

using namespace graph; //using the graph namespace

//construct Graph with fixed number of vertices
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

//Function to add an edge between two vertices
void Graph::addEdge(int source, int dest, int weight){
  if (source < 0 || source >= numVertices || dest < 0 || dest >= numVertices)
        throw "Invalid vertex index"; //throw an exception if the input is invalid
        Neighbor* newVertex = new Neighbor(dest, weight, adjList[source]);
        adjList[source] = newVertex; //add the neighbor to the list of the source vertex
    
        newVertex = new Neighbor(source, weight, adjList[dest]);
        adjList[dest] = newVertex; //add the neighbor to the list of the destination vertex
}

//helper function to remove a vertex v from neighbors list
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


void Graph::removeEdge(int source,int dest){
  if (source < 0 || source >= numVertices || dest < 0 || dest >= numVertices){
        throw "Invalid vertex index"; //throw an exception if the input is invalid
  }
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

void Graph::printGraph() const {
    for (int i = 0; i < numVertices; ++i) {
        std::cout << "Vertex " << i << ": ";
        Neighbor* current = adjList[i];
        while (current) {
            std::cout << "(" << current->vertex << ", w=" << current->weight << ") ";
            current = current->next;
        }
        std::cout << std::endl;
    }
}

//Function to print the graph
int Graph::getNumVertices() const {
  return numVertices;
}

//Function to get the neighbor list of a vertex
Neighbor* Graph::getNeighbors(int vertex) const {
  if (vertex < 0 || vertex >= numVertices)
      throw "Invalid vertex index";
  return adjList[vertex];
}
