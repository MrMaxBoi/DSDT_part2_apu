#ifndef AMBULANCE_CQUEUE_HPP
#define AMBULANCE_CQUEUE_HPP

#include <string>

struct Ambulance {
    std::string id;    // "AMB-01"
    std::string plate; // "WXX 1234"
    std::string crew;  // "Lee/Kumar"
};

class AmbulanceCQueue {
    int capacity;
    int head;   // index of front
    int tail;   // index after last
    int count;
    Ambulance* data;

public:
    explicit AmbulanceCQueue(int cap = 8);
    ~AmbulanceCQueue();

    bool empty() const { return count == 0; }
    bool full()  const { return count == capacity; }
    int  size()  const { return count; }

    bool enqueue(const Ambulance& a);
    bool dequeue(Ambulance& out);
    bool rotate(); // move front to back if not empty

    template <typename Fn>
    void forEach(Fn fn) const {
        for (int i = 0, idx = head; i < count; ++i, idx = (idx + 1) % capacity)
            fn(data[idx]);
    }
};

#endif