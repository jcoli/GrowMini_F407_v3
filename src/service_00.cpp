/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#include <Arduino.h>

#include "eprom.h"
#include "defines.h"
#include "io_defines.h"
#include "display.h"
#include "structures.h"
#include "defines_protocol.h"
#include "tools.h" 

void on_service_0x00(String line_in);

void com_0x00_0x00(String command);
void com_0x00_0x01(String command);
void com_0x00_0x02(String command);
void com_0x00_0x03(String command);
void com_0x00_0x04(String command);
void com_0x00_0x05(String command);
void com_0x00_0x06(String command);
void com_0x00_0x07(String command);
void com_0x00_0x08(String command);
void com_0x00_0x09(String command);
void com_0x00_0x0A(String command);
void com_0x00_0x0B(String command);
void com_0x00_0x0C(String command);
void com_0x00_0x0D(String command);
void com_0x00_0x0E(String command);
void com_0x00_0x0F(String command);
void com_0x00_0x10(String command);
void com_0x00_0x11(String command);
void com_0x00_0x12(String command);
void com_0x00_0x13(String command);
void com_0x00_0x14(String command);
void com_0x00_0x15(String command);
void com_0x00_0x16(String command);
void com_0x00_0x17(String command);
void com_0x00_0x18(String command);
void com_0x00_0x19(String command);
void com_0x00_0x1A(String command);
void com_0x00_0x1B(String command);
void com_0x00_0x1C(String command);
void com_0x00_0x1D(String command);
void com_0x00_0x1E(String command);
void com_0x00_0x1F(String command);
void com_0x00_0x20(String command);
void com_0x00_0x21(String command);
void com_0x00_0x22(String command);
void com_0x00_0x23(String command);
void com_0x00_0x24(String command);


extern bool first_run;

extern int language;

extern byte minutes;
extern byte hours; 
extern byte weekDay;
extern byte day;
extern byte month;
extern byte year;

extern bool first_run;

extern int language;

//Service 01
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


//Service 02
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

//Service 03
extern bool level_irrig_l;
extern bool level_hum_l;
extern bool door;
extern bool wifi_connected;
extern bool mqtt_connected;
extern bool bt_connected;

//Service 04
extern bool fan_dehum_on;
extern bool fan1_inf_on;
extern bool fan2_inf_on;
extern bool fan3_inf_on;

extern bool fan_hum_on;
extern bool light_on;
extern bool pump_irr_on;
extern bool hum_on;

extern bool relay_1_on;
extern bool relay_2_on;
extern bool hum_1_on;

//Service 05
extern int fan1_inf_pwm;
extern int fan2_inf_pwm;
extern int light_pwm;
extern int hum_1_pwm;

// extern bool soil_hum_dig;

// extern bool ch_page;
// extern bool ch_page_ana;
// extern int tft_page;
// extern int tft_page_ant;
// extern int tft_sub_page;
// extern int tft_sub_page_ant;
// extern int draw_tab;
// extern int draw_page;

// extern String line;
extern String line1;
// extern String line2;
// extern String retMsg2[2];
// extern String retMsg3[3];
// extern String retMsg4[4];
extern String retMsg5[5];
// extern String retMsg6[6];
// extern String retMsg7[7];
// extern String retMsg8[8];
// extern String retMsg9[9];
// extern String retMsg10[10];

// extern var_grow var_grow_1[50];
// extern var_grow var_grow_2[40];
// extern var_grow var_grow_3[40];
extern var_grow var_grow_4[10];
// extern var_grow var_grow_5[30];
// extern var_grow var_grow_6[30];
// extern var_grow var_grow_7[30];

void on_service_0x00(String line_in){
    split_msg_5(line1);
    int i = toHexc(retMsg5[2]);
     switch (i) {
        case 0x00:
            // Serial.println("Status Temp Ext 0x03 0x00");
            com_0x00_0x00(retMsg5[3]); 
            break;
        case 0x01:
            // Serial.println("Status Temp Int 0x03 0x01");
            com_0x00_0x01(retMsg5[3]);
            break;    
        case 0x02:
            // Serial.println("Status Hum Ext 0x03 0x02");
            com_0x00_0x02(retMsg5[3]);
            break;
        case 0x03:
            // Serial.println("Status Hum Ext 0x03 0x03");
            com_0x00_0x03(retMsg5[3]);
            break;    
        case 0x04:
            // Serial.println("Status C02 Ext 0x03 0x04");
            com_0x00_0x04(retMsg5[3]);
            break;    
        case 0x05:
            // Serial.println("Status C02 Int 0x03 0x05");
            com_0x00_0x05(retMsg5[3]);
            break;    
        case 0x06:
            // Serial.println("Status Fan desum 0x03 0x06");
            com_0x00_0x06(retMsg5[3]);
            break;    
        case 0x07:
            // Serial.println("Status Fan1 0x03 0x07");
            com_0x00_0x07(retMsg5[3]);
            break;    
        case 0x08:
            // Serial.println("Status Fan2 0x03 0x08");
            com_0x00_0x08(retMsg5[3]);
            break;    
        case 0x09:
            // Serial.println("Status Light 0x03 0x09");
            com_0x00_0x09(retMsg5[3]);
            break;    
        case 0x0A:
            // Serial.println("Status Fan Peltier Insu 0x03 0x0A");
            com_0x00_0x0A(retMsg5[3]);
            break;    
        case 0x0B:
            // Serial.println("Status Fan Peltier Desum 0x03 0x0B");
            com_0x00_0x0B(retMsg5[3]);
            break;    
        case 0x0C:
            // Serial.println("Status Light 0x03 0x0C");
            com_0x00_0x0C(retMsg5[3]);
            break;
        case 0x0D:
            // Serial.println("Status Door 0x03 0x0D");
            com_0x00_0x0D(retMsg5[3]);
            break;       
        case 0x0E:
            // Serial.println("Status Water Level irrigation 0x03 0x0E");
            com_0x00_0x0E(retMsg5[3]);
            break;
        case 0x0F:
            // Serial.println("Status Water Level Hum 0x03 0x0F");
            com_0x00_0x0F(retMsg5[3]);
            break;         
        case 0x10:
            // Serial.println("Status Fan Petier 0x03 0x10");
            com_0x00_0x10(retMsg5[3]);
            break;
        case 0x11:
            // Serial.println("Status Fan Petier 0x03 0x11");
            com_0x00_0x11(retMsg5[3]);
            break;
        case 0x12:
            // Serial.println("Status Pump Desum 0x03 0x12");
            com_0x00_0x12(retMsg5[3]);
            break;
        case 0x13:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x13(retMsg5[3]);
            break;
        case 0x14:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x14(retMsg5[3]);
            break;    
        case 0x15:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x15(retMsg5[3]);
            break;    
        case 0x16:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x16(retMsg5[3]);
            break;    
        case 0x17:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x17(retMsg5[3]);
            break;    
        case 0x18:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x18(retMsg5[3]);
            break;    
        case 0x19:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x19(retMsg5[3]);
            break;    
        case 0x1A:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x1A(retMsg5[3]);
            break;    
        case 0x1B:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x1B(retMsg5[3]);
            break;    
        case 0x1C:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x1C(retMsg5[3]);
            break;    
        case 0x1D:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x1D(retMsg5[3]);
            break;    
        case 0x1E:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x1E(retMsg5[3]);
            break;    
        case 0x1F:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x1F(retMsg5[3]);
            break;    
        case 0x20:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x20(retMsg5[3]);
            break;    
        case 0x21:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x21(retMsg5[3]);
            break;    
        case 0x22:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x22(retMsg5[3]);
            break;        
        case 0x23:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x23(retMsg5[3]);
            break;        
        case 0x24:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x00_0x24(retMsg5[3]);
            break;        
     }
}

void com_0x00_0x00(String command){
    
}

void com_0x00_0x01(String command){
    
}

void com_0x00_0x02(String command){
    
}

void com_0x00_0x03(String command){
    
}

void com_0x00_0x04(String command){
    
}

void com_0x00_0x05(String command){
    
}

void com_0x00_0x06(String command){
    
}

void com_0x00_0x07(String command){
    
}

void com_0x00_0x08(String command){
    
}

void com_0x00_0x09(String command){
    
}

void com_0x00_0x0A(String command){
    
}

void com_0x00_0x0B(String command){
    
}

void com_0x00_0x0C(String command){
    
}

void com_0x00_0x0D(String command){
    
}

void com_0x00_0x0E(String command){
    
}

void com_0x00_0x0F(String command){
    
}

void com_0x00_0x10(String command){
    
}

void com_0x00_0x11(String command){
    
}

void com_0x00_0x12(String command){
    
}

void com_0x00_0x13(String command){
    
}

void com_0x00_0x14(String command){
    
}

void com_0x00_0x15(String command){
    
}

void com_0x00_0x16(String command){
    
}

void com_0x00_0x17(String command){
    
}

void com_0x00_0x18(String command){
    
}

void com_0x00_0x19(String command){
    
}

void com_0x00_0x1A(String command){
    
}

void com_0x00_0x1B(String command){
    
}

void com_0x00_0x1C(String command){
    
}

void com_0x00_0x1D(String command){
    
}

void com_0x00_0x1E(String command){
    
}

void com_0x00_0x1F(String command){
    
}

void com_0x00_0x20(String command){
    
}

void com_0x00_0x21(String command){
    
}

void com_0x00_0x22(String command){
    
}

void com_0x00_0x23(String command){
    
}

void com_0x00_0x24(String command){
    
}