/*
마이크로스위치 테스트 코드
스위치 누르면 0 떼면 1을 각각 시리얼 출력 
문열면1 문닫으면0
Switch - Arduino
COM - GND
NC - 4
*/
const int switchPin = 4;

boolean switchVal;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(switchPin,INPUT);

  digitalWrite(switchPin, 1);   //풀업
}

void loop() {
  // put your main code here, to run repeatedly:
  switchVal = digitalRead(switchPin);
  Serial.print("switch = ");
  Serial.println(switchVal);
}
