#include <Servo.h>

Servo myservo;  // 서보 모터 객체
const int servoPin = 9;  // 서보 모터 핀

void setup() {
  myservo.attach(servoPin);  // 서보 모터 연결
  Serial.begin(9600);        // 시리얼 모니터 시작
}

void loop() {
  // 서보 모터를 0도에서 180도까지 움직여봄
  for (int pos = 0; pos <= 180; pos++) {
    myservo.write(pos);      // 서보를 pos 위치로 이동
    delay(15);               // 서보가 이동할 시간
  }

  delay(1000);  // 1초 대기

  // 서보 모터를 180도에서 0도까지 움직여봄
  for (int pos = 180; pos >= 0; pos--) {
    myservo.write(pos);      // 서보를 pos 위치로 이동
    delay(15);               // 서보가 이동할 시간
  }

  delay(1000);  // 1초 대기
}
