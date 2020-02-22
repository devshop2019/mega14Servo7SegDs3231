#include "EepromManager.h"

servoLedEepromStruct myLed7Seg, myLed7Seg2, currentLed7SegServo;

void ResetEeprom_ServoInfo(){
    servoLedEepromStruct temLed;
    EEPROM.get(SERVO_LED_INFO_ADDR, temLed);
    temLed.saveState = _INFO_STATE_UNSAVE_;
    EEPROM.put(SERVO_LED_INFO_ADDR, temLed);
}

void LoadEeprom_ServoInfo(){
    // myLed7Seg2.saveState = _INFO_STATE_UNSAVE_;
    // memcpy(&myLed7Seg2.servoInfo, &servoInfo, sizeof(servoInfo));
    // EEPROM.put(SERVO_LED_INFO_ADDR, myLed7Seg2);

    // get data Servo from Eeprom
    EEPROM.get(SERVO_LED_INFO_ADDR, currentLed7SegServo);
    if(currentLed7SegServo.saveState == _INFO_STATE_UNSAVE_){
        memcpy(&currentLed7SegServo.servoInfo, &servoInfo, sizeof(servoInfo));
    }else;

    

    Serial.print("data Size: " + String(sizeof(servoInfo)));
    Serial.print(" Eep state s: " + String(myLed7Seg2.saveState));
    Serial.print(" Eep state d: " + String(currentLed7SegServo.saveState));
    Serial.print(" Eep data s: " + String(servoInfo[0][6].pin));
    Serial.println(" Eep data d: " + String(currentLed7SegServo.servoInfo[0][6].pin));
}

void SaveEeprom_ServoInfo(){
    currentLed7SegServo.saveState = _INFO_STATE_SAVE_;
    EEPROM.put(SERVO_LED_INFO_ADDR, currentLed7SegServo);
}

void PrintEeprom_ServoInfo(Stream* _printer_){
    servoLedEepromStruct temLed;
    EEPROM.get(SERVO_LED_INFO_ADDR, temLed);
    _printer_->println(F("const servoPinInfo servoInfo[MAX_NUM_7SEG][MAX_NUMSERVO7SEG] = {"));
    for(int cled = 0; cled < MAX_NUM_7SEG; cled++){
        _printer_->print(F("\t{\t//LedID "));
        _printer_->println(cled);
        _printer_->println(F("\t\t//pin\t\tonPos\t\toffPos"));
        // _printer_->println(cled);
        for(uint8_t cf = 0; cf < MAX_NUMSERVO7SEG; cf++){
            _printer_->print(F("\t\t"));
            _printer_->print(F("{"));
            _printer_->print(temLed.servoInfo[cled][cf].pin);
            _printer_->print(F(",\t\t"));
            _printer_->print(temLed.servoInfo[cled][cf].onPos);
            _printer_->print(F(",\t\t"));
            _printer_->print(temLed.servoInfo[cled][cf].offPos);
            if(cf < (MAX_NUMSERVO7SEG - 1)) _printer_->print(F("\t},\t\t// Seg_Id: "));
            else _printer_->print(F("\t}\t\t// Seg_Id: "));
            _printer_->println(cf + 1);
        }
        _printer_->print(F("\t}"));
        if(cled == (MAX_NUM_7SEG - 1)) _printer_->println();
        else _printer_->println(F(","));
    }
    _printer_->print(F("};"));
}