#include "SensorBaseMqtt.h"

void SensorBaseMqtt::init(){

  led.init(LED_BUILTIN);
 // Optional functionalities of EspMQTTClient
  //client.enableMQTTPersistence();
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("TestClient/lastwill", "offline");  // You can activate the retain flag by setting the third parameter to true
  //client.setKeepAlive(8); 
  WiFi.mode(WIFI_STA);
}

void SensorBaseMqtt::availableSignal(){
  client.publish(topic_name + "/available", "online"); 
}

void SensorBaseMqtt::blinkLed(){
  static unsigned long ledWifiPrevTime = 0;
  static unsigned long ledMqttPrevTime = 0;
  unsigned long time_ms = millis();
  
  if( (WiFi.status() == WL_CONNECTED)){
    if(client.isMqttConnected()){
      if( (time_ms-ledMqttPrevTime) >= LED_INTERVAL_MQTT){
        led.blink();
        led2.blink();
        ledMqttPrevTime = time_ms;
      }      
    }
    else{
      led.on();
      led2.on();
    }
  }
  else{
    led.off();
    led2.off();
  }
}

void SensorBaseMqtt::loop(){
  unsigned long time_ms = millis();

  client.loop();

  if (time_ms - dataIntevalPrevTime >= DATA_INTERVAL) {
    //client.executeDelayed(1 * 100, metodoPublisher);  
    metodoPublisher();
    dataIntevalPrevTime = time_ms;
  }

  if (time_ms - availableIntevalPrevTime >= AVAILABLE_INTERVAL) {
    // client.executeDelayed(1 * 500, availableSignal);
    availableSignal();
    availableIntevalPrevTime = time_ms;
  }

  blinkLed();
}

void SensorBaseMqtt::enableSecondLed(byte pin){
  led2.init(pin);
}