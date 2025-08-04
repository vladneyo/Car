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

  Serial.begin(115200);
  gyro.setup();
}

void loop() {
  // ServoSweep.loop();
  
  // carservo.turn(LEFT);
  // delay(TURN_DELAY);

  // carservo.turn(FORWARD);
  // delay(TURN_DELAY);

  // carservo.turn(RIGHT);
  // delay(TURN_DELAY);

  // carservo.turn(FORWARD);
  // delay(TURN_DELAY);

  PRY pry = gyro.getPRY();
  // Print the values on the serial monitor
  Serial.print("Pitch: ");
  Serial.print(pry.pitch);
  Serial.print(" Roll: ");
  Serial.print(pry.roll);
  Serial.print(" Yaw: ");
  Serial.println(pry.yaw);
}