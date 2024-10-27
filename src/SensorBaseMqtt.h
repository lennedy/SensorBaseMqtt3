#ifndef SENSOR_BASE_MQTT_H
#define SENSOR_BASE_MQTT_H

#include "Connect.h"
#include "StatusLed.h"
#include <ArduinoJson.h>

#define DATA_INTERVAL 1000       // Intervalo para adquirir novos dados do sensor (milisegundos).
                                 // Os dados serão publidados depois de serem adquiridos valores equivalentes a janela do filtro
#define AVAILABLE_INTERVAL 5000  // Intervalo para enviar sinais de available (milisegundos)
#define LED_INTERVAL_MQTT 1000        // Intervalo para piscar o LED quando conectado no broker

class SensorBaseMqtt{
  unsigned long dataIntevalPrevTime = 0;      // will store last time data was send
  unsigned long availableIntevalPrevTime = 0; // will store last time "available" was send
  StatusLed led2;
  StatusLed led;

public:
  void init();
  void availableSignal();
  void blinkLed();
  virtual void metodoPublisher()=0;

  void loop();
  void enableSecondLed(byte pin);
};

#endif