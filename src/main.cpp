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
  #ifdef FEEDER_LINEAL_CONVEYOR
    #include "ESP32_L298N.h"
    L298N motorDevise(PWM_BITS, MOTOR_PWM, MOTOR_PIN1, MOTOR_PIN2);
  #endif
#endif


String ip_board=" ";
int auxBand = 0;
//Function to interupter
#ifdef FEEDER_2SENSOR_1MOTOR
  int sensor1_state = 0;
  void IRAM_ATTR isr() {
    if (sensor1_state == 0){
      sensor1_state =1;
    }
  }
#endif
void setup()
{
  #include "INIT_ESP32_CONNECTION.h"
  #include "INIT_ROS_CONNECTION.h"
  //config digitalPIN
  #ifdef FEEDER_2SENSOR_1MOTOR
    pinMode(SENSOR_1, INPUT_PULLUP);
    attachInterrupt(SENSOR_1, isr, FALLING);
    pinMode(SENSOR_2, INPUT);
    motorDevise.stopMotor();
  #endif
  #ifdef FEEDER_LINEAL_CONVEYOR
    pinMode(STOP_EMERG, INPUT);
    motorDevise.stopMotor();
  #endif
}


void loop(){
  //Actions
  #ifdef FEEDER_2SENSOR_1MOTOR
    int sensor2_state = digitalRead(SENSOR_2);
    state_msg.data=stateDevise;
    if (digitalRead(SENSOR_1)==0){
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
  #ifdef FEEDER_LINEAL_CONVEYOR
    int stop_button = digitalRead(STOP_EMERG);
    if (stop_button==1){
      state_msg.data = 3;
    }else{
      state_msg.data=stateDevise;
    }
  #endif
  if (nh.connected()){
    #ifdef FEEDER_2SENSOR_1MOTOR
      pDeviseSensor1.publish( &sensor1_msg );
      pDeviseSensor2.publish( &sensor2_msg);
      pDeviseState.publish( &state_msg);
      if (state_msg.data>0){
        if (state_msg.data == 1){
          if (sensor1_state==0){
            motorDevise.moveMotor(VEL_PWM);
          }else{
            motorDevise.stopMotor();
            state_msg.data = 0;
            sensor1_state=0;
          }
        }else if (state_msg.data == 2){
            if (sensor1_state==0){
              motorDevise.backMotor(VEL_PWM);
            }else{
              motorDevise.stopMotor();
              state_msg.data = 0;
              sensor1_state=0;
            }
        }else if (state_msg.data == 3 || state_msg.data == 4){
          if (sensor1_state==0 && state_msg.data == 3){
            motorDevise.stopMotor();
          }
          if (sensor1_state==1 && state_msg.data == 3 && sensor2_state == 1){
            motorDevise.stopMotor();
            state_msg.data = 4;
          }
          if (sensor1_state == 1 && state_msg.data == 3 && sensor2_state == 0 ){
            sensor1_state == 0;
            state_msg.data = 3;
          }
        }
      }else{
        motorDevise.stopMotor();
      }
    #endif

    #ifdef FEEDER_LINEAL_CONVEYOR
      pDeviseState.publish( &state_msg);
      if (state_msg.data>0 && state_msg.data != 3){
        if (state_msg.data == 1){
          motorDevise.moveMotor(VEL_PWM);
        }else if (state_msg.data == 2){
          motorDevise.backMotor(VEL_PWM);
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
    #ifdef FEEDER_LINEAL_CONVEYOR
      motorDevise.stopMotor();
      state_msg.data=0;
    #endif
  }      
  nh.spinOnce();
  delay(DT_BOARD/10);
}
