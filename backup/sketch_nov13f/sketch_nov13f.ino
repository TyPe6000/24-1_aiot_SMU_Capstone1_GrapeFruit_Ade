#include <Servo.h>

// 서보 모터 설정
Servo myservo;
const int servoPin = 11;

// 센서 핀 설정
const int MSwitch = 4;
const int HallDIn = 7;
const int FSRPin1 = A3;
const int FSRPin2 = A2; // 두 번째 FSR 센서 핀

// 서보 모터 위치 상수
const int servoIDLE = 90;     // 모터 정지 위치
const int servoPull = 20;     // 모터 문 닫기 위치
const int servoRelease = 160; // 모터 케이블 풀기 위치

// 센서 임계값
const int FSRCrit = 120;
const int FSR2Crit = 950;

// 타이머 설정
const unsigned long duration = 1000;
const unsigned long Rduration = 3000; // 릴리스 대기 시간 조정

// 상태 변수
struct SystemState {
    bool MSVal;
    int HDVal;
    int FSRVal;
    int FSR2Val;          // 두 번째 FSR 값 변수
    bool GDCondition;
    bool Release;
    bool ReleaseComplete;
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
    state.ReleaseComplete = false;
    
    delay(500);
}

void updateSensors() {
    state.MSVal = digitalRead(MSwitch);
    state.HDVal = digitalRead(HallDIn);
    state.FSRVal = analogRead(FSRPin1);
    state.FSR2Val = analogRead(FSRPin2); // 두 번째 FSR 센서 값 업데이트
}

void moveServo() {
    if (state.desiredServoPos != myservo.read()) {
        myservo.write(state.desiredServoPos);
    }
}

// Force Stop 조건을 확인하고 처리하는 함수
void checkForceStop() {
    if (state.FSRVal > FSRCrit || state.FSR2Val > FSR2Crit) { // 두 FSR 중 하나라도 임계값 초과 시
        state.desiredServoPos = servoIDLE;  // 모터 정지
        moveServo();
        
        Serial.print("ALERT!!! Force Stop triggered due to high FSR value.\n");
        delay(3000);
        state.Release = true;
        state.ReleaseComplete = false;
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
    } else if (!state.GDCondition) { 
        state.desiredServoPos = servoIDLE;
    }
    moveServo();
}

void checkStopCondition() {
    if ((state.HDVal == 1 || state.MSVal == 0) && !(state.MSVal == 1 && state.HDVal == 1)) {
        state.desiredServoPos = servoIDLE;
        moveServo();
        state.GDCondition = false;

        state.Release = true;
        state.ReleaseComplete = false;
        state.RstartMillis = millis();
    }

    if (state.MSVal == 1 && state.HDVal == 1) {
        state.desiredServoPos = servoIDLE;
        state.GDCondition = false;
        state.Release = false;
        state.ReleaseComplete = false;
        moveServo();
    }
}

void handleRelease() {
    if (state.Release && !state.ReleaseComplete) {
        unsigned long elapsedTime = millis() - state.RstartMillis;
        
        if (elapsedTime <= Rduration) {
            state.desiredServoPos = servoRelease;
        } else {
            state.desiredServoPos = servoIDLE;
            state.Release = false;
            state.ReleaseComplete = true;
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
    Serial.print("  FSR2Val = ");
    Serial.print(state.FSR2Val);
    Serial.print("  Desired Servo Position = ");
    Serial.println(state.desiredServoPos);
}

void loop() {
    updateSensors();
    
    checkForceStop();
    
    if (!state.Release) { 
        checkGhostDoorCondition();
        checkStopCondition();
    }
    
    handleRelease();
    printDebugInfo();
}
