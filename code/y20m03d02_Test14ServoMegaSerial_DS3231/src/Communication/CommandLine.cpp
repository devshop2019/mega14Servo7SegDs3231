#include "CommandLine.h"
#include "../../EepromManager.h"
#include "../../MainFunction.h"
// #include "../../DebugManager.h"

const CommandLine_struct myCommand[] = {
    {"HELP", &showHelp, "HELP : show list command  222"},
    {COMMAND_CONTENT_SETONPOS, &SetUpOnPosOfSeg, COMMAND_CONTENT_SETONPOS",LED_ID,SEG_ID,ON_ANGLE_VALUE \t\t\tEX:"COMMAND_CONTENT_SETONPOS",1,7,180"},
    {COMMAND_CONTENT_SETOFFPOS, &SetUpOffPosOfSeg, COMMAND_CONTENT_SETOFFPOS",LED_ID,SEG_ID,OFF_ANGLE_VALUE \t\tEX:"COMMAND_CONTENT_SETOFFPOS",1,7,30"},
    {COMMAND_CONTENT_SETPIN, &SetUpPinOfSeg, COMMAND_CONTENT_SETPIN",LED_ID,SEG_ID,PIN_NUMBER \t\t\tEX:"COMMAND_CONTENT_SETPIN",1,7,10"},
    {COMMAND_CONTENT_SHOWLED, &ShowLed, COMMAND_CONTENT_SHOWLED",LED_ID,NUMBER_VALUE \t\t\t\tEX:"COMMAND_CONTENT_SHOWLED",1,7,9"},
    {COMMAND_SAVE_SERVO_INFO, &SaveServo_Info, COMMAND_SAVE_SERVO_INFO" : SAVE SERVO INFO"},
    {COMMAND_RESET_SERVO_INFO, &ResetServo_Info, COMMAND_RESET_SERVO_INFO" : RESET SERVO INFO"},
    {COMMAND_PRINT_SERVO_INFO, &PrintServo_Info, COMMAND_PRINT_SERVO_INFO" : PRINT SERVO INFO"},

    {COMMAND_NOTE, &showNote, COMMAND_NOTE" : Explain: <LED_ID>, <SEG_ID>,<ON_ANGLE_VALUE>,<OFF_ANGLE_VALUE>,<PIN_NUMBER>, <NUMBER_VALUE>"},
    {COMMAND_EN_RUNTESTCOUNT, &EnRunTestCount, COMMAND_EN_RUNTESTCOUNT" : LED7SERVO will show from 0 to 99"}
};

void showNote(String _ttstring_, int _idcommand_, Stream *p_printer___){
    p_printer___->println(F("--------------------NOTE-----------------------"));
    p_printer___->println(F("- <LED_ID> : led7seg 's posistion (from 1 to 6)"));
    p_printer___->println(F("-----------------------------------------------"));
    p_printer___->println(F("- <SEG_ID> : Segment 's posistion (from 1 to 7)"));
    p_printer___->println(F("              6"));
    p_printer___->println(F("          --------"));
    p_printer___->println(F("      1 /         / 5"));
    p_printer___->println(F("       /    7    /"));
    p_printer___->println(F("       ---------"));
    p_printer___->println(F("  2  /         / 4"));
    p_printer___->println(F("    /         /"));
    p_printer___->println(F("    ---------"));
    p_printer___->println(F("        3"));
    p_printer___->println(F("-----------------------------------------------"));
    p_printer___->println(F("- <ON_ANGLE_VALUE> : the angle of servo when the Segment is show (from 0 to 180)"));
    p_printer___->println(F("-----------------------------------------------"));
    p_printer___->println(F("- <OFF_ANGLE_VALUE> : the angle of servo when the Segment is hidden (from 0 to 180)"));
    p_printer___->println(F("-----------------------------------------------"));
    p_printer___->println(F("- <PIN_NUMBER> : the pin of servo to control the Segment (from 2 to 53)"));
    p_printer___->println(F("-----------------------------------------------"));
    p_printer___->println(F("- <NUMBER_VALUE> : the number which the Led7Seg will show (from 0 to 9), if <10> All Led7Seg 's Segment are HIDDEN"));
}

void showHelp(String _ttstring_, int _idcommand_, Stream *p_printer___){
    p_printer___->println(F("=========== HELP ============="));
    for(int ccm = 0; ccm < _END_COMMAND_ID_; ccm++){
        p_printer___->println(myCommand[ccm].note);
    }
    p_printer___->println(F("========= END HELP ==========="));
}

void SetUpOnPosOfSeg(String _ttstring_, int _idcommand_, Stream *p_printer___){
    int tempLedID = splitString2(_ttstring_, COMMAND_CONTENT_SETONPOS, ",", ",", 1).toInt();
    int tempSegID = splitString2(_ttstring_, COMMAND_CONTENT_SETONPOS, ",", ",", 2).toInt();
    int tempOnPos = splitString2(_ttstring_, COMMAND_CONTENT_SETONPOS, ",", "", 3).toInt();

    if(
        (tempLedID >0 && tempLedID <= MAX_NUM_7SEG) &&
        (tempSegID >0 && tempSegID <= MAX_NUMSERVO7SEG) &&
        (tempOnPos >=0 && tempOnPos <= 180)
    ){
        currentLed7SegServo.servoInfo[tempLedID - 1][tempSegID - 1].onPos = tempOnPos;
        mServo[tempLedID - 1][tempSegID - 1]->write(tempOnPos);
        p_printer___->print(F("LedID: ")); 
        p_printer___->print(tempLedID);
        p_printer___->print(F("\tSegID: "));
        p_printer___->print(tempSegID);
    }

    
    p_printer___->print(F("\tonPos: "));
    p_printer___->println(tempOnPos);

}

void SetUpOffPosOfSeg(String _ttstring_, int _idcommand_, Stream *p_printer___){
    int tempLedID = splitString2(_ttstring_, COMMAND_CONTENT_SETOFFPOS, ",", ",", 1).toInt();
    int tempSegID = splitString2(_ttstring_, COMMAND_CONTENT_SETOFFPOS, ",", ",", 2).toInt();
    int tempOffPos = splitString2(_ttstring_, COMMAND_CONTENT_SETOFFPOS, ",", "", 3).toInt();
    
    if(
        (tempLedID >0 && tempLedID <= MAX_NUM_7SEG) &&
        (tempSegID >0 && tempSegID <= MAX_NUMSERVO7SEG) &&
        (tempOffPos >= 0 && tempOffPos <= 180)
    ){
        currentLed7SegServo.servoInfo[tempLedID - 1][tempSegID - 1].offPos = tempOffPos;
        mServo[tempLedID - 1][tempSegID - 1]->write(tempOffPos);
        p_printer___->print(F("LedID: ")); 
        p_printer___->print(tempLedID);
        p_printer___->print(F("\tSegID: "));
        p_printer___->print(tempSegID);
    }

    p_printer___->print(F("\toffPos: "));
    p_printer___->println(tempOffPos);

}

void SetUpPinOfSeg(String _ttstring_, int _idcommand_, Stream *p_printer___){
    int tempLedID = splitString2(_ttstring_, COMMAND_CONTENT_SETPIN, ",", ",", 1).toInt();
    int tempSegID = splitString2(_ttstring_, COMMAND_CONTENT_SETPIN, ",", ",", 2).toInt();
    int tempPin = splitString2(_ttstring_, COMMAND_CONTENT_SETPIN, ",", "", 3).toInt();
    
    if(
        (tempLedID >0 && tempLedID <= MAX_NUM_7SEG) &&
        (tempSegID >0 && tempSegID <= MAX_NUMSERVO7SEG) &&
        (tempPin >= 2 && tempPin <= 53)
    ){
        currentLed7SegServo.servoInfo[tempLedID - 1][tempSegID - 1].pin = tempPin;
        mServo[tempLedID - 1][tempSegID - 1]->detach();
        mServo[tempLedID - 1][tempSegID - 1]->attach(tempPin);
        p_printer___->print(F("LedID: ")); 
        p_printer___->print(tempLedID);
        p_printer___->print(F("\tSegID: "));
        p_printer___->print(tempSegID);
    }

    p_printer___->print(F("\tPin: "));
    p_printer___->println(tempPin);

}

void ShowLed(String _ttstring_, int _idcommand_, Stream *p_printer___){
    int tempLedID = splitString2(_ttstring_, COMMAND_CONTENT_SHOWLED, ",", ",", 1).toInt();
    int tempNumber = splitString2(_ttstring_, COMMAND_CONTENT_SHOWLED, ",", "", 2).toInt();
    
    if(
        (tempLedID >0 && tempLedID <= MAX_NUM_7SEG) &&
        (tempNumber >=0 && tempNumber <= 10)
    ){
        WriteLedWithNumber(tempLedID, tempNumber);
        p_printer___->print(F("LedID: ")); 
        p_printer___->print(tempLedID);
    }
    
        p_printer___->print(F("\tNumber: "));
        p_printer___->println(tempNumber);
}

void SaveServo_Info(String _ttstring_, int _idcommand_, Stream *p_printer___){
    SaveEeprom_ServoInfo();
    p_printer___->println(F("Save eeprom Servo Info OK"));
}

void ResetServo_Info(String _ttstring_, int _idcommand_, Stream *p_printer___){
    ResetEeprom_ServoInfo();
    p_printer___->println(F("Reset eeprom Servo Info OK"));
}

void PrintServo_Info(String _ttstring_, int _idcommand_, Stream *p_printer___){
    PrintEeprom_ServoInfo(p_printer___);
    p_printer___->println(F("Print Servo Info done"));
}

void EnRunTestCount(String _ttstring_, int _idcommand_, Stream *p_printer___){
    runTestCount_Flag = !runTestCount_Flag;
}

void CheckCommand(String _commands_, Stream * p_printer___){
    for(int ccm = 0; ccm < _END_COMMAND_ID_; ccm++){
        String temStr = splitString2(_commands_, myCommand[ccm].commandString,",", ",",0);
        String temStr2 = splitString2(_commands_, myCommand[ccm].commandString,"\r", "",0);
        String temComandStr = myCommand[ccm].commandString;
        
        if((temStr == temComandStr) || (temStr2 == temComandStr)){
            if(myCommand[ccm].RunFunction) myCommand[ccm].RunFunction(_commands_, ccm, p_printer___);
            if((ccm == _COMMAND_ID_SET_ON_POS_) || (ccm == _COMMAND_ID_SET_OFF_POS_) ||
                (ccm == _COMMAND_ID_SET_PIN_) || (ccm == _COMMAND_ID_SHOW_LED_))
                runTestCount_Flag = false;
            break;
        }
    }
}