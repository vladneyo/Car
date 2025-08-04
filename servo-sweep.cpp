#include "Arduino.h"
#include "servo-config.h"
#include "servo-sweep.h"

void ServoSweep::setup() {
  Serial.begin(115200);
  srv.attach(servoPin);
  delay(1000);
}

void ServoSweep::loop() {
  // Sweep upward
  for (int pw = SERVO_MIN_PWM; pw <= SERVO_MAX_PWM; pw += SWEEP_STEP) {
    srv.writeMicroseconds(pw);
    Serial.print("PW→ "); Serial.println(pw);
    delay(SWEEP_HOLD_MS);
  }
  // Sweep downward
  for (int pw = SERVO_MAX_PWM; pw >= SERVO_MIN_PWM; pw -= SWEEP_STEP) {
    srv.writeMicroseconds(pw);
    Serial.print("PW← "); Serial.println(pw);
    delay(SWEEP_HOLD_MS);
  }
}