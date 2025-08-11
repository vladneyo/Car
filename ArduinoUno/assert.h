#pragma once
#include <Arduino.h>

// Configure: which pin to blink on failure (optional)
#ifndef ASSERT_LED_PIN
#define ASSERT_LED_PIN 13
#endif

inline void _assertFail(const char* file, int line) {
  // Ensure Serial is up (you can remove if you don't want Serial)
  Serial.begin(115200);
  Serial.print("ASSERT FAILED: ");
  Serial.print(file);
  Serial.print(":");
  Serial.println(line);

  // Blink LED forever so you see a failure
  pinMode(ASSERT_LED_PIN, OUTPUT);
  while (true) {
    digitalWrite(ASSERT_LED_PIN, HIGH);
    delay(200);
    digitalWrite(ASSERT_LED_PIN, LOW);
    delay(200);
  }
}

#define ASSERT(expr)                                \
  do {                                              \
    if (!(expr)) {                                  \
      _assertFail(__FILE__, __LINE__);              \
    }                                               \
  } while (0)