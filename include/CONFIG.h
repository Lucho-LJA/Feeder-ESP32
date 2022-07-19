#ifndef _CONFIG_H_
    #define _CONFIG_H_
    #include <Arduino.h>
    #include <string>
    
    //================DEFAULT CONFIGURATION=============================
    /*
        ROS CONFIGURATION - COMUNICATION
        ROBOT_NAME : name of robot to node (It must unique)
        ROUTER_SSID : SSID of router (Iqual as you see when scan a WiFi)
        ROUTER_PASSWORD : PASWORD in plain text
        IP_ESP32 : IP static (you should config a MAC in your Router)
        IP_GATEWAY : GETWAY of ROUTER
        IP_SUBNET : SUBNET (The same of router configuration)
        ROS_SERVER  : IP of machine where run roscore (server)
        ROS_SERVER_PORT : PORT where run ROS_SERVER (It is configured at ROS_SERVER package)
    */
    #define ROBOT_NAME "scara1"
    #define ROUTER_SSID "NETLIFE"
    #define ROUTER_PASWORD "NOITA123"
    #define IP_ESP32 192,168,0,200    //Use <,> and not <.> 
    #define IP_GATEWAY 192,168,0,1    //Use <,> and not <.> 
    #define IP_SUBNET 255,255,255,0   //Use <,> and not <.> 
    #define ROS_SERVER 192,168,0,197   //Use <,> and not <.> 
    #define ROS_SERVER_PORT 11411

    /*
        SELECT BOARD DEVELOPMENT
        Uncomment the type of board
        ESP32_38P : ESP32 with 38 pins and standar configuration OF 10 bits
    */
    #define ESP32_38P
    /*
        Define the default velocity PWM-10BITS (0-1024)
        Define the defult POSITION ANGLE
        Define max and min angle
        Define pins of board
    */
    



    #ifdef ESP32_38P

    #endif
    
    
    /*
        INPUT YOUR CONTROL PARAMETRES
        Uncomment the type of control that you want and configure it
    */
    #define DT_BOARD 100 
    


    //================CONFIGURATION FOLLOWING YOUR SELECTION=============================
    // EMERGENCI STOP
    int EmStop = 0;
    //BOARDS
    #ifdef ESP32_38P
        // PWM Resolution of the microcontroller
        #define PWM_BITS 10                
        int PWM_MAX=pow(2, PWM_BITS) - 1;
        #define PWM_MIN 0
       // #define CORE_NUM_INTERRUPT 32
    #endif


#endif