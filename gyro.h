#pragma once

#include <Wire.h>

const int MPU = 0x68; // MPU6050 I2C address

struct Gyro{
  void setup();
  void loop();
  private:
    void calculate_IMU_error();
};