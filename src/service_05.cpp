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
#include "program.h"


void on_service_0x05(String line_in);
void com_0x05_0x00(float com_pwm);
void com_0x05_0x01(float com_pwm);
void com_0x05_0x02(float com_pwm);
void com_0x05_0x03(float com_pwm);

void save_on_flash_serv5();


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
extern int co2_min_stp;
extern int co2_max_stp;
// extern int fan3_inf_pwm_stp;

//Service 02
// extern float eco2_ext;
// extern float eco2_int;
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
extern float co2_int;
extern float co2_ext;

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

extern bool fan_hum_on;
extern bool light_on;
extern bool pump_irr_on;
extern bool hum_on;

extern bool relay_1_on;
extern bool relay_2_on;

extern bool hum_1_on;

extern bool light_on_set;
extern bool pump_irr_on_set;
extern bool pump_hum_on_set;
extern bool relay_1_on_set;
extern bool relay_2_on_set;
extern bool relay_3_on_set;
extern bool relay_4_on_set;
extern bool fan1_inf_on_set;
extern bool fan2_inf_on_set;
extern bool hum_1_on_set;

extern bool fan1_inf_pwm_set;
extern bool fan2_inf_pwm_set;
extern bool light_pwm_set;


//Service 05
extern int fan1_inf_pwm;
extern int fan2_inf_pwm;
extern int fan3_inf_pwm;
extern int light_pwm;
extern int hum_1_pwm;

extern HardwareTimer *tim1;



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
// extern var_grow var_grow_4[40];
extern var_grow var_grow_5[10];
// extern var_grow var_grow_6[30];
// extern var_grow var_grow_7[30];
// extern var_grow var_grow_9[10];
extern var_grow var_grow_A[10];




void on_service_0x05(String line_in){
    Serial.println("on service 5");
    Serial.println(line_in);
    split_msg_5(line_in);
    
    // float rec_data[5];
    // for (int x = 0; x<5; x++){
    //     rec_data[x] = (retMsg5[x]).toFloat();
    // //     Serial.print(rec_data[x]);
    // //     Serial.print(",");
    // // }
    Serial.println(line_in);
    int i = retMsg5[2].toInt(); 
    switch (i) {
        case 0x00:
            Serial.println("pwm 0x05 0x00 Fan 1 Desum");
            com_0x05_0x00(retMsg5[3].toFloat());
            break;
        case 0x01:
            Serial.println("on/off 0x04 0x01 Fan2 Insu");
            com_0x05_0x01(retMsg5[3].toFloat());
            break;       
         case 0x02:
            // Serial.println("on/off 0x04 0x01 Fan1 Insu");
            com_0x05_0x02(retMsg5[3].toFloat());
            break;           
        case 0x03:
            // Serial.println("on/off 0x04 0x06 Lights");
            com_0x05_0x03(retMsg5[3].toFloat());
            break;
    }
    show_display_2();
    relay_1_control();
    relay_2_control();
    relay_3_control();
    relay_4_control();
}

void save_on_flash_serv5(){
    // Serial.print("Save Flash");
    uint32_t addr;
    uint32_t data = 0;
    eraseSector(var_grow_5[0].eprom_address);
    for (int i = 0; i <= 2; i++){
        addr = var_grow_5[i].eprom_address;
            data = *var_grow_5[i].var_int; 
            if(writeLong(addr, data)){
                // Serial.print("Write 1 OK ");
                // Serial.print("save flash: ");
                // Serial.print(i);
                // Serial.print("Eprom 1 ");
                // var_grow_5[i].descr;
                // Serial.print(" - ");
                // Serial.print(data);
                // Serial.print(" - ");
                // Serial.print(addr);
                uint8_t ret = read_Byte(addr);
                // Serial.print(" - ");
                // Serial.println(ret);
            }else{
                Serial.println("Write 1 not OK");
            }
    }
}

// void save_on_flash_servA(){
//     // Serial.print("Save Flash");
//     uint32_t addr;
//     uint32_t data = 0;
//     eraseSector(var_grow_A[1].eprom_address);
//     for (int i = 0; i <= 2; i++){
//         addr = var_grow_A[i].eprom_address;
//             data = *var_grow_A[i].var_int; 
//             if(writeLong(addr, data)){
//                 // Serial.print("Write 1 OK ");
//                 // Serial.print("save flash: ");
//                 // Serial.print(i);
//                 // Serial.print("Eprom 1 ");
//                 // var_grow_5[i].descr;
//                 // Serial.print(" - ");
//                 // Serial.print(data);
//                 // Serial.print(" - ");
//                 // Serial.print(addr);
//                 uint8_t ret = readByte(addr);
//                 // Serial.print(" - ");
//                 // Serial.println(ret);
//             }else{
//                 Serial.println("Write 1 not OK");
//             }
//     }
// }



void com_0x05_0x00(float com_pwm){
    fan1_inf_pwm = com_pwm;
    // Serial.println("==================================");
    // Serial.println("fan1: "+fan1_inf_pwm);
    // Serial.println("==================================");
    // delay(1000);
    if (fan1_inf_on){
        // Serial.println("com_pwm_0x01 on");
        tim1->setCaptureCompare(2, fan1_inf_pwm, PERCENT_COMPARE_FORMAT);
    }else{
        // Serial.println("com_pwm_0x01 off");
        tim1->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT);
    }     
    // save_on_flash_serv5();
    // fan1_inf_pwm_set = true;
}

void com_0x05_0x01(float com_pwm){
    fan2_inf_pwm = com_pwm;    
    // Serial.println("fan2: "+fan2_inf_pwm);
    if (fan2_inf_on){
        // Serial.println("com_pwm_0x02 on");
        tim1->setCaptureCompare(3, fan2_inf_pwm, PERCENT_COMPARE_FORMAT);
    }else{
        //  Serial.println("com_pwm_0x02 off");
         tim1->setCaptureCompare(3, 0, PERCENT_COMPARE_FORMAT);
    } 
    // save_on_flash_serv5();  
    // fan2_inf_pwm_set = true;  
}

void com_0x05_0x02(float com_pwm){
    fan3_inf_pwm = com_pwm;    
    // Serial.println("fan2: "+fan2_inf_pwm);
    if (fan2_inf_on){
        // Serial.println("com_pwm_0x02 on");
        // tim1->setCaptureCompare(2, fan2_inf_pwm, PERCENT_COMPARE_FORMAT);
    }else{
        //  Serial.println("com_pwm_0x02 off");
        //  tim1->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT);
    } 
    
}


void com_0x05_0x03(float com_pwm){
    light_pwm = com_pwm;
    
    // Serial.println("light1: "+light_pwm);
    // Serial.print("light1: ");
    // String dataStr = String(*var_grow_5[3].var_int);
    // Serial.println(dataStr);
    if (light_on){
        // Serial.println("com_pwm_0x06 on");
        tim1->setCaptureCompare(1, light_pwm, PERCENT_COMPARE_FORMAT);
        
    }else{
        // Serial.println("com_pwm_0x06 off");
        tim1->setCaptureCompare(1, 0, PERCENT_COMPARE_FORMAT);
    }
    
    // save_on_flash_serv5();
    // light_pwm_set = true;
}

