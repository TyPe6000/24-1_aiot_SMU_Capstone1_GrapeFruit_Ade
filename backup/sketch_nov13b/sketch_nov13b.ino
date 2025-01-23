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
const int FSRCrit = 400;

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
    // 평시 상태 (MSVal == 1 && HDVal == 1)에서는 state.Release가 true로 바뀌지 않도록 설정
    if ((state.HDVal == 1 || state.MSVal == 0) && !(state.MSVal == 1 && state.HDVal == 1)) {
        state.desiredServoPos = servoIDLE;
        moveServo();
        state.GDCondition = false;
        state.Release = true;
        state.RstartMillis = millis();
    }
}

void handleRelease() {
    if (state.Release) {
        unsigned long elapsedTime = millis() - state.RstartMillis;
        
        if (elapsedTime <= Rduration) {
            state.desiredServoPos = servoRelease;
        } else {
            state.desiredServoPos = servoIDLE;
            state.Release = false;
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
    checkGhostDoorCondition();
    checkStopCondition();
    handleRelease();
    printDebugInfo();
}
