#include "Servo7Seg.h"
#include "EepromManager.h"

const uint8_t tempalteServo7SegPosNumber[] = {
                                            0b1111110,//0
                                            0b0001100,//1
                                            0b0110111,//2
                                            0b0011111,//3
                                            0b1001101,//4
                                            0b1011011,//5
                                            0b1111011,//6
                                            0b0001110,//7
                                            0b1111111,//8
                                            0b1011111,//9
                                            0// Off all
                                        };

// const uint8_t tempalteServo7SegPosNumber[] = {
//                                             1,//0
//                                             2,//1
//                                             3,//2
//                                             4,//3
//                                             5,//4
//                                             6,//5
//                                             7,//6
//                                             8,//7
//                                             9,//8
//                                             10,//9
//                                             0// tat het
//                                         };

Servo *mServo[MAX_NUM_7SEG][MAX_NUMSERVO7SEG];
// servoPinInfo servoInfo[MAX_NUM_7SEG][MAX_NUMSERVO7SEG] = {
//   {
//     {23,90,0},
//     {25,90,0},
//     {27,90,0},
//     {29,90,0},
//     {31,90,0},
//     {33,90,0},
//     {35,90,0}
//   },

//   {
//     {37,90,0},
//     {39,90,0},
//     {41,90,0},
//     {43,90,0},
//     {45,90,0},
//     {47,90,0},
//     {49,90,0}
//   }
// };
#pragma region test servoInfo
const servoPinInfo servoInfo[MAX_NUM_7SEG][MAX_NUMSERVO7SEG] = {
  {
    //pin,onPos,offPos
    {2,90,180},//1
    {3,90,180},//2
    {4,90,180},//3
    {5,80,15},//4
    {6,90,175}, //5
    {7,90,180},//6
    {8,90, 180}//7
  },

  {
    {A0,90,180},//1
    {A1,90,180},//2
    {A2,90,0}, //3
    {A3,90,0}, //4
    {10,90,0}, //5
    {11,90,180},//6
    {12,90,0}//7
  }
};

#pragma endregion

void SetUpPinServo(){
    for(int cled = 0; cled < MAX_NUM_7SEG; cled++){
        for(uint8_t cf = 0; cf < MAX_NUMSERVO7SEG; cf++){
            if(mServo[cled][cf]) delete mServo[cf];
            mServo[cled][cf] = new Servo;
            mServo[cled][cf]->attach(servoInfo[cled][cf].pin);
        }
    }
}

void SetUpPinServo(servoPinInfo servoInfo_[MAX_NUM_7SEG][MAX_NUMSERVO7SEG]){
  LoadEeprom_ServoInfo();
  for(int cled = 0; cled < MAX_NUM_7SEG; cled++){
      for(uint8_t cf = 0; cf < MAX_NUMSERVO7SEG; cf++){
        if(servoInfo_[cled][cf].pin <=2) continue;
        if(servoInfo_[cled][cf].pin >=57) continue;
        if(mServo[cled][cf]) delete mServo[cf];
        mServo[cled][cf] = new Servo;
        int pintt = servoInfo_[cled][cf].pin;
        mServo[cled][cf]->attach(servoInfo_[cled][cf].pin);
        Serial.println(pintt);
      }
  }
}

void testServo7SegWithSegID(int _ledSegId_){
    for(int cled = 0; cled < MAX_NUM_7SEG; cled ++){
      for(uint8_t cf = 0; cf < MAX_NUMSERVO7SEG; cf++){
        if(cf != _ledSegId_){
          mServo[cled][cf]->write(90);
        }else{
          mServo[cled][cf]->write(0);
        }
      }
    }
}

void WriteLedWithNumber(uint8_t _ledId_, uint8_t _value_){
  uint8_t temValue = GET_VALUE_FROM_NUM(_value_);
  uint8_t temLedID = _ledId_ - 1;

  for(uint8_t cf = 0; cf < MAX_NUMSERVO7SEG; cf++){
    uint8_t temBit = bitRead(temValue,(MAX_NUMSERVO7SEG - 1) - cf);
    bool temFlag = false;

    if(temBit){
      mServo[temLedID][cf]->write(currentLed7SegServo.servoInfo[temLedID][cf].onPos);
    }else{
      mServo[temLedID][cf]->write(currentLed7SegServo.servoInfo[temLedID][cf].offPos);
    }
  }
}