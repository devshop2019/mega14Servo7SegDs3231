#ifndef _EEPROM_MANAGER_H_
#define _EEPROM_MANAGER_H_
#include "Servo7Seg.h"
#include "EEPROM.h"

#define SERVO_LED_INFO_ADDR         0

#define  _INFO_STATE_SAVE_          100
#define  _INFO_STATE_UNSAVE_        200

typedef struct servoLedEepromStruct{
  uint8_t saveState;
  servoPinInfo  servoInfo[MAX_NUM_7SEG][MAX_NUMSERVO7SEG];
  
};

extern servoLedEepromStruct currentLed7SegServo;
extern void ResetEeprom_ServoInfo();
extern void LoadEeprom_ServoInfo();
extern void SaveEeprom_ServoInfo();
extern void PrintEeprom_ServoInfo(Stream* _printer_);
#endif