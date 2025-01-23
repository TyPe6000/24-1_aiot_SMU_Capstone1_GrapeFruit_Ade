/*
캠 - 임계1 상호작용 테스트 코드
//스위치 누르면 0 떼면 1을 각각 시리얼 출력
Switch - Arduino
COM - GND
NC - 4
*/
#include <Servo.h>
Servo myservo;
const int servoPin = 8;
const int switchPin = 4;
const int hallPin = 3;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchPin,INPUT);
  pinMode(hallPin,INPUT);
  myservo.attach(servoPin);
  digitalWrite(switchPin, 1);   //풀업
}

void loop() {
  // put your main code here, to run repeatedly:
  
  boolean switchVal = digitalRead(switchPin);
  int hallVal = digitalRead(hallPin);
  Serial.print("switch = ");
  Serial.println(switchVal);
  Serial.print("hall = ");
  Serial.println(hallVal);
  

  int ServoCamPush = 0;
  int ServoIDLE = 90;
  myservo.write(ServoIDLE);
  if (switchVal ==1)
  {
    myservo.write(ServoCamPush);
  }
  else
  {
    myservo.write(ServoIDLE);
  }
  
}
