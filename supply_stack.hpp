#ifndef SUPPLY_STACK_HPP
#define SUPPLY_STACK_HPP

#include <string>

struct Supply {
    std::string name;
    int qty = 0;
    std::string batch; // e.g., "B24-1106"
};

class SupplyStack {
    struct Node {
        Supply val;
        Node* next;
        Node(const Supply& v, Node* n) : val(v), next(n) {}
    };
    Node* top_;
    size_t count_;

public:
    SupplyStack() : top_(nullptr), count_(0) {}
    ~SupplyStack();

    bool empty() const { return count_ == 0; }
    size_t size() const { return count_; }

    void push(const Supply& s);
    bool pop(Supply& out);
    const Supply* peek() const; // returns nullptr if empty
};

#endif