#pragma once

#include <Wire.h>

const int MPU = 0x68; // MPU6050 I2C address

struct PRY{
  double pitch, roll, yaw;
};

struct IMUError{
  double AccErrorX, AccErrorY, AccErrorZ, GyroErrorX, GyroErrorY, GyroErrorZ;
};

struct Gyro{
  void setup();
  PRY getPRY();
  private:
    IMUError calculate_IMU_error();
    IMUError imuerror;
};