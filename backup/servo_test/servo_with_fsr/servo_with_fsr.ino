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
  //fsr = map(fsr, 0, 1023, 0, 255);
  
  if (fsr>=300)   //센서 눌러 압력이 임계를 넘으면 작동한다.
  {
    myservo.write(90); 
    delay(100);
  }
  else if (fsr<300)
  {
    myservo.write(180);
    delay(100);
  }
}