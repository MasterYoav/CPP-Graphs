// Author: realyoavperetz@gmail.com

#pragma once

namespace graph {

class Queue {
private:
    int* data;       // underlying array
    int front;       // index of front element
    int rear;        // index for next insert
    int size;        // current number of elements
    int capacity;    // total capacity

public:
    // Constructor
    Queue(int capacity);

    // Destructor
    ~Queue();

    // Add an element to the rear
    void enqueue(int value);

    // Remove and return the front element
    int dequeue();

    // Check if the queue is empty
    bool isEmpty() const;
};

}