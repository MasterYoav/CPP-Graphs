#include "../include/PriorityQueue.hpp"
#include <limits> // for INT_MAX equivalent

using namespace graph;

// Constructor: initialize heap arrays
PriorityQueue::PriorityQueue(int cap) {
    capacity = cap;
    size = 0;

    vertices = new int[cap];
    distances = new int[cap];

    // Initialize arrays with default values
    for (int i = 0; i < cap; ++i) {
        vertices[i] = -1; // no vertex
        distances[i] = std::numeric_limits<int>::max(); // infinite distance
    }
}

// Destructor: free allocated arrays
PriorityQueue::~PriorityQueue() {
    delete[] vertices;
    delete[] distances;
}

// Check if the heap is empty
bool PriorityQueue::isEmpty() const {
    return size == 0;
}

// Swap two entries in the heap
void PriorityQueue::swap(int i, int j) {
    int tempV = vertices[i];
    int tempD = distances[i];
    vertices[i] = vertices[j];
    distances[i] = distances[j];
    vertices[j] = tempV;
    distances[j] = tempD;
}

// Restore heap order from a node upward
void PriorityQueue::heapifyUp(int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;
        if (distances[index] < distances[parent]) {
            swap(index, parent);
            index = parent;
        } else break;
    }
}

// Restore heap order from a node downward
void PriorityQueue::heapifyDown(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < size && distances[left] < distances[smallest])
        smallest = left;
    if (right < size && distances[right] < distances[smallest])
        smallest = right;

    if (smallest != index) {
        swap(index, smallest);
        heapifyDown(smallest); // recursive fix
    }
}

// Insert new (vertex, distance) into heap
void PriorityQueue::insert(int vertex, int distance) {
    vertices[size] = vertex;
    distances[size] = distance;
    heapifyUp(size);
    ++size;
}

// Remove and return the vertex with the smallest distance
int PriorityQueue::extractMin() {
    if (isEmpty())
        throw "Heap is empty";

    int minVertex = vertices[0];

    // Move last element to root and fix heap
    --size;
    vertices[0] = vertices[size];
    distances[0] = distances[size];
    heapifyDown(0);

    return minVertex;
}

// Return true if vertex exists in the queue
bool PriorityQueue::contains(int vertex) const {
    for (int i = 0; i < size; ++i)
        if (vertices[i] == vertex) return true;
    return false;
}

// Return the stored distance of a vertex
int PriorityQueue::getDistance(int vertex) const {
    for (int i = 0; i < size; ++i)
        if (vertices[i] == vertex) return distances[i];
    return std::numeric_limits<int>::max(); // default "infinite"
}

// Update distance of a vertex already in the queue
void PriorityQueue::updateDistance(int vertex, int newDist) {
    for (int i = 0; i < size; ++i) {
        if (vertices[i] == vertex) {
            distances[i] = newDist;
            heapifyUp(i); // re-balance
            break;
        }
    }
}