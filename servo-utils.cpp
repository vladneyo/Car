#include "Arduino.h"
#include "servo-utils.h"
#include "servo-config.h"

// Map angle (-90…+90) → pulse (SERVO_MIN_PWM...SERVO_MAX_PWM)
int angleToPulse(int angle){
  // clamp
  if (angle < -90) angle = -90;
  if (angle >  90) angle =  90;
  // map -90 → SERVO_MIN_PWM, +90 → SERVO_MAX_PWM
  return map(angle, -90, 90, SERVO_MIN_PWM, SERVO_MAX_PWM);
}