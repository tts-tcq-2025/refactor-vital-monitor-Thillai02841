// #include "./monitor.h"
// #include <assert.h>
// #include <thread>
// #include <chrono>
// #include <iostream>
// using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

// int vitalsOk(float temperature, float pulseRate, float spo2) {
//   if (temperature > 102 || temperature < 95) {
//     cout << "Temperature is critical!\n";
//     for (int i = 0; i < 6; i++) {
//       cout << "\r* " << flush;
//       sleep_for(seconds(1));
//       cout << "\r *" << flush;
//       sleep_for(seconds(1));
//     }
//     return 0;
//   } else if (pulseRate < 60 || pulseRate > 100) {
//     cout << "Pulse Rate is out of range!\n";
//     for (int i = 0; i < 6; i++) {
//       cout << "\r* " << flush;
//       sleep_for(seconds(1));
//       cout << "\r *" << flush;
//       sleep_for(seconds(1));
//     }
//     return 0;
//   } else if (spo2 < 90) {
//     cout << "Oxygen Saturation out of range!\n";
//     for (int i = 0; i < 6; i++) {
//       cout << "\r* " << flush;
//       sleep_for(seconds(1));
//       cout << "\r *" << flush;
//       sleep_for(seconds(1));
//     }
//     return 0;
//   }
//   return 1;
// }

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

// ---------- Pure functions (no I/O) ----------
VitalStatus checkTemperature(float temperature) {
    if (temperature < 95 || temperature > 102) {
        return {false, "Temperature is critical!"};
    }
    return {true, ""};
}

VitalStatus checkPulse(float pulseRate) {
    if (pulseRate < 60 || pulseRate > 100) {
        return {false, "Pulse Rate is out of range!"};
    }
    return {true, ""};
}

VitalStatus checkSpo2(float spo2) {
    if (spo2 < 90) {
        return {false, "Oxygen Saturation out of range!"};
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
        checkTemperature(temperature),
        checkPulse(pulseRate),
        checkSpo2(spo2)
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

