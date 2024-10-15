#include "SensorBaseMqtt.h"

void SensorBaseMqtt::init(){

  pinMode(LED_BUILTIN, OUTPUT);
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
  bool ledStatus = false;
  
  if( (WiFi.status() == WL_CONNECTED)){
    if(client.isMqttConnected()){
      if( (time_ms-ledMqttPrevTime) >= LED_INTERVAL_MQTT){
        ledStatus = !digitalRead(LED_BUILTIN);
        digitalWrite(LED_BUILTIN, ledStatus);
        ledMqttPrevTime = time_ms;
      }      
    }
    else{
      digitalWrite(LED_BUILTIN, LOW); //liga led
    }
  }
  else{
    digitalWrite(LED_BUILTIN, HIGH); //desliga led
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