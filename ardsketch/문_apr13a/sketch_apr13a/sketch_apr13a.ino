#include <Servo.h>

Servo myservo;
int servoPin = 12;
int initialAngle = 0;   // 시작 각도를 0으로 설정
int targetAngle = 40;   // 목표 각도를 40으로 설정
int duration = 4000;    // 이동을 완료하는 데 걸리는 시간 (밀리초)

void setup() {
  pinMode(servoPin, OUTPUT);
  myservo.attach(servoPin);
}

void loop() {
  int increment = 1; // 각도를 변경하는 값

  // 서보 모터 각도를 서서히 변경하여 이동
  for (int angle = initialAngle; angle <= targetAngle; angle += increment) {
    myservo.write(angle);
    delay(duration / (targetAngle - initialAngle)); // 이동 시간 조정
  }

  // 마지막으로 목표 각도에 정확히 맞춰줍니다.
  myservo.write(targetAngle);

  // 루프 종료
  while (true) {}
}
