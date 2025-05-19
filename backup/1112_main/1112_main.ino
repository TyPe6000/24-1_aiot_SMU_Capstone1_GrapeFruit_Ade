#include <Servo.h>

Servo myservo;                // 서보 모터 설정
const int servoPin = 11;

const int MSwitch = 4;        // 마이크로스위치 핀
boolean MSVal;                // 임계1: 마이크로스위치, 임계2: 홀센서
const int HallDIn = 5;
int HDVal = 0;

const int FSRPin1 = A3;       // 압력 센서 핀
int FSRVal = 0;

const int FSRCrit = 400;      // 모터 중지 조건 값 설정
const int servoIDLE = 90;     // 모터 정지 위치
const int servoPull = 20;     // 모터 문 닫기 위치
const int servoRelease = 160; // 모터 감긴 케이블 풀기 위치

bool GDCondition = false;     // 고스트 도어 작동 조건 변수
bool Release = false;

unsigned long startMillis;    // 대기 시간 시작 시점 저장
unsigned long RstartMillis;   // 릴리스 대기 시간 시작 시점 저장
const unsigned long duration = 1000;    // 대기 시간 (밀리초 단위)
const unsigned long Rduration = 5000;   // 릴리스 대기 시간 (밀리초 단위)

// 현재 모터 위치를 저장하는 변수
int currentServoPos = servoIDLE;

void setup() {
  Serial.begin(9600);         // 시리얼 모니터 설정
  myservo.attach(servoPin);   // 모터 시작
  pinMode(HallDIn, INPUT);
  pinMode(MSwitch, INPUT_PULLUP);  // 마이크로스위치 풀업 설정
  
  // 서보 모터의 초기 위치를 90도로 설정
  myservo.write(servoIDLE);   // 초기 모터 위치 설정
  currentServoPos = servoIDLE; // currentServoPos 초기화
  
  delay(500); // 모터가 초기 위치로 안정될 때까지 잠시 대기
}

void loop() {
  // 센서 및 스위치 상태 업데이트
  MSVal = digitalRead(MSwitch);   // 마이크로스위치 입력
  HDVal = digitalRead(HallDIn);   // 홀센서 입력
  FSRVal = analogRead(FSRPin1);   // 압력 센서 입력

  // 센서값 출력 (디버깅용)
  Serial.print("MSwitch = ");
  Serial.println(MSVal);
  Serial.print("HDVal = ");
  Serial.println(HDVal);

  // HDVal이 0으로 바뀌는 순간 대기 타이머 시작
  if (HDVal == 0 && !GDCondition) {
    startMillis = millis();
    GDCondition = true;
  }

  // 대기 시간 이후 모터 작동 시작
  if (GDCondition && millis() - startMillis >= duration) {
    currentServoPos = servoPull;
    myservo.write(currentServoPos);
  }

  // 정지 조건: HDVal이 1이 되거나 MSVal이 0이 될 때 모터 정지
  if (HDVal == 1 || MSVal == 0) {
    currentServoPos = servoIDLE;
    myservo.write(currentServoPos);
    GDCondition = false;         // 상태 초기화
    Release = true;              // 릴리스 상태 활성화
    RstartMillis = millis();     // 릴리스 타이머 시작
  }

  // 릴리스 조건: 릴리스 타이머가 Rduration까지 유지되도록 설정
  if (Release && millis() - RstartMillis <= Rduration) {
    currentServoPos = servoRelease;
    myservo.write(currentServoPos);
  } else if (Release && millis() - RstartMillis > Rduration) {
    currentServoPos = servoIDLE;
    myservo.write(currentServoPos);  // 릴리스 완료 후 모터 정지
    Release = false;                 // 릴리스 상태 초기화
  }

  // 모터 위치를 시리얼로 출력
  Serial.print("Current Servo Position = ");
  Serial.println(currentServoPos);
}
