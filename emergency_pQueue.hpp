#ifndef EMERGENCY_PQUEUE_HPP
#define EMERGENCY_PQUEUE_HPP

#include <string>

struct EmergencyCase {
    std::string patientName;
    std::string emergencyType;
    int priorityLevel; // 1 = highest priority
};

void run_emergency_pQueue();

#endif
