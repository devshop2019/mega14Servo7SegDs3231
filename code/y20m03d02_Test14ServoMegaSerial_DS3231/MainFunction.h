/*
    Kich ban:
    1/ Nguyen ly hoat dong:
        - bat dau ct se check Epprom xem servoInfo duoc set chua, neu chua se dung servoInfo khai bao mac dinh.
        - Dung Serial Commandline chon mode hoat dong: <RUNMODE,SETUP,> <HELP?>
            + Mode SETUP: setup Servo
                ++ Set onPos :      <SETONPOS,LED_ID,SEG_ID,value,>  ex: SETONPOS,0,4,90,  // set onPos cho Led 0(0~3), doan 4(1~7), goc 90(0~180)
                ++ Set offPos:      <SETOFFPOS,LED_ID,SEG_ID,value,>  ex: SETOFFPOS,0,4,70,  // set offPos choLed dau tien, doan 4, goc 70(0~180)
                ++ Set pin:         <SETPIN,LED_ID,SEG_ID,pinvalue,>
                ++ Save Epprom:     <SAVE_SERVO_INFO,>
                ++ Reset Epprom:     <RESET_SERVO_INFO,>
                ++ Print Servo info:<PRINT_INFO,>
                ++ Run test servo:  <RUN,LED_ID,SEG_ID,STATE,>         ex: RUN,0,4,1 hoặc RUN,0,4,0,  // chay Led thu 0(max 4), doan 4(1~7), len hoac xuong (1|0)
                ++ Set led value:   <SETLEDVALUE,LED_ID,NUMBER,>       // set so NUMBER(0-9) de led thu LED_ID(0~3) hien thi
                  
            + Mode TIME: Lay gio phut cua DS3231 de hien thi       <RUNMODE,TIME,>
            + Mode TEMP: Lay nhiet do cua DS3231 de hien thi       <RUNMODE,TEMP,>

    
*/
#ifndef _MAIN_FUNCTION_H_
#define _MAIN_FUNCTION_H_

#include "arduino.h"
#include "Servo7Seg.h"
#include "DebugManager.h"

extern String splitString2(String v_G_motherString, String v_G_Command, String v_G_Start_symbol, String v_G_Stop_symbol, unsigned char v_G_Offset);

#endif