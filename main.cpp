#include <iostream>

// forward decls for role entry points
void run_medical_supply();    // role_supply.cpp
void run_ambulance_dispatch();// role_ambulance.cpp

int main() {
    int choice = -1;
    while (true) {
        std::cout << "\n=== Hospital Management Demo ===\n"
                  << "1. Patient Admission\n"
                  << "2. Medical Supply\n"
                  << "3. Emergency Dept\n"
                  << "4. Ambulance\n"
                  << "0. Exit\n"
                  << "Select: ";
        if (!(std::cin >> choice)) return 0;
        if (choice == 0) break;
        switch (choice) {
            case 1:
                std::cout << "[TODO] Patient Admission (Queue) not implemented in this demo.\n";
                break;
            case 2:
                run_medical_supply();
                break;
            case 3:
                std::cout << "[TODO] Emergency Dept (Priority Queue) not implemented in this demo.\n";
                break;
            case 4:
                run_ambulance_dispatch();
                break;
            default:
                std::cout << "Invalid option.\n";
        }
    }
    std::cout << "Bye.\n";
    return 0;
}