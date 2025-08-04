// #include "servo-config.h"
// #include "servo-utils.h"

// #include "servo-sweep.h"
// ServoSweep ServoSweep;

// #include "car-servo.h"
// CarServo carservo;

#include "gyro.h"
Gyro gyro;

// const int TURN_DELAY = 1000;

void setup() {
  // ServoSweep.setup();
  // carservo.setup();
  gyro.setup();
}

void loop() {
  gyro.loop();
  // ServoSweep.loop();
  
  // carservo.turn(LEFT);
  // delay(TURN_DELAY);

  // carservo.turn(FORWARD);
  // delay(TURN_DELAY);

  // carservo.turn(RIGHT);
  // delay(TURN_DELAY);

  // carservo.turn(FORWARD);
  // delay(TURN_DELAY);
}