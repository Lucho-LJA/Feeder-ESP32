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
    #define DEVISE_NAME "feeder"
    #define ROUTER_SSID "NETLIFE"
    #define ROUTER_PASWORD "NOITA123"
    #define IP_ESP32 192,168,0,200    //Use <,> and not <.> 
    #define IP_GATEWAY 192,168,0,1    //Use <,> and not <.> 
    #define IP_SUBNET 255,255,255,0   //Use <,> and not <.> 
    #define ROS_SERVER 192,168,0,197   //Use <,> and not <.> 
    #define ROS_SERVER_PORT 11420

    /*
        DEVISE CONFIGURATION
        Uncomment the option
            FEEDER_2SENSOR_1MOTOR : Feeder with motor that turn to move a element. It have
                                    2 sensor ON/OFF to detec piece and control the turn.
                                    Feeder use one motor DC with control driver.
    */
    #define FEEDER_2SENSOR_1MOTOR
    /*
        SELECT BOARD DEVELOPMENT
        Uncomment the type of board
        ESP32_38P : ESP32 with 38 pins and standar configuration OF 10 bits
    */
    #define ESP32_38P
    /*
        Define the default velocity PWM-10BITS (0-1024)
        Define PINS
    */

    #ifdef ESP32_38P
        #define VEL_PWM 1023
        #ifdef FEEDER_2SENSOR_1MOTOR
            #define SENSOR_1 4
            #define SENSOR_2 15
            #define MOTOR_PWM 14
        #endif
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