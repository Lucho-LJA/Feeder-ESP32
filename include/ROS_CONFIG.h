#ifndef _ROS_CONFIG_
    #define _ROS_CONFIG_
    #include "CONFIG.h"
    #include "Arduino.h"
    #include "ros.h"
    #include "std_msgs/Int8.h"
    #include "std_msgs/Int16.h"
    #include <string>

    const char* ssid     = ROUTER_SSID;
    const char* password = ROUTER_PASWORD;
    //Set the IP's configuration
    IPAddress ip(IP_ESP32);
    IPAddress gateway(IP_GATEWAY);
    IPAddress subnet(IP_SUBNET);

    // Set the rosserial socket server IP address
    IPAddress server(ROS_SERVER);
    // Set the rosserial socket server port
    const uint16_t serverPort = ROS_SERVER_PORT;

    ros::NodeHandle nh;
    //name to devise
    String name_robot = DEVISE_NAME;
    #ifdef FEEDER_2SENSOR_1MOTOR
        // VARIABLES TO TOPICS
        String pSensor1=name_robot+"/get_sensor_turn";
        String pSensor2=name_robot+"/get_sensor_piece";
        String pState=name_robot+"/get_state";
        String sState=name_robot+"/set_state";
        String sVel=name_robot+"/set_vel";
        

        //FUNCTIONS TO SYBSCRIPTORS
        void ReadSetPoint( const std_msgs::Int16& msg){
            setMotor= msg.data;
        }
        void ReadState( const std_msgs::Int8& msg){
            stateDevise= msg.data;
        }
        

        //MAKE VARIABLES TO PUBLISHERS
        std_msgs::Int8 sensor1_msg;
        std_msgs::Int8 sensor2_msg;
        std_msgs::Int8 state_msg;

        //BUILD PUBLISHER
        ros::Publisher pDeviseSensor1(pSensor1.c_str(), &sensor1_msg);
        ros::Publisher pDeviseSensor2(pSensor2.c_str(), &sensor2_msg);
        ros::Publisher pDeviseState(pState.c_str(), &state_msg);

        //BUILD SUBSCRIPTORS
        ros::Subscriber<std_msgs::Int16> sDeviseSetMotor(sVel.c_str(),&ReadSetPoint);
        ros::Subscriber<std_msgs::Int8> sDeviseState(sState.c_str(),&ReadState);

    #endif
    #ifdef FEEDER_LINEAL_CONVEYOR
        // VARIABLES TO TOPICS
        String pState=name_robot+"/get_state";
        String sState=name_robot+"/set_state";
        String sVel=name_robot+"/set_vel";
        

        //FUNCTIONS TO SYBSCRIPTORS
        void ReadSetPoint( const std_msgs::Int16& msg){
            setMotor= msg.data;
        }
        void ReadState( const std_msgs::Int8& msg){
            stateDevise= msg.data;
        }
        

        //MAKE VARIABLES TO PUBLISHERS
        std_msgs::Int8 stop_msg;
        std_msgs::Int8 state_msg;

        //BUILD PUBLISHER
        ros::Publisher pDeviseState(pState.c_str(), &state_msg);

        //BUILD SUBSCRIPTORS
        ros::Subscriber<std_msgs::Int16> sDeviseSetMotor(sVel.c_str(),&ReadSetPoint);
        ros::Subscriber<std_msgs::Int8> sDeviseState(sState.c_str(),&ReadState);

    #endif
    
#endif