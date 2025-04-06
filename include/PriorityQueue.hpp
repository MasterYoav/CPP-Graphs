// Author: realyoavperetz@gmail.com

#pragma once

namespace graph {

// A manual min-heap based priority queue for (vertex, distance) pairs
class PriorityQueue {
private:
    int* vertices;     // stores vertex IDs
    int* distances;    // stores their current priority (distance)
    int size;          // current number of elements
    int capacity;      // maximum size of the heap

    // Internal helpers to maintain heap order
    void swap(int i, int j);            // swaps two elements
    void heapifyUp(int index);          // restore heap from bottom up
    void heapifyDown(int index);        // restore heap from top down

public:
    // Constructor / Destructor
    PriorityQueue(int capacity);
    ~PriorityQueue();

    // Returns true if queue is empty
    bool isEmpty() const;

    // Insert a (vertex, distance) pair into the queue
    void insert(int vertex, int distance);

    // Remove and return the vertex with the smallest distance
    int extractMin();

    // Check if queue currently contains this vertex
    bool contains(int vertex) const;

    // Get the stored distance for a vertex (if found)
    int getDistance(int vertex) const;

    // Update the distance of a vertex (if it exists in the queue)
    void updateDistance(int vertex, int newDist);
};

}