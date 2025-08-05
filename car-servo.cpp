#include "Servo.h"

#include "servo-config.h"
#include "car-servo.h"
#include "servo-utils.h"
#include "assert.h"


void CarServo::setup(){
  srv.attach(servoPin, SERVO_MIN_PWM, SERVO_MAX_PWM);
}

void CarServo::turn(Direction direction){
  switch (direction) {
    case LEFT:
      srv.writeMicroseconds(angleToPulse(-90));
      break;
    case FORWARD:
      srv.writeMicroseconds(angleToPulse(0));
      break;
    case RIGHT:
      srv.writeMicroseconds(angleToPulse(90));
      break;
  }
}

void CarServo::turnAngle(int angle){
  // ASSERT(angle > -90 && angle < 90);
  if (angle < -90 || angle > 90) {
    return;
  }

  srv.writeMicroseconds(angleToPulse(angle));
}

void CarServo::resetAngle(){
  turn(FORWARD);
}