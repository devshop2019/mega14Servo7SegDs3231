#include "CommandLine.h"
#include "MainFunction.h"
#include "EepromManager.h"

const CommandLine_struct myCommand[] = {
    {"HELP", &showHelp, "show list command"},
    {COMMAND_CONTENT_SETONPOS, &SetUpOnPosOfSeg, COMMAND_CONTENT_SETONPOS",LED_ID,SEG_ID,value"},
    {COMMAND_CONTENT_SETOFFPOS, &SetUpOffPosOfSeg, COMMAND_CONTENT_SETOFFPOS",LED_ID,SEG_ID,value"},
    {COMMAND_CONTENT_SETPIN, &SetUpPinOfSeg, COMMAND_CONTENT_SETPIN",LED_ID,SEG_ID,PIN_NUMBER"},
    {COMMAND_SAVE_SERVO_INFO, &SaveServo_Info, COMMAND_SAVE_SERVO_INFO" : SAVE SERVO INFO"},
    {COMMAND_RESET_SERVO_INFO, &ResetServo_Info, COMMAND_RESET_SERVO_INFO" : RESET SERVO INFO"},
    {COMMAND_PRINT_SERVO_INFO, &PrintServo_Info, COMMAND_PRINT_SERVO_INFO" : PRINT SERVO INFO"},
    

    {"alo2", &showAlo, "Luu y 2"}
};

void showAlo(String _ttstring_, int _idcommand_, Stream *p_printer___){
    Serial.print("note: ");
    Serial.print(myCommand[_idcommand_].note);
    Serial.println("\tshow Alo " + _ttstring_);
}

void showHelp(String _ttstring_, int _idcommand_, Stream *p_printer___){
    p_printer___->println(F("========= HELP ==========="));
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
    int tempLedID = splitString2(_ttstring_, COMMAND_CONTENT_SETOFFPOS, ",", ",", 1).toInt();
    int tempSegID = splitString2(_ttstring_, COMMAND_CONTENT_SETOFFPOS, ",", ",", 2).toInt();
    int tempPin = splitString2(_ttstring_, COMMAND_CONTENT_SETOFFPOS, ",", "", 3).toInt();
    
    if(
        (tempLedID >0 && tempLedID <= MAX_NUM_7SEG) &&
        (tempSegID >0 && tempSegID <= MAX_NUMSERVO7SEG) &&
        (tempPin >= 0 && tempPin <= 180)
    ){
        currentLed7SegServo.servoInfo[tempLedID - 1][tempSegID - 1].offPos = tempPin;
        mServo[tempLedID - 1][tempSegID - 1]->write(tempPin);
        p_printer___->print(F("LedID: ")); 
        p_printer___->print(tempLedID);
        p_printer___->print(F("\tSegID: "));
        p_printer___->print(tempSegID);
    }

    p_printer___->print(F("\tPin: "));
    p_printer___->println(tempPin);

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

void CheckCommand(String _commands_){
    for(int ccm = 0; ccm < _END_COMMAND_ID_; ccm++){
        String temStr = splitString2(_commands_, myCommand[ccm].commandString,",", ",",0);
        String temStr2 = splitString2(_commands_, myCommand[ccm].commandString,"", "",0);
        String temComandStr = myCommand[ccm].commandString;
        if((temStr == temComandStr) || (temStr2 == temComandStr)){
            if(myCommand[ccm].RunFunction) myCommand[ccm].RunFunction(_commands_, ccm, &Serial);
            break;
        }
    }
}