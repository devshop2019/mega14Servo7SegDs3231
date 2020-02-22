#ifndef _Servo7Seg_H_
#define _Servo7Seg_H_
#include "arduino.h"
#include <Servo.h>

#define MAX_NUM_7SEG          4

#define MAX_NUMSERVO7SEG      7

#define MID_SEG_SERVO_ID_7    (6)
#define MID_SEG_SERVO_ID_1    (0)
#define MID_SEG_SERVO_ID_5    (4)
#define MID_SEG_MOVE_POS      (15)

/*
              6
          --------
      1 /         / 5
       /    7    /
        --------
  2 /         / 4
   /         /
   --------
        3
*/
extern const uint8_t tempalteServo7SegPosNumber[];

#define SERVO7SEG_NUM_0             10
#define SERVO7SEG_NUM_1             0
#define SERVO7SEG_NUM_2             1
#define SERVO7SEG_NUM_3             2
#define SERVO7SEG_NUM_4             3
#define SERVO7SEG_NUM_5             4
#define SERVO7SEG_NUM_6             5
#define SERVO7SEG_NUM_7             6
#define SERVO7SEG_NUM_8             7
#define SERVO7SEG_NUM_9             8

#define GET_VALUE_FROM_NUM(x)       tempalteServo7SegPosNumber[x]
#define SET_LED7SEG(LEDID, VALUE)   

typedef struct{
    uint8_t                     pin;
    uint8_t                     onPos;
    uint8_t                     offPos;
    uint8_t                     oldBit;
}servoPinInfo;

extern Servo *mServo[MAX_NUM_7SEG][MAX_NUMSERVO7SEG];
extern const servoPinInfo servoInfo[MAX_NUM_7SEG][MAX_NUMSERVO7SEG];

extern void SetUpPinServo();
void SetUpPinServo(servoPinInfo servoInfo_[MAX_NUM_7SEG][MAX_NUMSERVO7SEG]);
extern void testServo7SegWithSegID(int _ledSegId_);

#endif