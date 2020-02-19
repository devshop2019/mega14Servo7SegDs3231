#include <Servo.h>
#include "Servo7Seg.h"

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  SetUpPinServo();
  
}

void loop() {
  // put your main code here, to run repeatedly:
  ReadSerial();
  // WriteLedWithNumber(0,8);
  // WriteLedWithNumber(1,8);
  // delay(3000);
}

void ReadSerial(){
  if(Serial.available()){
    int kk = Serial.readStringUntil('\n').toInt();
    Serial.print(kk);
    Serial.print("\t");
    Serial.println(GET_VALUE_FROM_NUM(kk), BIN);

    // testServo7SegWithSegID(kk);
    WriteLedWithNumber(0,kk);
  }
}

void WriteLedWithNumber(uint8_t _ledId_, uint8_t _value_){
  uint8_t temValue = GET_VALUE_FROM_NUM(_value_);

  for(uint8_t cf = 0; cf < MAX_NUMSERVO7SEG; cf++){
    uint8_t temBit = bitRead(temValue,(MAX_NUMSERVO7SEG - 1) - cf);
    if(temBit){
      mServo[_ledId_][cf]->write(servoInfo[_ledId_][cf].onPos);
    }else{
      mServo[_ledId_][cf]->write(servoInfo[_ledId_][cf].offPos);
    }
  }
}