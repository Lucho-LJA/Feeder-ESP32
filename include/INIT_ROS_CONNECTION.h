#ifndef _INIT_ROS_CONNECTION_H_
    #define _INIT_ROS_CONNECTION_H_
    #include <CONFIG.h>
    #include <ROS_CONFIG.h>
    #include "Arduino.h"
    #include <string>
    

    #ifdef ESP32_38P 
        // Set the connection to rosserial socket server
        nh.getHardware()->setConnection(server, serverPort);
            
        nh.initNode();
        //length to variables of publisher
        #ifdef FEEDER_2SENSOR_1MOTOR
            // Start publish
            nh.advertise(pDeviseSensor1);
            nh.advertise(pDeviseSensor2);
            nh.advertise(pDeviseState);

            //Start subscriptors
            nh.subscribe(sDeviseSetMotor);
            nh.subscribe(sDeviseState);
        #endif
        #ifdef FEEDER_LINEAL_CONVEYOR
            // Start publish
            nh.advertise(pDeviseState);

            //Start subscriptors
            nh.subscribe(sDeviseSetMotor);
            nh.subscribe(sDeviseState);
        #endif
    #endif    
    

    
    
#endif