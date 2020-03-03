#include "DebugManager.h"
#include <Servo.h>
#include "Servo7Seg.h"
#include "MainFunction.h"
#include "EepromManager.h"
#import "src/Communication/CommandLine.h"
#import "src/DS3231RTC/DS3232RTC.h"
// #import "src/Debug/ArduinoTrace.h"

DS3232RTC myRTC;

uint8_t count = 0;
unsigned long lastTestTimeInterval = 0;
bool runTestCount_Flag = false;
void runTestCount(){
  if(runTestCount_Flag){
    if(millis() - lastTestTimeInterval >= 1000){
      lastTestTimeInterval = millis();
      WriteLedWithNumber(2, count%10);
      WriteLedWithNumber(1, count/10);
      Serial.println(count);
      if(count <99)count++;
      else count = 0;
    }
  }
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  // ResetEeprom_ServoInfo();// Only use for the First time

  SetUpPinServo(currentLed7SegServo.servoInfo);
  
  //  myRTC.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  ReadSerial();
  runTestCount();
  // display();
}

void ReadSerial(){
  if(Serial.available()){
    String kk = Serial.readStringUntil('\n');
    Serial.println(kk);
    CheckCommand(kk, &Serial);

  }
}

unsigned long lastTimeDisplay = 0;
void display()
{
  if(millis() - lastTimeDisplay >= 1000){
    lastTimeDisplay = millis();
    char buf[40];
    time_t t = myRTC.get();
    float celsius = myRTC.temperature() / 4.0;
    float fahrenheit = celsius * 9.0 / 5.0 + 32.0;
    sprintf(buf, "%.2d:%.2d:%.2d %.2d%s%d ",
        hour(t), minute(t), second(t), day(t), monthShortStr(month(t)), year(t));
    Serial.print(buf);
    Serial.print(celsius);
    Serial.print("C ");
    Serial.print(fahrenheit);
    Serial.println("F");
  }
}