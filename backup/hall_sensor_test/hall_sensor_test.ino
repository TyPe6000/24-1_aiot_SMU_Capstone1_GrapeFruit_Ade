/*
홀센서 테스트 코드
analog입력, digital입력 시리얼모니터에 출력

Hall sensor - Arduino
VIN - VIN
GND - GND
A0 - A2
D0 - 3
*/

const int analogInPin = A2;
const int digitalInPin = 3;
int sensorValue = 0;        // value read from the pot
int digitValue = 0;

void setup() {
  pinMode(digitalInPin,INPUT);
  Serial.begin(9600);
}

void loop() {
  sensorValue = analogRead(analogInPin);
  digitValue = digitalRead(digitalInPin);
  //Serial.print("ANA = ");
  //Serial.println(sensorValue);
  Serial.print("DIG = ");
  Serial.println(digitValue);
  
  delay(100);
}