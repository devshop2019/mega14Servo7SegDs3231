#ifndef _CommandLine_H_
#define _CommandLine_H_

#include "arduino.h"

#define COMMAND_CONTENT_SETONPOS        "SETONPOS"
#define COMMAND_CONTENT_SETOFFPOS       "SETOFFPOS"
#define COMMAND_CONTENT_SETPIN          "SETPIN"
#define COMMAND_CONTENT_SHOWLED         "SHOWLED"
#define COMMAND_SAVE_SERVO_INFO         "SAVESERVOINFO"

#define COMMAND_RESET_SERVO_INFO        "RESETSERVOINFO"
#define COMMAND_PRINT_SERVO_INFO        "PRINTSERVOINFO"

#define COMMAND_NOTE                    "NOTE"
#define COMMAND_EN_RUNTESTCOUNT         "RUNCOUNT"

enum{
    _COMMAND_ID_HELP,
    _COMMAND_ID_SET_ON_POS_,
    _COMMAND_ID_SET_OFF_POS_,
    _COMMAND_ID_SET_PIN_,
    _COMMAND_ID_SHOW_LED_,
    _COMMAND_ID_SAVE_SERVO_INFO_,
    _COMMAND_ID_RESET_SERVO_INFO_,
    _COMMAND_ID_PRINT_SERVO_INFO_,

    _COMMAND_ID_NOTE,
    _COMMAND_ID_EN_RUNTESTCOUNT,
    _END_COMMAND_ID_
}CommandID_Enum;

typedef void (*callback)(String, int, Stream *);

typedef struct CommandLine_struct{
    const char * commandString;
    callback RunFunction;
    const char* note;
};

extern const CommandLine_struct myCommand[];
extern void showNote(String _ttstring_, int _idcommand_, Stream *p_printer___);
extern void CheckCommand(String _commands_);
extern void CheckCommand(String _commands_, Stream * _serial__);
extern void showHelp(String _ttstring_, int _idcommand_, Stream *p_printer___);
extern void SetUpOnPosOfSeg(String _ttstring_, int _idcommand_, Stream *p_printer___);
extern void SetUpOffPosOfSeg(String _ttstring_, int _idcommand_, Stream *p_printer___);
extern void SetUpPinOfSeg(String _ttstring_, int _idcommand_, Stream *p_printer___);
extern void ShowLed(String _ttstring_, int _idcommand_, Stream *p_printer___);
extern void SaveServo_Info(String _ttstring_, int _idcommand_, Stream *p_printer___);
extern void ResetServo_Info(String _ttstring_, int _idcommand_, Stream *p_printer___);
extern void PrintServo_Info(String _ttstring_, int _idcommand_, Stream *p_printer___);

extern bool runTestCount_Flag;
extern void EnRunTestCount(String _ttstring_, int _idcommand_, Stream *p_printer___);
#endif