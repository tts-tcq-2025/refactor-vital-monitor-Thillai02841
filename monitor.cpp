#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <string>
#include <vector>
#include <algorithm>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// ---------- Data structures ----------
struct VitalStatus {
    bool ok;
    std::string message;
};

VitalStatus checkVital(float value, float minVal, float maxVal, const std::string& name) {
    if (value < minVal || value > maxVal) {
        return {false, name + " is out of range!"};
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

int vitalsOk(float temperature, float pulseRate, float spo2) {
    std::vector<VitalStatus> results = {
        checkVital(temperature, 95, 102, "Temperature"),
        checkVital(pulseRate, 60, 100, "Pulse Rate"),
        checkVital(spo2, 90, 100, "Oxygen Saturation")
    };

    auto it = std::find_if(results.begin(), results.end(),
                           [](const VitalStatus& s){ return !s.ok; });

    if (it != results.end()) {
        cout << it->message << "\n";
        blinkWarning();
        return 0;
    }
    return 1;
}

