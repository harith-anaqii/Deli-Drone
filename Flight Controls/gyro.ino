#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  mpu.initialize();
  
  Serial.println("MPU6050 initialized");
}

void loop() {
  int16_t gyroX, gyroY, gyroZ;
  
  mpu.getRotation(&gyroX, &gyroY, &gyroZ);