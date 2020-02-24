#include <Servo.h>
#include "Servo7Seg.h"
#include "MainFunction.h"
#include "EepromManager.h"
#include "CommandLine.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  LoadEeprom_ServoInfo();

  SetUpPinServo(currentLed7SegServo.servoInfo);

  PrintEeprom_ServoInfo(&Serial);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  ReadSerial();
  // runTestCount();
  // WriteLedWithNumber(0,8);
  // WriteLedWithNumber(1,8);
  // delay(3000);
}

void ReadSerial(){
  if(Serial.available()){
    String kk = Serial.readStringUntil('\n');
    Serial.println(kk);
    // Serial.print("\t");
    // Serial.println(GET_VALUE_FROM_NUM(kk.toInt()), BIN);

    // Serial.print(splitString2(kk,"ttrr",",",",",0) + "\t");
    // Serial.print(splitString2(kk,"ttrr",",",",",1) + "\t");
    // Serial.println(splitString2(kk,"ttrr",",","",2) + "\t");

    CheckCommand(kk);

    // testServo7SegWithSegID(kk);
    // WriteLedWithNumber(1,kk.toInt());
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
  }
}

uint8_t count = 0;
unsigned long lastTestTimeInterval = 0;
void runTestCount(){
  if(millis() - lastTestTimeInterval >= 1000){
    lastTestTimeInterval = millis();
    WriteLedWithNumber(1, count%10);
    WriteLedWithNumber(0, count/10);
    if(count <99)count++;
    else count = 0;
  }
}

