// Author: realyoavperetz@gmail.com

#include "../include/Queue.hpp"

using namespace graph;

Queue::Queue(int capacity) {
    this->capacity = capacity;
    data = new int[capacity];
    front = 0;
    rear = 0;
    size = 0;
}

Queue::~Queue() {
    delete[] data;
}

void Queue::enqueue(int value) {
    if (size == capacity)
        throw "Queue overflow";
    data[rear] = value;
    rear = (rear + 1) % capacity;
    ++size;
}

int Queue::dequeue() {
    if (isEmpty())
        throw "Queue underflow";
    int val = data[front];
    front = (front + 1) % capacity;
    --size;
    return val;
}

bool Queue::isEmpty() const {
    return size == 0;
}