// #include <Servo.h>
// Servo srv;

// const int servoPin = 9;

// // A wide sweep range—narrower than this if your servo jitter-stalls early
// const int SWEEP_MIN = 600;
// const int SWEEP_MAX = 2400;
// const int STEP      = 100;    // change increment for finer granularity
// const int HOLD_MS   = 100;   // how long to hold each pulse

// void setup() {
//   Serial.begin(115200);
//   srv.attach(servoPin);
//   delay(1000);
// }

// void loop() {
//   // Sweep upward
//   for (int pw = SWEEP_MIN; pw <= SWEEP_MAX; pw += STEP) {
//     srv.writeMicroseconds(pw);
//     Serial.print("PW→ "); Serial.println(pw);
//     delay(HOLD_MS);
//   }
//   // Sweep downward
//   for (int pw = SWEEP_MAX; pw >= SWEEP_MIN; pw -= STEP) {
//     srv.writeMicroseconds(pw);
//     Serial.print("PW← "); Serial.println(pw);
//     delay(HOLD_MS);
//   }
// }

#include <Servo.h>
#include "servo-config.h"
Servo myservo;



// Map angle (-90…+90) → pulse (PULSE_MIN…PULSE_MAX)
int angleToPulse(int angle) {
  // clamp
  if (angle < -90) angle = -90;
  if (angle >  90) angle =  90;
  // map -90→PULSE_MIN, +90→PULSE_MAX
  return map(angle, -90, 90, SERVO_MIN_PWM, SERVO_MAX_PWM);
}

void setup() {
  myservo.attach(servoPin, SERVO_MIN_PWM, SERVO_MAX_PWM);
}

void loop() {
  myservo.writeMicroseconds( angleToPulse(-90) );   // full left
  delay(1000);

  myservo.writeMicroseconds( angleToPulse(0) );     // center
  delay(1000);

  myservo.writeMicroseconds( angleToPulse(90) );    // full right
  delay(1000);

  myservo.writeMicroseconds( angleToPulse(0) );     // center
  delay(1000);
}