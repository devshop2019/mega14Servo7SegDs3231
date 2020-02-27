#include <Servo.h>
#include "Servo7Seg.h"
#include "MainFunction.h"
#include "EepromManager.h"
#include "CommandLine.h"

uint8_t count = 0;
unsigned long lastTestTimeInterval = 0;
bool runTestCount_Flag = false;
void runTestCount(){
  if(runTestCount_Flag){
    if(millis() - lastTestTimeInterval >= 1000){
      lastTestTimeInterval = millis();
      WriteLedWithNumber(2, count%10);
      WriteLedWithNumber(1, count/10);
      Serial.println(count);
      if(count <99)count++;
      else count = 0;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // ResetEeprom_ServoInfo();// Only use for the First time

  SetUpPinServo(currentLed7SegServo.servoInfo);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  ReadSerial();
  runTestCount();
}

void ReadSerial(){
  if(Serial.available()){
    String kk = Serial.readStringUntil('\n');
    Serial.println(kk);
    CheckCommand(kk, &Serial);

  }
}

