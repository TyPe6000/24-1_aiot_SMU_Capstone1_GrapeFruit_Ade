//구부림센서(flex)의 측정값이 200보다 크면 LED를 켜고 아니면 LED를 끄는 예제
#define led 2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//PC에 결과를 출력하겠다~
  pinMode(led,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  int sensor = analogRead(A0);
  Serial.println(sensor);

  if(sensor > 50){
    //LED를 켜는 조건
    digitalWrite(led,HIGH);
  }else{
    //LED를 끄는 조건
    digitalWrite(led,LOW);
  }
  
  delay(100);
}