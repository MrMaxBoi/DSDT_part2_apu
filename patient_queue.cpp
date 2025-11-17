#include "patient_queue.hpp"
#include <algorithm>
#include <deque>

// Enqueue a patient
void PatientQueue::enqueue(const Patient& p) {
    q.push_back(p);
}

// Dequeue a patient, returns MaybePatient
MaybePatient PatientQueue::dequeue() {
    if (q.empty()) return MaybePatient();

    // Look for critical patient (severity >= 5)
    auto it = std::find_if(q.begin(), q.end(), [](const Patient& p){ return p.severity >= 5; });
    if (it != q.end()) {
        Patient out = *it;
        q.erase(it);
        return MaybePatient(out);
    }

    // Otherwise take the first patient
    Patient out = q.front();
    q.pop_front();
    return MaybePatient(out);
}

// Peek at the next patient without removing
MaybePatient PatientQueue::peek() const {
    if (q.empty()) return MaybePatient();

    auto it = std::find_if(q.begin(), q.end(), [](const Patient& p){ return p.severity >= 5; });
    if (it != q.end()) return MaybePatient(*it);

    return MaybePatient(q.front());
}

// List all patients
std::vector<Patient> PatientQueue::listAll() const {
    return std::vector<Patient>(q.begin(), q.end());
}

// Find patient by ID
MaybePatient PatientQueue::findById(int id) const {
    auto it = std::find_if(q.begin(), q.end(), [id](const Patient& p){ return p.id == id; });
    if (it != q.end()) return MaybePatient(*it);
    return MaybePatient();
}

// Queue size
size_t PatientQueue::size() const noexcept {
    return q.size();
}

// Check if empty
bool PatientQueue::empty() const noexcept {
    return q.empty();
}

// Clear the queue
void PatientQueue::clear() noexcept {
    q.clear();
}
#include "patient_queue.hpp"
#include <algorithm>
#include <deque>

// Enqueue a patient
void PatientQueue::enqueue(const Patient& p) {
    q.push_back(p);
}

// Dequeue a patient, returns MaybePatient
MaybePatient PatientQueue::dequeue() {
    if (q.empty()) return MaybePatient();

    // Look for critical patient (severity >= 5)
    auto it = std::find_if(q.begin(), q.end(), [](const Patient& p){ return p.severity >= 5; });
    if (it != q.end()) {
        Patient out = *it;
        q.erase(it);
        return MaybePatient(out);
    }

    // Otherwise take the first patient
    Patient out = q.front();
    q.pop_front();
    return MaybePatient(out);
}

// Peek at the next patient without removing
MaybePatient PatientQueue::peek() const {
    if (q.empty()) return MaybePatient();

    auto it = std::find_if(q.begin(), q.end(), [](const Patient& p){ return p.severity >= 5; });
    if (it != q.end()) return MaybePatient(*it);

    return MaybePatient(q.front());
}

// List all patients
std::vector<Patient> PatientQueue::listAll() const {
    return std::vector<Patient>(q.begin(), q.end());
}

// Find patient by ID
MaybePatient PatientQueue::findById(int id) const {
    auto it = std::find_if(q.begin(), q.end(), [id](const Patient& p){ return p.id == id; });
    if (it != q.end()) return MaybePatient(*it);
    return MaybePatient();
}

// Queue size
size_t PatientQueue::size() const noexcept {
    return q.size();
}

// Check if empty
bool PatientQueue::empty() const noexcept {
    return q.empty();
}

// Clear the queue
void PatientQueue::clear() noexcept {
    q.clear();
}
