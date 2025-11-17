#include <iostream>
#include <string>
#include "emergency_pQueue.hpp"
#include <cctype>
const std::string RED = "\033[31m";
const std::string GREEN = "\033[32m";
const std::string YELLOW = "\033[33m";
const std::string BLUE = "\033[34m";
const std::string MAGENTA = "\033[35m";
const std::string CYAN = "\033[36m";
const std::string WHITE = "\033[37m";
const std::string RESET = "\033[0m";
const std::string BOLD = "\033[1m";

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
public:
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
            cout << "\nNo emergency cases are currently pending.\n";
            return;
        }

        cout << "\n=== Emergency Cases Queue (" << count << "/" << MAX_EMERGENCY_CASES << ") ===\n";
        cout << "(Ordered by priority: Critical → Minor)\n\n";
        
        for (int i = 0; i < count; ++i) {
            string priority_desc, priority_color;
            switch(data[i].priorityLevel) {
                case 1: priority_desc = "Critical"; priority_color = RED; break;
                case 2: priority_desc = "High"; priority_color = YELLOW; break;
                case 3: priority_desc = "Medium"; priority_color = BLUE; break;
                case 4: priority_desc = "Low"; priority_color = GREEN; break;
                case 5: priority_desc = "Minor"; priority_color = CYAN; break;
            }
            
            cout << (i + 1) << ". " << priority_color << "[P" << data[i].priorityLevel 
                 << " - " << priority_desc << "]" << RESET << " ";
            cout << data[i].patientName << "\n";
            cout << "   Emergency: " << data[i].emergencyType << "\n";
            if (i < count - 1) cout << "\n";
        }
        cout << "\n" << string(50, '=') << "\n";
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

void display_priority_guide() {
    cout << "\n--- Priority Level Guide ---\n";
    cout << "1 - Critical (Life-threatening, immediate attention)\n";
    cout << "2 - High (Urgent, within 15 minutes)\n";
    cout << "3 - Medium (Semi-urgent, within 30 minutes)\n";
    cout << "4 - Low (Less urgent, within 1 hour)\n";
    cout << "5 - Minor (Non-urgent, within 2 hours)\n";
    cout << "---------------------------\n";
}

char read_confirmation(const string& prompt) {
    char response;
    while (true) {
        cout << prompt << " (y/n): ";
        if (!(cin >> response)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter 'y' or 'n'.\n";
            continue;
        }
        cin.ignore(1000, '\n');
        
        response = static_cast<char>(std::tolower(static_cast<unsigned char>(response)));
        if (response == 'y' || response == 'n') {
            return response;
        }
        cout << "Please enter 'y' for yes or 'n' for no.\n";
    }
}

int read_priority(const string& prompt) {
    int p;
    display_priority_guide();
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
        cout << "\n" << YELLOW << "WARNING:" << RESET << " Emergency queue is at maximum capacity (" << MAX_EMERGENCY_CASES << " cases).\n";
        cout << "Please process some cases before adding new ones.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    EmergencyCase c;
    cout << "\n=== Log New Emergency Case ===\n";

    // Ensure unique patient name
    while (true) {
        cout << "Patient name: ";
        std::getline(cin, c.patientName);

        if (c.patientName.empty()) {
            cout << RED << "ERROR:" << RESET << " Patient name cannot be empty. Please re-enter.\n";
            continue;
        }

        if (pq.containsPatientName(c.patientName)) {
            cout << RED << "ERROR:" << RESET << " A case for '" << c.patientName << "' already exists in the queue.\n"
                 << "Please enter a different patient name.\n";
            continue;
        }

        break; // valid and unique name
    }

    while (true) {
        cout << "Emergency type/description: ";
        std::getline(cin, c.emergencyType);
        if (!c.emergencyType.empty()) break;
        cout << RED << "ERROR:" << RESET << " Emergency type cannot be empty. Please re-enter.\n";
    }

    c.priorityLevel = read_priority("Select priority level: ");

    cout << "\n--- Case Summary ---\n";
    cout << "Patient: " << c.patientName << "\n";
    cout << "Emergency: " << c.emergencyType << "\n";
    cout << "Priority: " << c.priorityLevel;
    
    string priority_desc, priority_color;
    switch(c.priorityLevel) {
        case 1: priority_desc = " (Critical)"; priority_color = RED; break;
        case 2: priority_desc = " (High)"; priority_color = YELLOW; break;
        case 3: priority_desc = " (Medium)"; priority_color = BLUE; break;
        case 4: priority_desc = " (Low)"; priority_color = GREEN; break;
        case 5: priority_desc = " (Minor)"; priority_color = CYAN; break;
    }
    cout << priority_color << priority_desc << RESET << "\n";

    if (read_confirmation("\nConfirm logging this case?") == 'y') {
        if (pq.enqueue(c)) {
            cout << "\n" << GREEN << "SUCCESS:" << RESET << " Emergency case logged successfully!\n";
        } else {
            cout << "\n" << RED << "ERROR:" << RESET << " Failed to log emergency case (queue full).\n";
        }
    } else {
        cout << "\nCase logging cancelled.\n";
    }
    
    cout << "Press Enter to continue...";
    cin.get();
}

void process_case(EmergencyPriorityQueue& pq) {
    EmergencyCase c;
    cout << "\n=== Process Most Critical Case ===\n";

    if (pq.isEmpty()) {
        cout << "No emergency cases are currently pending.\n";
        cout << "Press Enter to continue...";
        cin.get();
        return;
    }

    // Show the next case without removing it first
    cout << "Next case to process:\n";
    cout << "Patient: " << pq.data[0].patientName << "\n";
    cout << "Emergency: " << pq.data[0].emergencyType << "\n";
    cout << "Priority: " << pq.data[0].priorityLevel;
    
    string priority_desc, priority_color;
    switch(pq.data[0].priorityLevel) {
        case 1: priority_desc = " (Critical)"; priority_color = RED; break;
        case 2: priority_desc = " (High)"; priority_color = YELLOW; break;
        case 3: priority_desc = " (Medium)"; priority_color = BLUE; break;
        case 4: priority_desc = " (Low)"; priority_color = GREEN; break;
        case 5: priority_desc = " (Minor)"; priority_color = CYAN; break;
    }
    cout << priority_color << priority_desc << RESET << "\n\n";

    if (read_confirmation("Confirm processing this case?") == 'y') {
        pq.dequeue(c);
        cout << "\n" << GREEN << "SUCCESS:" << RESET << " Case processed successfully!\n";
        cout << "Patient " << c.patientName << " is now being attended to.\n";
    } else {
        cout << "Case processing cancelled.\n";
    }
    
    cout << "Press Enter to continue...";
    cin.get();
}

void view_cases(EmergencyPriorityQueue& pq) {
    pq.printAll();
    if (!pq.isEmpty()) {
        cout << "\nNext case to be processed: " << pq.data[0].patientName;
        cout << " (Priority " << pq.data[0].priorityLevel << ")\n";
    }
    cout << "Press Enter to continue...";
    cin.get();
}

void run_emergency_pQueue() {
    EmergencyPriorityQueue pq;
    int choice;

    cout << "\nWelcome to Emergency Department Management System\n";
    cout << "This system manages emergency cases using priority-based queuing.\n";

    while (true) {
        cout << "\n" << string(55, '=') << "\n";
        cout << BOLD << CYAN << "EMERGENCY DEPARTMENT - PRIORITY QUEUE SYSTEM" << RESET << "\n";
        cout << string(55, '=') << "\n";
        cout << "Current Status: " << (pq.isEmpty() ? GREEN + "No pending cases" + RESET : 
                YELLOW + std::to_string(pq.count) + " case(s) pending" + RESET) << "\n";
        cout << string(55, '-') << "\n";
        cout << "1) Log new emergency case\n";
        cout << "2) Process most critical case\n";
        cout << "3) View all pending cases\n";
        cout << "0) Return to main menu\n";
        cout << string(55, '=') << "\n";

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
                cout << "\nReturning to main menu...\n";
                return;
        }
    }
}
