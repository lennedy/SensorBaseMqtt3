#include "StatusLed.h"

StatusLed::StatusLed():ledEnabled(false){
}

void StatusLed::init(byte pin){
  ledPin=pin;
  ledEnabled=true;
  pinMode(ledPin, OUTPUT);
}

void StatusLed::blink(){
  if(ledEnabled){
    bool ledStatus = !digitalRead(ledPin);
    digitalWrite(ledPin, ledStatus);
  }
}

void StatusLed::turnOnOff(bool on){
  if(ledEnabled){
    digitalWrite(ledPin, on);
  }
}
