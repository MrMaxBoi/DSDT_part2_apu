#include "ambulance_cqueue.hpp"

AmbulanceCQueue::AmbulanceCQueue(int cap)
    : capacity(cap), head(0), tail(0), count(0) {
    if (capacity < 1) capacity = 1;
    data = new Ambulance[capacity];
}

AmbulanceCQueue::~AmbulanceCQueue() {
    delete[] data;
}

bool AmbulanceCQueue::enqueue(const Ambulance& a) {
    if (full()) return false;
    data[tail] = a;
    tail = (tail + 1) % capacity;
    ++count;
    return true;
}

bool AmbulanceCQueue::dequeue(Ambulance& out) {
    if (empty()) return false;
    out = data[head];
    head = (head + 1) % capacity;
    --count;
    return true;
}

bool AmbulanceCQueue::rotate() {
    if (count <= 1) return true; // nothing to do but still "ok"
    Ambulance front;
    dequeue(front);
    return enqueue(front);
}