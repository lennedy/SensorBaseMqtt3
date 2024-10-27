#ifndef STATUS_LED_H
#define STATUS_LED_H

#include <EspMQTTClient.h>

class StatusLed{
  private:
  bool ledEnabled;
  byte ledPin;

  void turnOnOff(bool on);

  public:
  inline const bool isEnabled(){return ledEnabled;}
  StatusLed();

  void init(byte pin);
  void blink();
  inline void off(){turnOnOff(false);}
  inline void on(){turnOnOff(true);}
};

#endif