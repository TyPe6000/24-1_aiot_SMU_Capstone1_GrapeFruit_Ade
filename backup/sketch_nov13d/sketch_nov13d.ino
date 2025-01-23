/*
모터에 케이블 시계 방향으로 감기

결선도는 첨부된 이미지 참조
*/

#include <Servo.h>

// 서보 모터 설정
Servo myservo;
const int servoPin = 11;

// 센서 핀 설정
const int MSwitch = 4;
const int HallDIn = 7;
const int FSRPin1 = A3;

// 서보 모터 위치 상수
const int servoIDLE = 90;     // 모터 정지 위치
const int servoPull = 20;     // 모터 문 닫기 위치
const int servoRelease = 160; // 모터 케이블 풀기 위치

// 센서 임계값
const int FSRCrit = 200;

// 타이머 설정
const unsigned long duration = 1000;
const unsigned long Rduration = 3000; // 릴리스 대기 시간 조정

// 상태 변수
struct SystemState {
    bool MSVal;
    int HDVal;
    int FSRVal;
    bool GDCondition;
    bool Release;
    int desiredServoPos;
    unsigned long startMillis;
    unsigned long RstartMillis;
} state;

void setup() {
    Serial.begin(9600);
    
    // 핀 모드 설정
    pinMode(HallDIn, INPUT);
    pinMode(MSwitch, INPUT_PULLUP);
    
    // 서보 모터 초기화
    myservo.attach(servoPin);
    state.desiredServoPos = servoIDLE;
    myservo.write(state.desiredServoPos);
    
    // 상태 초기화
    state.GDCondition = false;
    state.Release = false;
    
    delay(500);
}

void updateSensors() {
    state.MSVal = digitalRead(MSwitch);
    state.HDVal = digitalRead(HallDIn);
    state.FSRVal = analogRead(FSRPin1);
}

void moveServo() {
    if (state.desiredServoPos != myservo.read()) {
        myservo.write(state.desiredServoPos);
    }
}

// Force Stop 조건을 확인하고 처리하는 함수
void checkForceStop() {
    if (state.FSRVal > FSRCrit) {
        state.desiredServoPos = servoIDLE;  // 모터 정지
        moveServo();
        
        Serial.print("ALERT!!! Force Stop triggered due to high FSRVal.\n");
        // Release 상태를 설정하고 Release 타이머 시작
        state.Release = true;
        state.RstartMillis = millis();
    }
}

void checkGhostDoorCondition() {
    if (state.HDVal == 0 && !state.GDCondition) {
        state.startMillis = millis();
        state.GDCondition = true;
    }
    
    if (state.GDCondition && millis() - state.startMillis >= duration) {
        state.desiredServoPos = servoPull;
    } else if (!state.GDCondition) { // 기본 상태로 돌아가기
        state.desiredServoPos = servoIDLE;
    }
    moveServo();
}

void checkStopCondition() {
    if ((state.HDVal == 1 || state.MSVal == 0) && !(state.MSVal == 1 && state.HDVal == 1)) {
        state.desiredServoPos = servoIDLE;
        moveServo();
        state.GDCondition = false;
        
        // Release 상태 전환 및 타이머 시작
        state.Release = true;
        state.RstartMillis = millis();
    }

    // 추가된 부분: MSVal == 1과 HDVal == 1로 상태가 돌아왔을 때 모터 초기화
    if (state.MSVal == 1 && state.HDVal == 1) {
        state.desiredServoPos = servoIDLE;
        state.GDCondition = false;
        state.Release = false;  // Release 상태 초기화
        moveServo();
    }
}

void handleRelease() {
    if (state.Release) {
        unsigned long elapsedTime = millis() - state.RstartMillis;
        
        if (elapsedTime <= Rduration) {
            state.desiredServoPos = servoRelease;
        } else {
            // Release 상태가 끝난 후 desiredServoPos를 servoIDLE로 복원
            state.desiredServoPos = servoIDLE;
            state.Release = false; // Release 상태 초기화
        }
        moveServo();
    }
}

void printDebugInfo() {
    Serial.print("MSwitch = ");
    Serial.print(state.MSVal);
    Serial.print("  HDVal = ");
    Serial.print(state.HDVal);
    Serial.print("  FSRVal = ");
    Serial.print(state.FSRVal);
    Serial.print("  Desired Servo Position = ");
    Serial.println(state.desiredServoPos);
}

void loop() {
    updateSensors();
    
    checkForceStop();          // Force Stop 조건 확인을 가장 먼저 실행
    
    // Force Stop이 아닌 경우에만 다른 조건 함수 실행
    if (!state.Release) { 
        checkGhostDoorCondition();
        checkStopCondition();
    }
    
    handleRelease(); // Release 상태에 따라 desiredServoPos를 업데이트
    printDebugInfo();
}
