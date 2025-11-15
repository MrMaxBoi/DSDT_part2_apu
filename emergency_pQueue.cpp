#include <iostream>
#include <string>
#include "emergency_pQueue.hpp"
#include <cctype>

using std::cin;
using std::cout;
using std::string;

const int MAX_EMERGENCY_CASES = 100;

string toLower(const string& s) {
    string r = s;
    for (char &ch : r) {
        ch = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
    }
    return r;
}

class EmergencyPriorityQueue {
private:
    EmergencyCase data[MAX_EMERGENCY_CASES];
    int count;

public:
    EmergencyPriorityQueue() : count(0) {}

    bool isEmpty() const {
        return count == 0;
    }

    bool isFull() const {
        return count == MAX_EMERGENCY_CASES;
    }

    // Check if a patient name already exists in the queue
    bool containsPatientName(const string& name) const {
        string target = toLower(name);
        for (int i = 0; i < count; ++i) {
            if (toLower(data[i].patientName) == target) {
                return true;
            }
        }
        return false;
    }


    // Priority-based insertion (1 = most critical)
    bool enqueue(const EmergencyCase& c) {
        if (isFull()) return false;

        int i = count - 1;

        // Sort ascending by priorityLevel
        while (i >= 0 && c.priorityLevel < data[i].priorityLevel) {
            data[i + 1] = data[i];
            --i;
        }

        data[i + 1] = c;
        ++count;
        return true;
    }

    // Remove highest-priority (data[0])
    bool dequeue(EmergencyCase& out) {
        if (isEmpty()) return false;

        out = data[0];
        for (int i = 1; i < count; ++i) {
            data[i - 1] = data[i];
        }
        --count;
        return true;
    }

    void printAll() const {
        if (isEmpty()) {
            cout << "\nNo pending emergency cases.\n";
            return;
        }

        cout << "\n-- Pending Emergency Cases (highest priority first) --\n";
        for (int i = 0; i < count; ++i) {
            cout << (i + 1)
                 << ") [Priority " << data[i].priorityLevel << "] "
                 << data[i].patientName << " - "
                 << data[i].emergencyType << "\n";
        }
    }
};

// Read any integer (for priority etc.)
int read_int(const string& prompt) {
    int v;
    while (true) {
        cout << prompt;
        if (cin >> v) {
            cin.ignore(1000, '\n');
            return v;
        }
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Invalid number. Try again.\n";
    }
}

// Read menu selection within [min, max] and reject junk / out-of-range
int read_menu_choice(int min, int max) {
    int choice;
    while (true) {
        cout << "Select: ";
        if (!(cin >> choice)) {
            // Non-integer (string, symbol, etc.)
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between "
                 << min << " and " << max << ".\n";
            continue;
        }
        cin.ignore(1000, '\n'); // clear the rest of the line
        if (choice < min || choice > max) {
            cout << "Invalid option. Please enter a number between "
                 << min << " and " << max << ".\n";
            continue;
        }
        return choice;
    }
}

int read_priority(const string& prompt) {
    int p;
    while (true) {
        cout << prompt;
        if (!(cin >> p)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number between 1 and 5.\n";
            continue;
        }
        cin.ignore(1000, '\n');

        if (p < 1 || p > 5) {
            cout << "Priority must be between 1 (Critical) and 5 (Minor). Please try again.\n";
            continue;
        }

        return p;
    }
}


void log_case(EmergencyPriorityQueue& pq) {
    if (pq.isFull()) {
        cout << "Queue is full.\n";
        return;
    }

    EmergencyCase c;
    cout << "\n-- Log Emergency Case --\n";

    // Ensure unique patient name
    while (true) {
        cout << "Patient name: ";
        std::getline(cin, c.patientName);

        if (c.patientName.empty()) {
            cout << "Patient name cannot be empty. Please re-enter.\n";
            continue;
        }

        if (pq.containsPatientName(c.patientName)) {
            cout << "A case for this patient name already exists in the queue.\n"
                 << "Please enter a different patient name.\n";
            continue;
        }

        break; // valid and unique name
    }

    cout << "Emergency type: ";
    std::getline(cin, c.emergencyType);

    c.priorityLevel = read_priority("Priority (1 = Critical ... 5 = Minor): ");

    if (pq.enqueue(c)) {
        cout << "Emergency case logged.\n";
    } else {
        cout << "Failed to log emergency case (queue full).\n";
    }
}

void process_case(EmergencyPriorityQueue& pq) {
    EmergencyCase c;
    cout << "\n-- Process Most Critical Case --\n";

    if (!pq.dequeue(c)) {
        cout << "No cases pending.\n";
        return;
    }

    cout << "Attending patient: " << c.patientName << "\n"
         << "Emergency: " << c.emergencyType << "\n"
         << "Priority level: " << c.priorityLevel << "\n";
}

void view_cases(EmergencyPriorityQueue& pq) {
    pq.printAll();
}

void run_emergency_pQueue() {
    EmergencyPriorityQueue pq;
    int choice;

    while (true) {
        cout << "\n-- Emergency Department (Priority Queue) --\n"
             << "1) Log emergency case\n"
             << "2) Process most critical case\n"
             << "3) View pending cases\n"
             << "0) Back to main menu\n";

        // Valid menu choice between 0 and 3
        choice = read_menu_choice(0, 3);

        switch (choice) {
            case 1: 
                log_case(pq); 
                break;
            case 2: 
                process_case(pq); 
                break;
            case 3: 
                view_cases(pq); 
                break;
            case 0: 
                return;
        }
    }
}
