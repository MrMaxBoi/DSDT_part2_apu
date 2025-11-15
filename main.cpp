#include <iostream>

// forward decls for role entry points
void run_medical_supply();    // role_supply.cpp
void run_ambulance_dispatch();// role_ambulance.cpp
void run_emergency_pQueue();  // emergency_pQueue.cpp

// Helper for safe menu input
int read_main_menu_choice(int min, int max) {
    int choice;
    while (true) {
        std::cout << "Select: ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Invalid input. Please enter a number between "
                      << min << " and " << max << ".\n";
            continue;
        }
        std::cin.ignore(1000, '\n');
        if (choice < min || choice > max) {
            std::cout << "Invalid option. Please enter a number between "
                      << min << " and " << max << ".\n";
            continue;
        }
        return choice;
    }
}

int main() {
    while (true) {
        std::cout << "\n=== Hospital Management Demo ===\n"
                  << "1. Patient Admission\n"
                  << "2. Medical Supply\n"
                  << "3. Emergency Dept\n"
                  << "4. Ambulance\n"
                  << "0. Exit\n";

        int choice = read_main_menu_choice(0, 4);

        switch (choice) {
            case 0:
                std::cout << "Bye.\n";
                return 0;

            case 1:
                std::cout << "[TODO] Patient Admission (Queue) not implemented in this demo.\n";
                break;

            case 2:
                run_medical_supply();
                break;

            case 3:
                run_emergency_pQueue();
                break;

            case 4:
                run_ambulance_dispatch();
                break;
        }
    }
}
