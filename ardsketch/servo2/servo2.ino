#include <Servo.h>

Servo servomotor;
int pos = 40; // 시작 각도를 40도로 설정합니다.

void setup() {
  servomotor.attach(12);
}

void loop() {
  // 시작 각도로 이동
  servomotor.write(pos);
  delay(5000); // 5초 동안 유지

  // 10도씩 줄어들면서 0도까지 이동
  for (int i = pos; i >= 0; i -= 1) {
    servomotor.write(i);
    delay(100); // 이동 후 잠시 대기
  }
  
  // 0도에서 1초 동안 유지
  delay(1000);
}
