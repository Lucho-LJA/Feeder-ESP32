#ifndef _ROS_CONFIG_
    #define _ROS_CONFIG_
    #include "CONFIG.h"
    #include "Arduino.h"
    #include "ros.h"
    #include "std_msgs/String.h"
    #include "std_msgs/Int8.h"
    #include "std_msgs/Int16.h"
    #include "std_msgs/Float32MultiArray.h"
    #include "std_msgs/Int32MultiArray.h"
    #include "std_msgs/Char.h"
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
    
#endif