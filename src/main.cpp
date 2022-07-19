#include "CONFIG.h"
#include "ROS_CONFIG.h"
#include <string>
#include "Arduino.h"

#ifdef ESP32_38P
  #include <ESP32_AnalogWrite.h>
  #include <ESP32AnalogRead.h>
  #ifdef FEEDER_2SENSOR_1MOTOR
    #include "ESP32_L298N.h"
    L298N motorDevise(PWM_BITS, MOTOR_PWM, MOTOR_PIN1, MOTOR_PIN2);
  #endif
#endif


String ip_board=" ";
int auxBand = 0;

void setup()
{

  #ifndef _INIT_SERIAL_
    #define _INIT_SERIAL_
    #ifdef ESP32_38P
      Serial.begin(115200);
    #endif
  #endif
  #include "INIT_ESP32_CONNECTION.h"
  #include "INIT_ROS_CONNECTION.h"
  //config digitalPIN
  #ifdef FEEDER_2SENSOR_1MOTOR
    pinMode(SENSOR_1, INPUT);
    pinMode(SENSOR_2, INPUT);
    motorDevise.stopMotor();
  #endif
}


void loop()
{
  
  //Actions
  #ifdef FEEDER_2SENSOR_1MOTOR
    int sensor1_state = digitalRead(SENSOR_1);
    int sensor2_state = digitalRead(SENSOR_2);
    state_msg.data=stateDevise;
    if (sensor1_state==0){
      sensor1_msg.data = 0;
    }else{
      sensor1_msg.data = 1;
    }
    if (sensor2_state==0){
      sensor1_msg.data = 0;
    }else{
      sensor1_msg.data = 1;
    }
  #endif
  if (nh.connected()) {
    #ifdef FEEDER_2SENSOR_1MOTOR
      pDeviseSensor1.publish( &sensor1_msg );
      pDeviseSensor2.publish( &sensor2_msg);
      pDeviseState.publish( &state_msg);
      if (state_msg.data>0){
        if (state_msg.data == 1){
          if ((sensor1_state == 1 && auxBand== 0) || sensor1_state==0){
            motorDevise.moveMotor(VEL_PWM);
            if (auxBand==0){
              delay(DELAY_INIT_MOTOR);
              auxBand==1;
            }
          }else{
            motorDevise.stopMotor();
            state_msg.data = 0;
          }
        }else if (state_msg.data == 2){
          if (state_msg.data == 1){
          if ((sensor1_state == 1 && auxBand== 0) || sensor1_state==0){
            motorDevise.backMotor(VEL_PWM);
            if (auxBand==0){
              delay(DELAY_INIT_MOTOR);
              auxBand==1;
            }
          }else{
            motorDevise.stopMotor();
            state_msg.data = 0;
          }
        }else if (state_msg.data == 3 || state_msg.data == 4){
          if (sensor1_state == 1 && sensor2_state == 1 ){
            motorDevise.stopMotor();
            state_msg.data = 4;
          }else{
            motorDevise.moveMotor(VEL_PWM);
            state_msg.data = 3;
          }
        }
      }else{
        motorDevise.stopMotor();
      }
    #endif
          

  }else{
    Serial.println("Not Connected SERVER");
    #ifdef FEEDER_2SENSOR_1MOTOR
      motorDevise.stopMotor();
      state_msg.data=0;
    #endif
  }      
  nh.spinOnce();
  delay(DT_BOARD/10);
}
