#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  Serial.println("Start");
}

void loop() {
  if(Serial.available()){
    int kk = Serial.readStringUntil('\n').toInt();
    Serial.println(kk);
    myservo.write(kk);                  // sets the servo position according to the scaled value 
  }
}
