#include <iostream>
#include <limits>
#include "supply_stack.hpp"

static void pause_line() {
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

static void list_all_copy(SupplyStack& st) {
    // Non-destructive listing: pop to temp, print, then restore
    SupplyStack temp;
    Supply s;
    while (st.pop(s)) {
        std::cout << " - " << s.name << " x" << s.qty << " [" << s.batch << "]\n";
        temp.push(s);
    }
    while (temp.pop(s)) st.push(s);
}

static void seed_supply(SupplyStack& st) {
    st.push({"N95 Masks", 200, "B24-1106"});
    st.push({"IV Set", 120, "B24-1105"});
    st.push({"Ceftriaxone 1g", 60, "B24-1104"});
}

void run_medical_supply() {
    SupplyStack store;
    // quick demo so your marker sees life
    std::cout << "\n[Medical Supply: quick scripted test]\n";
    seed_supply(store);
    std::cout << "Pushed 3 batches. Top should be last-in: ";
    if (auto p = store.peek()) std::cout << p->name << " x" << p->qty << "\n";
    Supply used{};
    store.pop(used);
    std::cout << "Popped for usage: " << used.name << " x" << used.qty << "\n";
    std::cout << "Current stack (top to bottom):\n";
    list_all_copy(store);
    pause_line();

    int c = -1;
    while (true) {
        std::cout << "\n-- Medical Supply (Stack: LIFO) --\n"
                  << "1) Receive new stock (push)\n"
                  << "2) Use latest stock (pop)\n"
                  << "3) View latest stock (peek)\n"
                  << "4) List all (non-destructive)\n"
                  << "0) Back\n"
                  << "Select: ";
        if (!(std::cin >> c)) return;
        if (c == 0) return;

        if (c == 1) {
            Supply s;
            std::cout << "Item name: "; std::cin.ignore(); std::getline(std::cin, s.name);
            std::cout << "Quantity: "; std::cin >> s.qty;
            std::cout << "Batch: "; std::cin >> s.batch;
            store.push(s);
            std::cout << "Pushed.\n";
        } else if (c == 2) {
            Supply s;
            if (store.pop(s)) {
                std::cout << "Used: " << s.name << " x" << s.qty << " [" << s.batch << "]\n";
            } else {
                std::cout << "No stock to use.\n";
            }
        } else if (c == 3) {
            auto p = store.peek();
            if (!p) std::cout << "Empty.\n";
            else std::cout << "Top: " << p->name << " x" << p->qty << " [" << p->batch << "]\n";
        } else if (c == 4) {
            if (store.empty()) { std::cout << "Empty.\n"; continue; }
            std::cout << "Stack contents (top -> bottom):\n";
            list_all_copy(store);
        } else {
            std::cout << "Invalid.\n";
        }
    }
}