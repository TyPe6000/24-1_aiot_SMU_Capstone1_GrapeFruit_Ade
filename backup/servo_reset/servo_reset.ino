/*
서보모터 위상 초기화 및 조정
1106 14시 설치 기준 0 위치로 움직이며 밀기, 180값 넣었을 시에 원위치
*/

#include <Servo.h>

Servo myservo;
static int pushServoPin = 8;
static int pullServoPin = 9;
int Angle = 20;
int pull = 30;
int release = 150;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myservo.attach(servoPin);
}

void loop() {
  // put your main code here, to run repeatedly:
  myservo.write(Angle);
  //Serial.println(Angle);
  //myservo.write(90);
  delay(2000);

  myservo.write(160);
  delay(2000);
  /*for(int i=0;i<180;i++)
  {
    myservo.write(Angle-i);
    delay(100);
    Serial.println(Angle-i);
  }*/
  /*if (Angle>0){
    Angle--; 
    delay(50);
  }*/

  /*if (Serial.available())
  {
    Angle = Serial.parseInt();
  }*/
}
