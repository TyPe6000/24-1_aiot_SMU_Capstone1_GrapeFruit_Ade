#include "Adafruit_VL53L0X.h"
#include <Servo.h>

Adafruit_VL53L0X lox = Adafruit_VL53L0X();
Servo myServo;

const int servoPin = 9;                  // 서보 모터 연결 핀
const int startAngle = 40;               // 시작 각도
const int endAngle = 10;                 // 종료 각도
const unsigned long moveDuration = 10000; // 서보 모터 이동 시간 (10초)
const unsigned long delayInterval = 20;  // 서보 모터 이동 단계 사이의 지연 시간 (20ms)

void setup() {
  Serial.begin(115200);
  myServo.attach(servoPin);
  myServo.write(startAngle); // 서보 모터를 시작 각도로 설정

  // VL53L0X 센서 초기화
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while (1);
  }
  Serial.println(F("VL53L0X API Simple Ranging example\n\n"));
}

void loop() {
  unsigned long startTime = millis();
  unsigned long currentTime;
  int currentAngle = startAngle;
  int totalSteps = (moveDuration / delayInterval);
  float angleStep = (float)(startAngle - endAngle) / totalSteps;

  // 서보 모터 움직임
  while (true) {
    // 거리 측정 및 처리
    measureAndHandleDistance();

    // 서보 모터 각도 조정
    currentTime = millis();
    if (currentTime - startTime >= moveDuration) {
      myServo.write(endAngle); // 최종 각도 설정
      break; // 루프 종료
    } else {
      currentAngle -= angleStep;
      myServo.write(currentAngle);
      delay(delayInterval);
    }
  }
}

void measureAndHandleDistance() {
  VL53L0X_RangingMeasurementData_t measure;
  if (lox.rangingTest(&measure, false)) {
    if (measure.RangeStatus != 4) {
      int distance = measure.RangeMilliMeter;
      Serial.print("Distance (mm): ");
      Serial.println(distance);

      if (distance >= 300 && distance <= 500) {
        Serial.println("Distance within 300-500mm, stopping servo.");
        myServo.detach(); // 서보 모터 정지
        while (true) {
          // 서보 모터가 정지할 때까지 대기
        }
      }
    } else {
      Serial.println(" out of range ");
    }
  } else {
    Serial.println("Sensor read error");
  }
}
