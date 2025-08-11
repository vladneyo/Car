#include "servo-config.h"
#include "servo-utils.h"

#include "gyro.h"
Gyro gyro;

#include "ultrasonic.h"
Ultrasonic us;

#include "car-servo.h"
CarServo servo;

// const int TURN_DELAY = 1000;

float initAngle;

void setup() {
  Serial.begin(115200);

  servo.setup();
  gyro.setup();
  us.setup();

  servo.resetAngle();
  initAngle = gyro.getPRY().yaw;
}

void loop() { 

  PRY pry = gyro.getPRY();
  // Print the values on the serial monitor
  Serial.print("Pitch: ");
  Serial.print(pry.pitch);
  Serial.print(" Roll: ");
  Serial.print(pry.roll);
  Serial.print(" Yaw: ");
  Serial.println(pry.yaw);

  float deltaAngle = initAngle - pry.yaw;
  servo.turnAngle(-(int)deltaAngle);
  // delay(5);
}