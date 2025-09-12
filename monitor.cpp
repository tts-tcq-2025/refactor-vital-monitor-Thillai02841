#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// ---------- Data structures ----------
struct VitalThreshold {
    std::string name;
    float minVal;
    float maxVal;
};

struct VitalStatus {
    bool ok;
    std::string message;
};

VitalStatus checkVital(float value, const VitalThreshold& threshold) {
    if (value < threshold.minVal || value > threshold.maxVal) {
        return {false, threshold.name + " is out of range!"};
    }
    return {true, ""};
}

// ---------- I/O side effects ----------
void blinkWarning(int secondsDuration = 6) {
    for (int i = 0; i < secondsDuration; i++) {
        cout << "\r* " << flush;
        sleep_for(seconds(1));
        cout << "\r *" << flush;
        sleep_for(seconds(1));
    }
    cout << "\n";
}

// Helper: Collect all abnormal vitals
std::vector<std::string> collectCriticalVitals(
    const std::vector<std::pair<float, VitalThreshold>>& vitals) {
    std::vector<std::string> messages;
    for (const auto& vital : vitals) {
        VitalStatus result = checkVital(vital.first, vital.second);
        if (!result.ok) {
            messages.push_back(result.message);
        }
    }
    return messages;
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    std::vector<std::pair<float, VitalThreshold>> vitals = {
        {temperature, {"Temperature", 95, 102}},
        {pulseRate, {"Pulse Rate", 60, 100}},
        {spo2, {"Oxygen Saturation", 90, 100}}
    };

    std::vector<std::string> warnings = collectCriticalVitals(vitals);

    if (!warnings.empty()) {
        for (const auto& msg : warnings) {
            cout << msg << "\n";
        }
        blinkWarning();
        return 0;
    }
    return 1;
}
