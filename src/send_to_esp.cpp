/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#include <Arduino.h>

#include "defines.h"
#include "comm_esp.h"
#include "structures.h"
#include "eprom.h"

void on_connect_bt();
void send_ana_values();

extern bool bt_connected;
extern bool wifi_connected;
extern bool ha_connected;
extern bool pauseSensorSends;

extern int temp_int_stp;
extern int hum_int_stp;
extern int soil_hum_stp;
extern int ph_irrig_stp;
extern int ph_hum_stp;
extern int light_hr_on_stp;
extern int light_min_on_stp;
extern int light_hr_off_stp;
extern int light_min_off_stp;
extern int pump_hr_irr_on_stp;
extern int pump_min_irr_on_stp;
extern int pump_hr_irr_off_stp;
extern int pump_min_irr_off_stp;
extern int irr_interval_stp;
extern int irr_1_hr_stp;
extern int irr_1_min_stp;
extern int irr_2_hr_stp;
extern int irr_2_min_stp;
extern int irr_3_hr_stp;
extern int irr_3_min_stp;
extern int irr_4_hr_stp;
extern int irr_4_min_stp;
extern int irr_5_hr_stp;
extern int irr_5_min_stp;
extern int irr_6_hr_stp;
extern int irr_6_min_stp;
extern int light_pwm_stp;
extern int fan1_inf_pwm_stp;
extern int fan2_inf_pwm_stp;
extern int fan3_inf_pwm_stp;

extern float eco2_ext;
extern float eco2_int;
extern float temp_ext;
extern float hum_ext;
extern float temp_ext;
extern float temp_int;
extern float hum_int;
extern float soil_1_hum;
extern float soil_2_hum;
extern float soil_3_hum;
extern float soil_4_hum;
extern float light_1_int;

extern bool water_irrig_1_level;
extern bool water_hum_1_level;

extern bool fan_dehum_on;
extern bool fan1_inf_on;
extern bool fan2_inf_on;
extern bool fan3_inf_on;
extern bool fan_dehumf_on;
extern bool fan_hum_on;
extern bool light_on;
extern bool pump_irr_on;
extern bool hum_1_on;
extern bool dehum_1_on;
extern bool relay_1_on;
extern bool relay_2_on;
extern bool relay_3_on;
extern bool relay_4_on;
extern bool output_1_on;
extern bool output_2_on;

extern bool soil_hum_dig;

extern bool door;
extern bool wifi_connected;
extern bool mqtt_connected;
extern bool bt_connected;

extern int fan_dehum_pwm;
extern int fan1_inf_pwm;
extern int fan2_inf_pwm;
extern int fan3_inf_pwm;
extern int fan_dehum_pwm;
extern int fan_hum_pwm;
extern int light_pwm;
extern int hum_1_pwm;
extern int dehum_1_pwm;

extern float VRef;
extern float intTemp;

extern String line;
extern String line1;
extern String line2;
extern String retMsg2[2];
extern String retMsg3[3];
extern String retMsg4[4];
extern String retMsg5[5];
extern String retMsg6[6];
extern String retMsg7[7];
extern String retMsg8[8];
extern String retMsg9[9];
extern String retMsg10[10];

extern var_grow var_grow_1[60];
extern var_grow var_grow_2[20];
extern var_grow var_grow_3[20];
extern var_grow var_grow_4[20];
extern var_grow var_grow_5[20];
extern var_grow var_grow_7[20];

void on_connect_bt(){
    String dest = "1";
    String svc1 = "1";
    String svc7 = "7";

    if (bt_connected){
        uint16_t addr;
        int data = 0;
        int service;
        int pid;
        String dataStr, svcStr, pidStr = "";

         delay(2500);

        for (int i = 0; i <= 52; i++){
            data=*var_grow_1[i].var_int;
            service=var_grow_1[i].service;
            pid=var_grow_1[i].pid;
            dataStr = String(*var_grow_1[i].var_int); 
            svcStr = String(var_grow_1[i].service);
            pidStr = String(var_grow_1[i].pid);
            send_esp_bt(dest,svcStr,pidStr,dataStr);
            delay(100);
        }

        for (int i = 0; i <= 12; i++){
            Serial.print("Schedule 7");
            Serial.println(i);
            addr = var_grow_7[i].eprom_address;
            svcStr = String(var_grow_7[i].service);
            pidStr = String(var_grow_7[i].pid);
            dataStr = read_String(addr);
            // Serial.println(dest+","+svcStr+","+pidStr+","+dataStr);
            send_esp_bt(dest,svcStr,pidStr,dataStr);
            delay(100);
        }  
    
    }
}

void send_ana_values(){
    // send_esp_bt(dest,svcStr,pidStr,dataStr);
    if (!pauseSensorSends){
        if ((bt_connected) || (wifi_connected)){
            uint16_t addr;
            int data = 0;
            int service;
            int pid;
            String dataStr, svcStr, pidStr = "";
            String dest = "1";
            for (int i = 0; i <= 10; i++){
                // Serial.print("Service 2");
                // Serial.println(i);
                dataStr = String(*var_grow_2[i].var_float);
                addr = var_grow_2[i].eprom_address;
                svcStr = String(var_grow_2[i].service);
                pidStr = String(var_grow_2[i].pid);
                // Serial.println(dest+","+svcStr+","+pidStr+","+dataStr);
                send_esp_bt(dest,svcStr,pidStr,dataStr);
                delay(100);
            }  

            for (int i = 0; i <= 6; i++){
                // Serial.print("Service 3");
                // Serial.println(i);
                if (*var_grow_3[i].var_bool){
                    dataStr = "1";
                }else{
                    dataStr = "0";    
                }
                
                addr = var_grow_3[i].eprom_address;
                svcStr = String(var_grow_3[i].service);
                pidStr = String(var_grow_3[i].pid);
                // Serial.println(dest+","+svcStr+","+pidStr+","+dataStr);
                send_esp_bt(dest,svcStr,pidStr,dataStr);
                delay(100);
            }  

            for (int i = 0; i <= 14; i++){
                // Serial.print("Service 4");
                // Serial.println(i);
                if (*var_grow_4[i].var_bool){
                    dataStr = "1";
                }else{
                    dataStr = "0";    
                }
                addr = var_grow_4[i].eprom_address;
                svcStr = String(var_grow_4[i].service);
                pidStr = String(var_grow_4[i].pid);
                // Serial.println(dest+","+svcStr+","+pidStr+","+dataStr);
                send_esp_bt(dest,svcStr,pidStr,dataStr);
                delay(100);
            } 

            for (int i = 0; i <= 4; i++){
                // Serial.print("Service 5");
                // Serial.println(i);
                dataStr = String(*var_grow_5[i].var_int);
                addr = var_grow_5[i].eprom_address;
                svcStr = String(var_grow_5[i].service);
                pidStr = String(var_grow_5[i].pid);
                // Serial.println(dest+","+svcStr+","+pidStr+","+dataStr);
                send_esp_bt(dest,svcStr,pidStr,dataStr);
                delay(100);
            }  
        }    
    }


}