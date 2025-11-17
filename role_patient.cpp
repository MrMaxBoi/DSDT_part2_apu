#include "patient_queue.hpp"
#include <iostream>
#include <limits>

// Patient Admission Clerk Role
void runPatientAdmissionClerk() {
    PatientQueue pq;
    int nextId = 1;

    while (true) {
        std::cout << "\n=== Patient Admission Clerk ===\n";
        std::cout << "1) Admit Patient\n";      // Function 1
        std::cout << "2) Discharge Patient\n";  // Function 2
        std::cout << "3) View Patient Queue\n"; // Function 3
        std::cout << "0) Exit\n";
        std::cout << "Select: ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        if (choice == 0) break;

        switch (choice) {
            case 1: { // Admit Patient
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                Patient p;
                p.id = nextId++;
                std::cout << "Patient name: ";
                std::getline(std::cin, p.name);
                std::cout << "Condition severity (1-5): ";
                while (!(std::cin >> p.severity) || p.severity < 1 || p.severity > 5) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Enter severity 1-5: ";
                }
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                p.arrival = "now"; // placeholder timestamp
                pq.enqueue(p);
                std::cout << "Admitted patient ID " << p.id << " (" << p.name << ").\n";
                break;
            }
            case 2: { // Discharge Patient
                MaybePatient mp = pq.dequeue();
                if (!mp.hasValue) {
                    std::cout << "No patients waiting.\n";
                } else {
                    Patient p = mp.value;
                    std::cout << "Discharged patient ID " << p.id << " - " << p.name
                              << " (severity " << p.severity << ")\n";
                }
                break;
            }
            case 3: { // View Patient Queue
                auto list = pq.listAll();
                if (list.empty()) {
                    std::cout << "Queue is empty.\n";
                } else {
                    std::cout << "Patients waiting (front -> back):\n";
                    for (const auto& p : list) {
                        std::cout << "  ID " << p.id << " | " << p.name
                                  << " | severity " << p.severity << "\n";
                    }
                }
                break;
            }
            default:
                std::cout << "Unknown option.\n";
        }
    }

    std::cout << "Exiting Patient Admission Clerk.\n";
}
