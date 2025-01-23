#include <Servo.h>

// 서보 모터 객체 생성
Servo myServo;

// 서보 모터 제어 핀
const int servoPin = 9;

// 압력센서 핀 번호 (아날로그 입력 핀)
const int fsrPin = A0;

// 플래그 변수
bool motorActivated = false;

// 임계값 설정
const int threshold = 40; // 임계값 설정 (필요에 따라 조정)

void setup() {
  // 서보 모터 핀을 설정
  myServo.attach(servoPin);

  // 초기 위치를 설정 (여기서는 0도로 설정)
  myServo.write(0);

  // 시리얼 통신 시작 (디버깅용)
  Serial.begin(9600);

  // 서보 모터 동작 시작
  Serial.println("Servo Activated!");

  // 플래그 변수를 true로 설정하여 서보 모터가 다시 작동하지 않도록 함
  motorActivated = true;

  // 서보 모터를 90도에서 0도까지 천천히 이동
  for (int angle = 90; angle >= 0; angle--) {
    // 압력센서 값 읽기
    int fsrValue = analogRead(fsrPin);
    
    // 센서 값과 목표 각도 값 시리얼 출력
    Serial.print("FSR Value: ");
    Serial.print(fsrValue);
    Serial.print(" | Servo Angle: ");
    Serial.println(angle);
    
    // 임계값 초과 여부 확인
    if (fsrValue > threshold) {
      Serial.println("Threshold exceeded, stopping servo.");
      break; // 서보 모터 이동 중지
    }

    // 서보 모터 각도 설정
    myServo.write(angle);
    delay(100);  // 100ms 대기. 90도 이동에 9초 걸림 (90 * 100ms = 9000ms)
  }
}

void loop() {
  // main loop가 빈 상태로 유지됨
}
