// 3번과 4번 핀은 모터 제어에 관한 핀
int IN1Pin = 3;
int IN2Pin = 4;
// 5번핀은 모터의 힘을 설정해주는 핀
int ENPin = 5;
// 박막 압2
int sensorPin = A2;


void setup() {
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT); // 3, 4번 제어핀들은 핀모드를 출력은로 설정
  analogWrite(ENPin, 255); //5번 핀에 255의 최대 힘을 설정한다. 
}

void loop() {    
  //Go : 핀 3, 핀 4 에 신호를 다르게 하면 전진
  digitalWrite(IN1Pin, HIGH); 
  digitalWrite(IN2Pin, LOW);
  delay(5000);//5sec 

  //Back : 핀 3, 핀 4 에 신호를 다르게 하면 후진
  digitalWrite(IN1Pin, LOW);
  digitalWrite(IN2Pin, HIGH);  
  delay(5000);//5sec
  
  //Brake (Stop) 핀 3, 4에 똑같이 High를 주거나 Low을 주면 은 멈춘다.
  digitalWrite(IN1Pin, HIGH);
  digitalWrite(IN2Pin, HIGH);
  delay(5000);//1sec
}