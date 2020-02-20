#include "Servo7Seg.h"

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
servoPinInfo servoInfo[MAX_NUM_7SEG][MAX_NUMSERVO7SEG] = {
  {
    //pin,onPos,offPos
    {2,90,180},//1
    {3,90,180},//2
    {4,90,180},//3
    {5,80,15},//4
    {6,90,175}, //5
    {7,90,180},//6
    {8,90, 0}//7
  },

  {
    {37,90,180},
    {39,90,180},
    {41,90,180},
    {43,90,180},
    {45,90,180},
    {47,90,180},
    {49,90,180}
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
