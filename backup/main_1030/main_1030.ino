/*
메인코드
서보 180 스타트, 작동시 0으로 이동

*/

#include <Servo.h>

Servo myservo;            //작동부 (서보모터) 셋업
const int servoPin = 9;

const int MSwitch = 4;   //작동조건 (마이크로스위치, 홀센서) 셋업
boolean MSVal;            //임계1 : 마이크로스위치, 임계2 : 홀센서
const int HallDIn = 3;
//const int HallAIn = A3;
int HDVal = 0;
int HAVal = 0;

unsigned long startMillis; // 대기 시간 시작 시점 저장
unsigned long RstartMillis; // 대기 시간 시작 시점 저장

const int FSRPin1 = A3;    //중지조건 (압력센서) 셋업
int FSRVal = 0;
//int HDtemp = 1;           //임계 1과 2를 위한 temp값
//int MStemp = 0;

void setup(){
  Serial.begin(9600);     //시리얼 모니터 셋업
  myservo.attach(servoPin); //모터 시작
  pinMode(HallDIn,INPUT);
  pinMode(MSwitch,INPUT);
  digitalWrite(MSwitch,1);  //마이크로스위치 풀업
  
}

void loop(){
  MSVal = digitalRead(MSwitch);   //마이크로스위치 입력
  HDVal = digitalRead(HallDIn);   //홀센서 입력
  //HAVal = analogRead(HallAIn);

  FSRVal = analogRead(FSRPin1);   //압력센서 입력
  int FSRCrit = 400;        //모터 중지 조건에 해당하는 값 설정
  int servoIDLE = 90;       //모터 정지 위치 90
  int servoPull = 20;       //모터 문 닫기
  int servoRelease = 160;   //모터 감긴 케이블 풀기
  bool GDCondition = false; //고스트 도어 작동조건 변수
  bool Release = false;
  const unsigned long duration = 1000; // 대기 시간 (밀리초 단위)
  const unsigned long Rduration = 5000; // 대기 시간 (밀리초 단위)

  myservo.write(servoIDLE);

  Serial.print("MSwitch = ");
  Serial.println(MSVal);
  Serial.print("HDVal = ");
  Serial.println(HDVal);
  //Serial.print("HAVal = ");
  //Serial.println(HAVal);

/*
  if (MStemp == 0 && HDVal == 0) HDtemp = HDVal;    //state 구분
  if (HDtemp == 0 && MSVal == 1) MStemp = MSVal;
  if (MStemp == 1 && HDVal == 0) {
    HDtemp = HDVal; MStemp = MSVal;
  }
*/
/*
 while(HDtemp ==0)                    //홀센서 임계2 TRUE 지남
  {
    int settime = millis();
    while(FSRVal < FSRCrit)             //압력센서 임계 미만 확인
    {
      int CamPushDelay = millis();      //캠 작동을 위한 딜레이 측정
      if (MStemp == 0)
        break;                          //임계1동작, 문닫힘 시 탈출
      else if (CamPushDelay > settime+1000){
        myservo.write(servoCamPush);    //임계2에서 임계1 사이, 2초 경과 -> 캠작동, 고스트 도어 실행
      }
      myservo.write(servoIDLE);
    }

  }
  //else if (MAVal == 1)
*/
//HDVal 0 덜닫힘 임계, MSVal 0 닫힘
  // HDVal이 0으로 바뀌는 순간 대기 타이머 시작
  if (HDVal == 0 && !GDCondition){
    startMillis = millis();
    GDCondition = true;
  }
  // 대기 시간 이후 모터 작동 시작
  if (GDCondition && millis() - startMillis >= duration){
    myservo.write(servoPull);
  }
  // 정지 조건: HDVal이 1이 되거나 MSVal이 0이 될 때 모터 정지
  if (HDVal == 1 || MSVal == 0) {
    myservo.write(servoIDLE);    // 모터 정지
    GDCondition = false;        // 상태 초기화
    Release = true;
    RstartMillis = millis();
  }
  if (Release && millis() - RstartMillis <= Rduration){
    myservo.write(servoRelease);
  }
  



}