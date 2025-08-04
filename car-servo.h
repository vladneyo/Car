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
  private:
    Servo srv;
};