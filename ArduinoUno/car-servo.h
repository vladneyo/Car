#pragma once

#include "Servo.h"

enum Direction{
  LEFT,
  FORWARD,
  RIGHT
};

struct CarServo{
  void setup();
  void turn(Direction direction);
  // angle is between -90 (max left) and 90 (max right)
  void turnAngle(int angle);
  void resetAngle();
  private:
    Servo srv;
};