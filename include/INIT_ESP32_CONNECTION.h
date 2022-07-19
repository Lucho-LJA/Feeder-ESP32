#ifndef _INIT_ESP32_CONNECTION_H_
    #define _INIT_ESP32_CONNECTION_H_
    #include <CONFIG.h>
    #include <ROS_CONFIG.h>
    #include "Arduino.h"
    #include <string>
    

   #ifdef ESP32_38P
    WiFi.mode(WIFI_STA);
    WiFi.config(ip,gateway,subnet);
    WiFi.begin(ssid, password);
      while (WiFi.status() != WL_CONNECTED){
        Serial.println("Connecting...");
        delay(500);
      }
      ip_board=String(WiFi.localIP());
      Serial.println(WiFi.localIP());
  #endif    
#endif