#include "Adafruit_VL53L0X.h"
#include <Servo.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Servo myServo;

const int servoPin = 9;                // Servo motor pin
const int startAngle = 40;             // Start angle
const int endAngle = 10;               // End angle
const unsigned long moveDuration = 10000; // Servo movement duration (10 seconds)
const unsigned long delayInterval = 100; // Delay between servo steps

void setup() {
  Serial.begin(115200);
  myServo.attach(servoPin);
  myServo.write(startAngle);           // Set servo to start angle

  // Initialize VL53L0X sensor
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
}

void loop() {
  unsigned long startTime = millis();
  unsigned long currentTime = startTime; // Initialize currentTime properly
  int currentAngle = startAngle;
  float angleStep = float(startAngle - endAngle) / (moveDuration / delayInterval); // Use floating point division

  bool distanceInRange = false;

  while (currentTime - startTime < moveDuration && !distanceInRange) {
    VL53L0X_RangingMeasurementData_t measure;
    lox.rangingTest(&measure, false);

    if (measure.RangeStatus != 4) {
      int distance = measure.RangeMilliMeter;
      Serial.print("Distance (mm): ");
      Serial.println(distance);

      if (distance >= 300 && distance <= 500) {
        Serial.println("Distance within 300-500mm, stopping servo.");
        distanceInRange = true;
      }
    } else {
      Serial.println(" out of range ");
    }

    currentTime = millis();
    if (!distanceInRange) {
      currentAngle -= angleStep;
      myServo.write(currentAngle);
      delay(delayInterval);
    }
  }

  if (!distanceInRange) {
    myServo.write(endAngle); // Set final angle if distance was never in range
  }

  myServo.detach(); // Stop servo motor
}