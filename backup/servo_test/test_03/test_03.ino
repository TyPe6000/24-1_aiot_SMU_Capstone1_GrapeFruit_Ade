#include <Servo.h>                  
Servo servomotor;         //servomotor 를 선언해줍니다. LED를 사용할 때 int LED 와 비슷하다고 생각하시면 됩니다.
int pos = 0;

void setup() {
  servomotor.attach(9);       //pinMode(LED,OUTPUT)과 비슷하다고 생각하시면 됩니다.servomotor를 9번핀에 준비시킵니다.
}

void loop() {
  for(pos = 0; pos < 180; pos++)
  {
    servomotor.write(pos);             //servomotor.write(숫자)는 서보모터가 위치할 각입니다. 숫자가 90이면 90도로 이동합니다.
    delay(15);
  }
  for(pos = 180; pos > 0; pos--)
  {
    servomotor.write(pos);            //결과적으로 이 코드는 0~179도, 179~0도로 왕복합니다.
    delay(15);
  }
}