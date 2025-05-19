/*
서보모터 위상 초기화 및 조정
1106 14시 설치 기준 0 위치로 움직이며 밀기, 180값 넣었을 시에 원위치
*/

#include <Servo.h>

Servo pushServo;    //pushServo 역할을 하는 ds3120mg는 6V기준 20kgf 토크인 고출력 일반 서보모터
Servo pullServo;    //pullServo 역할을 하는 MG995 무한회전 서보는 무한회전 서보 특성상 코드 구조가 약간 다름
static int pushServoPin = 8;
static int pullServoPin = 11;
int Angle = 20;
int pull = 20;      //pullServo 제어 변수, 0~180 범위 내에서 90이 정지, 커지거나 작아지면서 점점 빨라짐
int release = 160;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pushServo.attach(pushServoPin);
  pullServo.attach(pullServoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  //pushServo.write(Angle);
  //pullServo.write(pull);//반시계방향
  pullServo.write(release);
  delay(3000);
  Serial.println("A");

  //pushServo.write(160);
  //pullServo.write(release);
  pullServo.write(90);
  delay(3000);

  //pullServo.write(release);
  //delay(2000);
  

  /*if (Serial.available())
  {
    Angle = Serial.parseInt();
  }*/
}
