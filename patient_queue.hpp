#ifndef PATIENT_QUEUE_HPP
#define PATIENT_QUEUE_HPP

#include <string>
#include <deque>   // Allowed

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

// Simple array wrapper instead of std::vector
struct PatientArray {
    Patient* data;
    size_t size;

    PatientArray() : data(nullptr), size(0) {}
    
    bool empty() const { return size == 0; }
    Patient* begin() { return data; }
    Patient* end() { return data + size; }
    const Patient* begin() const { return data; }
    const Patient* end() const { return data + size; }
};

class PatientQueue {
public:
    PatientQueue() = default;

    void enqueue(const Patient& p);
    MaybePatient dequeue();
    MaybePatient peek() const;
    PatientArray listAll() const;   // NOW RETURNS ARRAY
    MaybePatient findById(int id) const;
    size_t size() const noexcept;
    bool empty() const noexcept;
    void clear() noexcept;

private:
    std::deque<Patient> q;  // <deque> is allowed
};
#endif