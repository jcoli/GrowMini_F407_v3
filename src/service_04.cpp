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
#include "comm_esp.h"


void on_service_0x04(String line_in);
void save_on_flash_serv4();
void com_0x04_0x00(String line_in);
void com_0x04_0x01(String line_in);
void com_0x04_0x02(String line_in); 
void com_0x04_0x03(String line_in);
void com_0x04_0x04(String line_in);
void com_0x04_0x05(String line_in);
void com_0x04_0x06(String line_in);
void com_0x04_0x07(String line_in);
void com_0x04_0x08(String line_in);
void com_0x04_0x09(String line_in);
void com_0x04_0x0A(String line_in);
void com_0x04_0x0B(String line_in);
void com_0x04_0x0C(String line_in);
void com_0x04_0x0D(String line_in);
void com_0x04_0x0E(String line_in);


extern byte minutes;
extern byte hours; 
extern byte weekDay;
extern byte day;
extern byte month;
extern byte year;

extern unsigned long loopDelay_pump;
extern unsigned long loopDelay_hum_pump;

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
extern float temp_ext;
extern float hum_ext;
extern float temp_ext;
extern float temp_int;
extern float hum_int;
extern float soil_1_hum;
extern float light_1_int;

//Service 03
extern bool level_irrig_l;
extern bool level_hum_l;
extern bool bt_connected;

//Service 04
extern bool fan1_inf_on;
extern bool fan2_inf_on;
extern bool fan3_inf_on;
extern bool light_on;
extern bool pump_irr_on;
extern bool pump_hum_on;
extern bool pump_dehum_on;
extern bool hum_1_on;
extern bool dehum_1_on;
extern bool relay_1_on;
extern bool relay_2_on;
extern bool relay_3_on;
extern bool relay_4_on;
extern bool relay_5_on;
extern bool relay_6_on;

//Service 05
extern int fan1_inf_pwm;
extern int fan2_inf_pwm;
extern int light_pwm;
extern int hum_pwm;

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

extern String retMsg5[5];

// extern String retMsg10[10];


extern var_grow var_grow_4[10];
extern var_grow var_grow_9[10];


void on_service_0x04(String line_in){
 
    split_msg_5(line1);
    int i = toHexc(retMsg5[2]);

    switch (i) {
        case 0x00:
            Serial.println("on/off 0x04 0x00 Fan Desum");
            com_0x04_0x00(retMsg5[3]);
            break;
        case 0x01:
            // Serial.println("on/off 0x04 0x01 Fan1 Insu");
            com_0x04_0x01(retMsg5[3]);
            break;       
        case 0x02:
            // Serial.println("on/off 0x04 0x02 Fan2 Insu");
            com_0x04_0x02(retMsg5[3]);
            break;

        case 0x03:
            // Serial.println("on/off 0x04 0x02 Fan2 Insu");
            com_0x04_0x03(retMsg5[3]);
            break;
        case 0x04:
            // Serial.println("on/off 0x04 0x02 Fan2 Insu"esp );
            com_0x04_0x04(retMsg5[3]);
            break;
        case 0x05:
            // Serial.println("on/off 0x04 0x02 Fan2 Insu");
            com_0x04_0x05(retMsg5[3]);
            break;
        case 0x06:
            // Serial.println("on/off 0x04 0x06 Lights");
            com_0x04_0x06(retMsg5[3]);
            break;
        case 0x07:
            // Serial.println("on/off 0x04 0x06 Lights");
            com_0x04_0x07(retMsg5[3]);
            break;
        case 0x08:
            // Serial.println("on/off 0x04 0x06 Lights");
            com_0x04_0x08(retMsg5[3]);
            break;
        case 0x09:
            // Serial.println("on/off 0x04 0x06 Lights");
            com_0x04_0x09(retMsg5[3]);
            break;
        case 0x0A:
            // Serial.println("on/off 0x04 0x06 Lights");
            com_0x04_0x0A(retMsg5[3]);
            break;    
        case 0x0B:
            // Serial.println("on/off 0x04 0x0B Bomba Rega");
            com_0x04_0x0B(retMsg5[3]);
            break;                        
        case 0x0C:
            // Serial.println("on/off 0x04 0x0B Um");
            com_0x04_0x0C(retMsg5[3]);
            break;                        
        case 0x0D:
            // Serial.println("on/off 0x04 0x0D");
            com_0x04_0x0D(retMsg5[3]);
            break;
        case 0x0E:
            // Serial.println("on/off 0x04 0x0E");
            com_0x04_0x0E(retMsg5[3]);
            break;
        
     }
     show_display_2();
     relay_1_control();
     relay_2_control();
     relay_3_control();
     relay_4_control();
    
}

void save_on_flash_serv4(){
    // Serial.print("Save Flash");
    uint16_t addr;
    uint8_t data = 0;
    eraseSector(var_grow_4[0].eprom_address);
    for (int i = 0; i <= 6; i++){
        addr = var_grow_4[i].eprom_address;
        if (*var_grow_4[i].var_bool){
            data = 255; 
            if(writeByte(addr, data)){
                    // Serial.print("Write 1 OK ");
                    // Serial.print("save flash: ");
                    // Serial.println(i);
                    // Serial.print("Eprom 1 ");
                    // Serial.print(data, BIN);
                    // Serial.print(", ");
                    // Serial.println(addr);
                    uint8_t ret = read_Byte(addr);
                    // Serial.print("Eprom 1 ");
                    // Serial.println(ret, BIN);
            }else{
                    Serial.println("Write 1 not OK");
            }
        }else{
            data = 0;
            if(writeByte(addr, data)){
                
                // Serial.println("Write 0 OK ");
                // Serial.print("save flash: ");
                // Serial.println(i);
                // Serial.print("Eprom 1 ");
                // Serial.print(data, BIN);
                // Serial.print(", ");
                // Serial.println(addr);
                uint8_t ret = read_Byte(addr);
                // Serial.print("Eprom 1 ");
                // Serial.println(ret, BIN);
            }else{
                Serial.println("Write 0 Not OK");
            }
        }
    }
    
}

// void save_on_flash_serv9(){
//     // Serial.print("Save Flash");
//     uint16_t addr;
//     uint8_t data = 0;
//     eraseSector(SERVICE_0X09);
//     for (int i = 0; i <= 6; i++){
//         addr = var_grow_9[i].eprom_address;
//         if (*var_grow_9[i].var_bool){
//             data = 255; 
//             if(writeByte(addr, data)){
//                     // Serial.print("Write 1 OK ");
//                     // Serial.print("save flash: ");
//                     // Serial.println(i);
//                     // Serial.print("Eprom 1 ");
//                     // Serial.print(data, BIN);
//                     // Serial.print(", ");
//                     // Serial.println(addr);
//                     uint8_t ret = readByte(addr);
//                     // Serial.print("Eprom 1 ");
//                     // Serial.println(ret, BIN);
//             }else{
//                     Serial.println("Write 1 not OK");
//             }
//         }else{
//             data = 0;
//             if(writeByte(addr, data)){
                
//                 // Serial.println("Write 0 OK ");
//                 // Serial.print("save flash: ");
//                 // Serial.println(i);
//                 // Serial.print("Eprom 1 ");
//                 // Serial.print(data, BIN);
//                 // Serial.print(", ");
//                 // Serial.println(addr);
//                 uint8_t ret = readByte(addr);
//                 // Serial.print("Eprom 1 ");
//                 // Serial.println(ret, BIN);
//             }else{
//                 Serial.println("Write 0 Not OK");
//             }
//         }
//     }
    
// }

void com_0x04_0x00(String command){
    Serial.print("Fan1");
    Serial.println(command);
    if (command.equals("1")){
        fan1_inf_on = true;
        tim1->setCaptureCompare(1, fan1_inf_pwm, PERCENT_COMPARE_FORMAT);
        // Serial.println("com_0x01 on");
    }else{
        fan1_inf_on = false;
        tim1->setCaptureCompare(1, 0, PERCENT_COMPARE_FORMAT);
        // Serial.println("com_0x01 off");
    } 
    // digitalWrite(FAN01, fan1_inf_on);  
    send_esp_bt("1","4","0", String(fan1_inf_on ? "1" : "0"));
    
}

void com_0x04_0x01(String command){
    Serial.print("Fan2");
    // Serial.println(command);
    if (command.equals("1")){
        fan2_inf_on = true;
        tim1->setCaptureCompare(2, fan1_inf_pwm, PERCENT_COMPARE_FORMAT);
        // Serial.println("com_0x01 on");
    }else{
        fan2_inf_on = false;
        tim1->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT);
        // Serial.println("com_0x01 off");
    } 
    digitalWrite(FAN02, fan2_inf_on);  
    send_esp_bt("1","4","1", String(fan2_inf_on ? "1" : "0"));
    // fan1_inf_on_set = true;
    // save_on_flash_serv4();
}

void com_0x04_0x02(String command){
    Serial.print("Fan3");
    // Serial.println(command);
    fan3_inf_on = bool(command ? "1" : "0");
    send_esp_bt("1","4","2", String(fan3_inf_on ? "1" : "0"));
    // fan2_inf_on_set = true;
    // save_on_flash_serv4();
}

void com_0x04_0x03(String command){
    Serial.print("light_on");
    // Serial.println(command);
    if (command.equals("1")){
        light_on = true;
        tim1->setCaptureCompare(3, fan2_inf_pwm, PERCENT_COMPARE_FORMAT);
        // Serial.println("com_0x02 on");
      }else{
        light_on = false;
        tim1->setCaptureCompare(3, 0, PERCENT_COMPARE_FORMAT);
        // Serial.println("com_0x02 off");
    }    
    send_esp_bt("1","4","3", String(light_on ? "1" : "0"));
    // digitalWrite(FAN02, fan2_inf_on);
    // fan3_inf_on_set = true;
    // save_on_flash_serv4();
}

void com_0x04_0x04(String command){
    Serial.print("dehum pump");
    // Serial.println(command);
    pump_dehum_on = bool(command ? "1" : "0"); 
    send_esp_bt("1","4","4", String(pump_dehum_on ? "1" : "0"));
}

void com_0x04_0x05(String command){
    Serial.print("pump_hum_on");
    // Serial.println(command);
    pump_hum_on = bool(command ? "1" : "0"); 
    digitalWrite(PUMP2, pump_hum_on);
    loopDelay_hum_pump = millis();
    send_esp_bt("1","4","5", String(pump_hum_on ? "1" : "0"));
}

void com_0x04_0x06(String command){
    Serial.print("pump_irr_on");
    // Serial.println(command);
    pump_irr_on = bool(command ? "1" : "0"); 
    digitalWrite(PUMP1, pump_irr_on);
    send_esp_bt("1","4","6", String(pump_irr_on ? "1" : "0"));
    loopDelay_pump = millis();
    
}

void com_0x04_0x07(String command){
    Serial.print("hum_1_on");
    // Serial.println(command);
    hum_1_on = bool(command? "1" : "0");
    digitalWrite(HUM, hum_1_on);
    send_esp_bt("1","4","7", String(hum_1_on ? "1" : "0"));
}

void com_0x04_0x08(String command){
    Serial.println("dehum_1_on");
    dehum_1_on = bool(command? "1" : "0");
    send_esp_bt("1","4","8", String(dehum_1_on ? "1" : "0"));
}
 
void com_0x04_0x09(String command){
    Serial.println("relay_1_on");
    relay_1_on = bool(command? "1" : "0");
    digitalWrite(RELAY1, relay_1_on);
    send_esp_bt("1","4","9", String(relay_1_on ? "1" : "0"));
}

void com_0x04_0x0A(String command){
    Serial.println("relay_2_on");
    relay_2_on = bool(command? "1" : "0");
    digitalWrite(RELAY2, relay_2_on);
    send_esp_bt("1","10","9", String(relay_2_on ? "1" : "0"));
}


void com_0x04_0x0B(String command){
    Serial.println("relay_3_on");
    relay_3_on = bool(command? "1" : "0");
    digitalWrite(RELAY3, relay_3_on);
    send_esp_bt("1","11","9", String(relay_3_on ? "1" : "0"));
}


void com_0x04_0x0C(String command){
    Serial.println("relay_4_on");
    relay_4_on = bool(command? "1" : "0");
    digitalWrite(RELAY4, relay_4_on);
    send_esp_bt("1","12","9", String(relay_4_on ? "1" : "0"));

}

void com_0x04_0x0D(String command){
    Serial.println("relay_5_on");
    relay_5_on = bool(command? "1" : "0");
    // digitalWrite(RELAY5, relay_5_on);
    send_esp_bt("1","4","13", String(relay_5_on ? "1" : "0"));
    
}

void com_0x04_0x0E(String command){
    Serial.println("relay_6_on");
    // Serial.println("Relay 1");
    relay_6_on = bool(command? "1" : "0");
    // digitalWrite(RELAY6, relay_6_on);
    send_esp_bt("1","4","14", String(relay_6_on ? "1" : "0"));
}





