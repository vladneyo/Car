#include "Servo.h"
#include "Arduino.h"
#include <Wire.h>

#include "gyro.h"

double AccX, AccY, AccZ;
double GyroX, GyroY, GyroZ;
double accAngleX, accAngleY, accAngleZ, gyroAngleX, gyroAngleY, gyroAngleZ;
double roll, pitch, yaw;
double AccErrorX, AccErrorY, AccErrorZ, GyroErrorX, GyroErrorY, GyroErrorZ;
double elapsedTime, currentTime, previousTime;
int c = 0;
int calibrationNumber = 200;
double AccSSF = 16384.0000000, GyroSSF = 131.0000000; // from https://invensense.tdk.com/wp-content/uploads/2015/02/MPU-6000-Datasheet1.pdf
double AccXcalib = -0.05, AccYcalib = 0.05, AccZcalib = 1.05;

void Gyro::setup(){
  Wire.begin();                      // Initialize comunication
  Wire.beginTransmission(MPU);       // Start communication with MPU6050 // MPU=0x68
  Wire.write(0x6B);                  // Talk to the register 6B
  Wire.write(0x00);                  // Make reset - place a 0 into the 6B register
  Wire.endTransmission(true);        //end the transmission

  accAngleX = accAngleY = accAngleZ = gyroAngleX = gyroAngleY = gyroAngleZ = 0.00000;
  AccErrorX = AccErrorY = AccErrorZ = GyroErrorX = GyroErrorY = GyroErrorZ = 0.00000;

  imuerror = calculate_IMU_error();
  delay(20);
}

PRY Gyro::getPRY(){
  // === Read acceleromter data === //
  Wire.beginTransmission(MPU);
  Wire.write(0x3B); // Start with register 0x3B (ACCEL_XOUT_H)
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 6 registers total, each axis value is stored in 2 registers
  
  //For a range of +-2g, we need to divide the raw values by 16384, according to the datasheet
  AccX = (Wire.read() << 8 | Wire.read()) / AccSSF + AccXcalib; // X-axis value
  AccY = (Wire.read() << 8 | Wire.read()) / AccSSF + AccYcalib; // Y-axis value
  AccZ = (Wire.read() << 8 | Wire.read()) / AccSSF + AccZcalib; // Z-axis value

  // Calculating Roll and Pitch from the accelerometer data
  accAngleX = (atan(AccY / sqrt(pow(AccX, 2) + pow(AccZ, 2))) * 180 / PI) - imuerror.AccErrorX;
  accAngleY = (atan(-1 * AccX / sqrt(pow(AccY, 2) + pow(AccZ, 2))) * 180 / PI) - imuerror.AccErrorY;
  accAngleZ = (atan2(sqrt(AccX*AccX + AccY*AccY), AccZ) * 180.0 / PI) - imuerror.AccErrorZ;
  
  // === Read gyroscope data === //
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  Wire.beginTransmission(MPU);
  Wire.write(0x43); // Gyro data first register address 0x43
  Wire.endTransmission(false);
  Wire.requestFrom(MPU, 6, true); // Read 4 registers total, each axis value is stored in 2 registers
  GyroX = (Wire.read() << 8 | Wire.read()) / GyroSSF; // For a 250deg/s range we have to divide first the raw value by 131.0, according to the datasheet
  GyroY = (Wire.read() << 8 | Wire.read()) / GyroSSF;
  GyroZ = (Wire.read() << 8 | Wire.read()) / GyroSSF;
  
  // Correct the outputs with the calculated error values
  GyroX = GyroX - imuerror.GyroErrorX;
  GyroY = GyroY - imuerror.GyroErrorY;
  GyroZ = GyroZ - imuerror.GyroErrorZ;
  
  // Currently the raw values are in degrees per seconds, deg/s, so we need to multiply by sendonds (s) to get the angle in degrees
  gyroAngleX = gyroAngleX + GyroX * elapsedTime; // deg/s * s = deg
  gyroAngleY = gyroAngleY + GyroY * elapsedTime;
  gyroAngleZ = gyroAngleZ + GyroZ * elapsedTime;
  
  // Serial.print("AccX: ");
  // Serial.print(AccX, 2);
  // Serial.print(" AccY: ");
  // Serial.print(AccY, 2);
  // Serial.print(" AccZ: ");
  // Serial.println(AccZ, 2);
  
  // Complementary filter - combine acceleromter and gyro angle values
  const double g2aration = 0.99;
  roll = g2aration * gyroAngleX + (1-g2aration) * accAngleX;
  pitch = g2aration * gyroAngleY + (1-g2aration) * accAngleY;
  yaw = g2aration * gyroAngleZ + (1-g2aration) * accAngleZ;
  // yaw =  yaw + GyroZ * elapsedTime;

  PRY pry;
  pry.pitch = pitch;
  pry.roll = roll;
  pry.yaw = yaw;

  return pry;
}

IMUError Gyro::calculate_IMU_error(){
  // We can call this funtion in the setup section to calculate the accelerometer and gyro data error. From here we will get the error values used in the above equations printed on the Serial Monitor.
  // Note that we should place the IMU flat in order to get the proper values, so that we then can the correct values
  // Read accelerometer values calibrationNumber times
  while (c < calibrationNumber) {
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    AccX = (Wire.read() << 8 | Wire.read()) / AccSSF + AccXcalib;
    AccY = (Wire.read() << 8 | Wire.read()) / AccSSF + AccYcalib;
    AccZ = (Wire.read() << 8 | Wire.read()) / AccSSF + AccZcalib;
    // Sum all readings
    AccErrorX = AccErrorX + ((atan((AccY) / sqrt(pow((AccX), 2) + pow((AccZ), 2))) * 180 / PI));
    AccErrorY = AccErrorY + ((atan(-1 * (AccX) / sqrt(pow((AccY), 2) + pow((AccZ), 2))) * 180 / PI));
    AccErrorZ = AccErrorZ + ((atan2(sqrt(AccX*AccX + AccY*AccY), AccZ) * 180 / PI));
    c++;
  }
  //Divide the sum by calibrationNumber to get the error value
  AccErrorX = AccErrorX / calibrationNumber;
  AccErrorY = AccErrorY / calibrationNumber;
  AccErrorZ = AccErrorZ / calibrationNumber;
  c = 0;
  // Read gyro values calibrationNumber times
  while (c < calibrationNumber) {
    Wire.beginTransmission(MPU);
    Wire.write(0x43);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU, 6, true);
    GyroX = Wire.read() << 8 | Wire.read();
    GyroY = Wire.read() << 8 | Wire.read();
    GyroZ = Wire.read() << 8 | Wire.read();
    // Sum all readings
    GyroErrorX = GyroErrorX + (GyroX / GyroSSF);
    GyroErrorY = GyroErrorY + (GyroY / GyroSSF);
    GyroErrorZ = GyroErrorZ + (GyroZ / GyroSSF);
    c++;
  }
  //Divide the sum by calibrationNumber to get the error value
  GyroErrorX = GyroErrorX / calibrationNumber;
  GyroErrorY = GyroErrorY / calibrationNumber;
  GyroErrorZ = GyroErrorZ / calibrationNumber;

  IMUError error;
  error.AccErrorX = AccErrorX;
  error.AccErrorY = AccErrorY;
  error.AccErrorZ = AccErrorZ;
  error.GyroErrorX = GyroErrorX;
  error.GyroErrorY = GyroErrorY;
  error.GyroErrorZ = GyroErrorZ;

  // Print the error values on the Serial Monitor
  Serial.print("AccErrorX: ");
  Serial.println(error.AccErrorX);
  Serial.print("AccErrorY: ");
  Serial.println(error.AccErrorY);
  Serial.print("AccErrorZ: ");
  Serial.println(error.AccErrorZ);
  Serial.print("GyroErrorX: ");
  Serial.println(error.GyroErrorX);
  Serial.print("GyroErrorY: ");
  Serial.println(error.GyroErrorY);
  Serial.print("GyroErrorZ: ");
  Serial.println(error.GyroErrorZ);
  delay(3000);

  return error;
}