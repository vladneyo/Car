#include "Arduino.h"

#include "ultrasonic.h"

void Ultrasonic::setup(){
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
}

float Ultrasonic::checkdistance()
{
    digitalWrite(12, LOW);
    delayMicroseconds(2);
    digitalWrite(12, HIGH);
    delayMicroseconds(10);
    digitalWrite(12, LOW);
    float distance = pulseIn(13, HIGH) / 58.00;
    delay(10);
    return distance;
}