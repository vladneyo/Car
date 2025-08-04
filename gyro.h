#pragma once

#include <Wire.h>

const int MPU = 0x68; // MPU6050 I2C address

struct PRY{
  float pitch, roll, yaw;
};

struct Gyro{
  void setup();
  PRY getPRY();
  private:
    void calculate_IMU_error();
};