#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

void setup() {
  Serial.begin(9600);
  Wire.begin();

  sensor.setTimeout(500);
  if (!sensor.init())
  {
    Serial.println("Failed to detect and initialize sensor!");
    while (1);
  }

  // 거리 측정 모드 설정
  sensor.setMeasurementTimingBudget(200000); // 타이밍 예산 설정(마이크로초)
  sensor.startContinuous(); // 연속 측정 모드 시작
}

void loop() {
  int distance = sensor.readRangeContinuousMillimeters();

  if (sensor.timeoutOccurred()) {
    Serial.print(" TIMEOUT");
  }

  Serial.print("Distance(mm): ");
  Serial.println(distance);
  delay(100);
}