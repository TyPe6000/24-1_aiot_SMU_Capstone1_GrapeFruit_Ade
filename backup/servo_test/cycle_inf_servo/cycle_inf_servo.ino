#include <Servo.h>

Servo myservo;
int fsrpin=A2;
int fsr;

void setup() {
  myservo.attach(9);
  Serial.begin(9600);
}

void loop() {
  fsr = analogRead(fsrpin);
  Serial.println(fsr);
  fsr = map(fsr, 0, 1023, 0, 255);
  
  if (fsr<90)
  {
  //myservo.write(90); // 정지
  //delay(1000); // 3초간 지속
  //myservo.write(80); // 역회전
  //delay(3000); // 3초간 지속
  //myservo.write(90); // 정지
  //delay(3000); // 3초간 지속
    myservo.write(100); // 정회전
    delay(500); // 3초간 지속
  }
  else if (fsr>=90){
    myservo.write(90);
    delay(500);
  }
}