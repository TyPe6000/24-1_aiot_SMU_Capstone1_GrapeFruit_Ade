#include <Servo.h>

//서보모터 기초 작동 테스트
//가변저항의 노브 위치값에 따라 모터의 작동 방향, 속도가 변화한다.

Servo Servo1;

int servoPin = 9;   //서보모터
int potPin = A0;    //가변저항(potentiometer)


void setup() {
    Servo1.attach(servoPin);
    Serial.begin(9600);
}


void loop() {
    int reading = analogRead(potPin);
    int angle = map(reading, 0, 1023, 0, 180);
    Servo1.write(angle);
    Serial.print("ANGLE: ");
    Serial.print(angle);
    delay(100);
}