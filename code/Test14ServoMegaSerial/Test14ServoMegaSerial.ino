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
  runTestCount();
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

// void checkSeg(uint8_t cf, int _deltaAngle_){
//   for(int _ledId_ = 0; _ledId_ < MAX_NUM_7SEG; _ledId_++){
//     if(cf == MID_SEG_SERVO_ID_7){
//       if(servoInfo[_ledId_][MID_SEG_SERVO_ID_1].oldBit){
//         mServo[_ledId_][MID_SEG_SERVO_ID_1]->write(servoInfo[_ledId_][MID_SEG_SERVO_ID_1].onPos - _deltaAngle_);
//         temFlag = true;
//       }
//       if(servoInfo[_ledId_][MID_SEG_SERVO_ID_5].oldBit){
//         mServo[_ledId_][MID_SEG_SERVO_ID_5]->write(servoInfo[_ledId_][MID_SEG_SERVO_ID_5].onPos + _deltaAngle_);
//         temFlag = true;
//       }
      
//       if(temFlag)delay(50);
//     }
//   }
  
// }

void WriteLedWithNumber(uint8_t _ledId_, uint8_t _value_){
  uint8_t temValue = GET_VALUE_FROM_NUM(_value_);

  for(uint8_t cf = 0; cf < MAX_NUMSERVO7SEG; cf++){
    uint8_t temBit = bitRead(temValue,(MAX_NUMSERVO7SEG - 1) - cf);
    bool temFlag = false;

    // if(cf == MID_SEG_SERVO_ID_7){
    //   if(servoInfo[_ledId_][MID_SEG_SERVO_ID_1].oldBit){
    //     mServo[_ledId_][MID_SEG_SERVO_ID_1]->write(servoInfo[_ledId_][MID_SEG_SERVO_ID_1].onPos - MID_SEG_MOVE_POS);
    //     temFlag = true;
    //   }
    //   if(servoInfo[_ledId_][MID_SEG_SERVO_ID_5].oldBit){
    //     mServo[_ledId_][MID_SEG_SERVO_ID_5]->write(servoInfo[_ledId_][MID_SEG_SERVO_ID_5].onPos + MID_SEG_MOVE_POS);
    //     temFlag = true;
    //   }
      
    //   if(temFlag)delay(50);
    // }
    // checkSeg(cf, MID_SEG_MOVE_POS);

    if(temBit){
      mServo[_ledId_][cf]->write(servoInfo[_ledId_][cf].onPos);
    }else{
      mServo[_ledId_][cf]->write(servoInfo[_ledId_][cf].offPos);
    }
    servoInfo[_ledId_][cf].oldBit = temBit;

    // checkSeg(cf, 0);
    
  }
}

uint8_t count = 0;
void runTestCount(){
  WriteLedWithNumber(0, count);
  if(count <10)count++;
  else count = 0;
  delay(1000);
}