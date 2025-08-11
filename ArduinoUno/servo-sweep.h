#pragma once

#include "Servo.h"

const int SWEEP_STEP      = 100;    // PWM increment for finer granularity
const int SWEEP_HOLD_MS   = 100;   // how long to hold each pulse

struct ServoSweep{
  void setup();
  void sweep();
  private:
    Servo srv;
};