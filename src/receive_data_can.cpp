/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#include <Arduino.h>
#include <SPI.h>
#include "STM32_CAN.h"

#include "defines.h"
#include "io_defines.h"
#include "can_control.h"
#include "display.h"

#include "structures.h"
#include "service_01.h"
#include "service_02.h"
#include "service_03.h"
#include "service_04.h"
#include "service_05.h"
#include "service_06.h"
#include "service_07.h"

void receive_can(int rxId, int service,  byte rec_data[8]);
// void service_0x01_can(byte rec_data[8]);
// void service_0x02_can(byte rec_data[8]);
// void service_0x03_can(byte rec_data[8]);
// void service_0x04_can(byte rec_data[8]);
// void service_0x05_can(byte rec_data[8]); 
// void service_0x06_can(byte rec_data[8]); 


// long unsigned int rxId;
// unsigned char len = 0;
// unsigned char rxBuf[8];
// char msgString[128];   
// byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};  

extern byte minutes;
extern byte hours; 
extern byte weekDay;
extern byte day;
extern byte month;
extern byte year;

extern bool first_run;

extern int language;

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


extern bool ch_page;
extern bool ch_page_ana;
extern int tft_page;
extern int tft_page_ant;
extern int tft_sub_page;
extern int tft_sub_page_ant;
extern int draw_tab;
extern int draw_page;


extern var_grow var_grow_1[20];
extern var_grow var_grow_2[20];
extern var_grow var_grow_3[20];
extern var_grow var_grow_4[20];
extern var_grow var_grow_5[20];
extern var_grow var_grow_6[20];
extern var_grow var_grow_7[30];



void receive_can(int rxId, int service,  byte rec_data[8]){
    Serial.println("receive can");

    // switch (service)
    // {
    //     case 0x01:
    //         on_service_1(rxId, rec_data);;
    //         break;
    //     case 0x02:
    //         // Serial.println("service 2 CAN");
    //         on_service_0x02_can(rxId, rec_data);;
    //         break;
    //     case 0x03:
    //         // Serial.println("service 3");
    //         on_service_0x03_can(rxId,rec_data);
    //         break;    
    //     case 0x04:
    //         // Serial.println("service 4 can");
    //         on_service_0x04_can(rxId,rec_data);
    //         break;   
    //     case 0x05:
    //         on_service_0x05_can(rxId,rec_data);
    //         break;    
    //     case 0x06:
    //         // Serial.println("service 6");
    //         on_service_0x06_can(rxId, rec_data);
    //         break;       
    //     case 0x07:
    //         // Serial.println("service 7");
    //         on_service_0x07_can(rxId, rec_data);
    //         break;    
    //     case 0x0A:
    //         Serial.print("LifeBit: ");
    //         Serial.print(rxId, HEX);
    //         Serial.print(", ");
    //         Serial.print(service, HEX);
    //         Serial.print(", ");
    //         Serial.print(rec_data[0], HEX);
    //         Serial.print(", ");
    //         Serial.print(rec_data[1], HEX);
    //         Serial.print(", ");
    //         Serial.print(rec_data[2], HEX);
    //         Serial.print(", ");
    //         Serial.print(rec_data[3], HEX);
    //         Serial.print(", ");
    //         Serial.print(rec_data[4], HEX);
    //         Serial.print(", ");
    //         Serial.print(rec_data[5], HEX);
    //         Serial.print(", ");
    //         Serial.print(rec_data[6], HEX);
    //         Serial.print(", ");
    //         Serial.println(rec_data[7], HEX);
    //         // on_service_0x07_can(rxId, rec_data);
    //         break;              
    //     default:
    //         break;
    // }


}

