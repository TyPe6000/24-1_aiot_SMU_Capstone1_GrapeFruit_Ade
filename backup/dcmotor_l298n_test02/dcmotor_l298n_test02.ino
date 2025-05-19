// 3번과 4번 핀은 모터 제어에 관한 핀
int IN1Pin = 3;
int IN2Pin = 4;
// 5번핀은 모터의 힘을 설정해주는 핀
int ENPin = 5;
// 박막 압2
int sensorPin = A2;
// 로터리 엔코더 테스트
int RE_SW = 9;
int RE_DT = 10;
int RE_CLK = 11;
int REtemp;
int REtemprotation = 100;
int RErotation = 100;

void setup() {
  pinMode(IN1Pin, OUTPUT);
  pinMode(IN2Pin, OUTPUT); // 3, 4번 제어핀들은 핀모드를 출력은로 설정
  analogWrite(ENPin, 255); //5번 핀에 255의 최대 힘을 설정한다. 
  
  Serial.begin(9600);

  pinMode(RE_SW, INPUT);  //로터리 엔코더 테스트
  pinMode(RE_DT, INPUT);
  pinMode(RE_CLK, INPUT);
}


int getEncoderTurn()
{
  static int oldDT = LOW;
  static int oldCLK = LOW;
  
  int result = 0;
  int newDT = digitalRead(RE_DT);
  int newCLK = digitalRead(RE_CLK);

  if ( newDT != oldDT || newCLK != oldCLK)
  {
    if (oldDT == LOW && newDT == HIGH)
    {
      result = -(oldCLK * 2 -1);
    }
  }
  oldDT = newDT;
  oldCLK = newCLK;

  return result;
}

void loop() {
 int change = getEncoderTurn();
 if (change != REtemp)
 {
  RErotation = RErotation + change;
  if (RErotation != REtemprotation)
  {
    Serial.print("RErotation");
    Serial.println(RErotation);
  }
  REtemprotation = RErotation;
 }
 REtemp = change; 

  /*
  int sensor = analogRead(sensorPin);
  Serial.print("sensor");
  Serial.println(sensor);

  //Go : 핀 3, 핀 4 에 신호를 다르게 하면 전진
  digitalWrite(IN1Pin, HIGH); 
  digitalWrite(IN2Pin, LOW);
  delay(100);//5sec 

  //Back : 핀 3, 핀 4 에 신호를 다르게 하면 후진
  //digitalWrite(IN1Pin, LOW);
  //digitalWrite(IN2Pin, HIGH);  
  //delay(5000);//5sec
  if (sensor>300)
  {
    //Brake (Stop) 핀 3, 4에 똑같이 High를 주거나 Low을 주면 은 멈춘다.
    digitalWrite(IN1Pin, HIGH);
    digitalWrite(IN2Pin, HIGH);
    delay(500);//1sec
  }
  */
}
