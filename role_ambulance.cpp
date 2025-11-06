#include <iostream>
#include <limits>
#include "ambulance_cqueue.hpp"

static void pause_line2() {
    std::cout << "Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cin.get();
}

static void print_queue(const AmbulanceCQueue& q) {
    int i = 1;
    q.forEach([&](const Ambulance& a){
        std::cout << i++ << ") " << a.id << " | " << a.plate << " | " << a.crew << "\n";
    });
}

static void seed_ambulances(AmbulanceCQueue& q) {
    q.enqueue({"AMB-01", "WXX1234", "Lee/Kumar"});
    q.enqueue({"AMB-02", "WYY5678", "Tan/Ravi"});
    q.enqueue({"AMB-03", "WZZ2468", "Aida/Chen"});
}

void run_ambulance_dispatch() {
    AmbulanceCQueue sched(8);

    // quick scripted test
    std::cout << "\n[Ambulance: quick scripted test]\n";
    seed_ambulances(sched);
    std::cout << "Initial schedule:\n"; print_queue(sched);
    std::cout << "Rotate twice...\n"; sched.rotate(); sched.rotate();
    print_queue(sched);
    pause_line2();

    int c = -1;
    while (true) {
        std::cout << "\n-- Ambulance Dispatch (Circular Queue) --\n"
                  << "1) Register ambulance (enqueue)\n"
                  << "2) Dispatch next (dequeue)\n"
                  << "3) Rotate shift (front -> back)\n"
                  << "4) Show schedule order\n"
                  << "0) Back\n"
                  << "Select: ";
        if (!(std::cin >> c)) return;
        if (c == 0) return;

        if (c == 1) {
            Ambulance a;
            std::cout << "ID: "; std::cin >> a.id;
            std::cout << "Plate: "; std::cin >> a.plate;
            std::cout << "Crew: "; std::cin.ignore(); std::getline(std::cin, a.crew);
            if (sched.enqueue(a)) std::cout << "Registered.\n";
            else std::cout << "Queue full, cannot register.\n";
        } else if (c == 2) {
            Ambulance a;
            if (sched.dequeue(a))
                std::cout << "Dispatched: " << a.id << " | " << a.plate << " | " << a.crew << "\n";
            else
                std::cout << "No ambulances waiting.\n";
        } else if (c == 3) {
            if (sched.rotate()) std::cout << "Rotated.\n";
        } else if (c == 4) {
            if (sched.empty()) std::cout << "Empty.\n";
            else print_queue(sched);
        } else {
            std::cout << "Invalid.\n";
        }
    }
}