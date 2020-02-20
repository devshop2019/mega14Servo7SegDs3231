#include <Servo.h>
#include "Servo7Seg.h"
#include "MainFunction.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  SetUpPinServo();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  ReadSerial();
  runTestCount();
  // WriteLedWithNumber(0,8);
  // WriteLedWithNumber(1,8);
  // delay(3000);
}

void ReadSerial(){
  if(Serial.available()){
    String kk = Serial.readStringUntil('\n');
    Serial.print(kk);
    Serial.print("\t");
    Serial.println(GET_VALUE_FROM_NUM(kk.toInt()), BIN);

    Serial.print(splitString2(kk,"ttrr",",",",",0) + "\t");
    Serial.print(splitString2(kk,"ttrr",",",",",1) + "\t");
    Serial.println(splitString2(kk,"ttrr",",",",",2) + "\t");

    // testServo7SegWithSegID(kk);
    WriteLedWithNumber(0,kk.toInt());
  }
}

void WriteLedWithNumber(uint8_t _ledId_, uint8_t _value_){
  uint8_t temValue = GET_VALUE_FROM_NUM(_value_);

  for(uint8_t cf = 0; cf < MAX_NUMSERVO7SEG; cf++){
    uint8_t temBit = bitRead(temValue,(MAX_NUMSERVO7SEG - 1) - cf);
    bool temFlag = false;

    if(temBit){
      mServo[_ledId_][cf]->write(servoInfo[_ledId_][cf].onPos);
    }else{
      mServo[_ledId_][cf]->write(servoInfo[_ledId_][cf].offPos);
    }
    servoInfo[_ledId_][cf].oldBit = temBit;
  }
}

uint8_t count = 0;
unsigned long lastTestTimeInterval = 0;
void runTestCount(){
  if(millis() - lastTestTimeInterval >= 1000){
    lastTestTimeInterval = millis();
    WriteLedWithNumber(0, count);
    if(count <10)count++;
    else count = 0;
  }
}

