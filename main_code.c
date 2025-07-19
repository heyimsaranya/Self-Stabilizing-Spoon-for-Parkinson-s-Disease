/* MPU6050 sensor with servo control for self-stabilizing spoon */

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Servo.h>


Servo spoonServo;
Adafruit_MPU6050 mpu;
void setup() {
  Serial.begin(115200);
  // Initialize Servo
  spoonServo.attach(3); // Change pin if needed
  spoonServo.write(0);  // Set initial position
  // Initialize MPU6050
  Wire.begin();
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1);
  }
  // Optional tuning
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  delay(100);
}

void loop() {
  sensors_event_t a, g, temp;
  // Get current sensor readings
  mpu.getEvent(&a, &g, &temp);
  // Get Y-axis acceleration value
  int value = a.acceleration.y;
  // Map to servo angle range
  value = map(value, -10, 10, 0, 180);
  value = constrain(value, 0, 180); // Avoid invalid servo values
  // Control the servo
  spoonServo.write(value);
  Serial.println(value);
  delay(10); // Adjust as needed
}

