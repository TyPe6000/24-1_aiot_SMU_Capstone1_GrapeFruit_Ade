// 3번과 4번 핀은 모터 제어에 관한 핀
int IN1Pin = 3;
int IN2Pin = 4;
// 5번핀은 모터의 힘을 설정해주는 핀
int ENPin = 5;
// 박막 압력센서 값 받아오는 아날로그 핀
int sensorPin = A2;


void setup() {
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT); // 3, 4번 제어핀들은 핀모드를 출력은로 설정
  analogWrite(ENPin, 255); //5번 핀에 255의 최대 힘을 설정한다. 
  Serial.begin(9600);
}

void loop() {
  int sensor = analogRead(sensorPin);
  Serial.print("SENSOR:");
  Serial.println(sensor);    
  //Go : 핀 3, 핀 4 에 신호를 다르게 하면 전진


  //Back : 핀 3, 핀 4 에 신호를 다르게 하면 후진
  //digitalWrite(IN1Pin, LOW);
  //digitalWrite(IN2Pin, HIGH);  
  //delay(5000);//5sec
  if (sensor>650)
  {
    //Brake (Stop) 핀 3, 4에 똑같이 High를 주거나 Low을 주면 은 멈춘다.
    digitalWrite(IN1Pin, HIGH);
    digitalWrite(IN2Pin, HIGH);
    Serial.print("Alert!");
    delay(300);//1sec
  }
  else
  {
    digitalWrite(IN1Pin, HIGH); 
    digitalWrite(IN2Pin, LOW);
   delay(100);//5sec 
  }
}