#include "Adafruit_VL53L0X.h"
#include <Servo.h>

Servo myservo;
Adafruit_VL53L0X lox = Adafruit_VL53L0X();
//int pushButton=4;

void setup() {
  myservo.attach(9);
  Serial.begin(115200);
  //pinMode(pushbutton,INPUT);
  // wait until serial port opens for native USB devices
  while (! Serial) {
    delay(1);
  }
  
  Serial.println("Adafruit VL53L0X test");
  if (!lox.begin()) {
    Serial.println(F("Failed to boot VL53L0X"));
    while(1);
  }
  // power 
  Serial.println(F("VL53L0X API Simple Ranging example\n\n")); 
}


void loop() {
  //int buttonState = digitalRead(pushButton);
  VL53L0X_RangingMeasurementData_t measure;
    
  Serial.print("Reading a measurement... ");
  lox.rangingTest(&measure, false); // pass in 'true' to get debug data printout!

  if (measure.RangeStatus != 4) {  // phase failures have incorrect data
    Serial.print("Distance (mm): "); Serial.println(measure.RangeMilliMeter);
  } else {
    Serial.println(" out of range ");
  }

  if (measure.RangeMilliMeter>100){
    myservo.write(30);
  }else{
    myservo.write(150);
  }
  

  delay(50);
}