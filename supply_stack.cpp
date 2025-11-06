#include "supply_stack.hpp"

SupplyStack::~SupplyStack() {
    Supply out;
    while (pop(out)) {}
}

void SupplyStack::push(const Supply& s) {
    top_ = new Node(s, top_);
    ++count_;
}

bool SupplyStack::pop(Supply& out) {
    if (!top_) return false;
    Node* n = top_;
    out = n->val;
    top_ = n->next;
    delete n;
    --count_;
    return true;
}

const Supply* SupplyStack::peek() const {
    return top_ ? &top_->val : nullptr;
}