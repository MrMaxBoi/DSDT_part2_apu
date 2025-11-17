#ifndef PATIENT_QUEUE_HPP
#define PATIENT_QUEUE_HPP

#include <string>
#include <deque>
#include <vector>

struct Patient {
    int id;
    std::string name;
    int severity;     // 1 = low, 5 = critical
    std::string arrival;
};

// Replacement for std::optional (GCC 6.3.0)
struct MaybePatient {
    bool hasValue;
    Patient value;

    MaybePatient() : hasValue(false), value(Patient()) {}
    MaybePatient(const Patient& p) : hasValue(true), value(p) {}
};

class PatientQueue {
public:
    PatientQueue() = default;

    void enqueue(const Patient& p);
    MaybePatient dequeue();
    MaybePatient peek() const;
    std::vector<Patient> listAll() const;
    MaybePatient findById(int id) const;
    size_t size() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;

private:
    std::deque<Patient> q;
};
#endif