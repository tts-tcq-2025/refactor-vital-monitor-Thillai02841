#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
  ASSERT_FALSE(vitalsOk(99, 102, 70));   // Pulse out of range
  ASSERT_TRUE(vitalsOk(98.1, 70, 98));   // All in range
}

TEST(Monitor, TemperatureLowShouldFail) {
  ASSERT_FALSE(vitalsOk(94, 70, 98));    // Low temperature
}

TEST(Monitor, TemperatureHighShouldFail) {
  ASSERT_FALSE(vitalsOk(103, 70, 98));   // High temperature
}

TEST(Monitor, PulseLowShouldFail) {
  ASSERT_FALSE(vitalsOk(98.6, 55, 98));  // Low pulse
}

TEST(Monitor, PulseHighShouldFail) {
  ASSERT_FALSE(vitalsOk(98.6, 105, 98));  // High pulse
}

TEST(Monitor, Spo2LowShouldFail) {
  ASSERT_FALSE(vitalsOk(98.6, 72, 85));  // Low SpO₂
}
