#include "CONFIG.h"
#include "ROS_CONFIG.h"
#include <string>

#ifdef PID_CONTROL
  #include "PID_CONTROL.h"
#endif

#ifdef ON_OFF_CONTROL
  #include "ON_OFF_CONTROL.h"
#endif

#ifdef ESP32_38P
  #include <ESP32_AnalogWrite.h>
  #include <ESP32AnalogRead.h>
  
#endif



String ip_board=" ";

unsigned long prev_time_board=0;
unsigned long time_board=0;

void setup()
{

  #ifndef _INIT_SERIAL_
    #define _INIT_SERIAL_
    #ifdef ESP32_38P
      Serial.begin(115200);
    #endif
  #endif
  #ifdef ESP32_38P
    WiFi.mode(WIFI_STA);
    WiFi.config(ip,gateway,subnet);
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) 
    {
      Serial.println("Connecting...");
      delay(500);
    }
    ip_board=String(WiFi.localIP());
    Serial.println(WiFi.localIP()); 
    
    // Set the connection to rosserial socket server
    nh.getHardware()->setConnection(server, serverPort);
        
    nh.initNode();
    //length to variables of publisher




    // Start publish
    

    //Start subscriptors
   
    

    
    //Init time to sample
    prev_time_board =millis();

  #endif
}


void loop()
{
  #ifdef ESP32_38P
    time_board = millis();
    if(time_board-prev_time_board>=DT_BOARD)
    {
      prev_time_board=time_board;
      

    }
      if (nh.connected()) 
        {
        
          

        } else {
          Serial.println("Not Connected SERVER");

        }
        //Actions
        

        
        nh.spinOnce();
        delay(DT_BOARD/10);
   #endif
}
