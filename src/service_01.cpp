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
#include "schedule.h"
#include "tools.h"
#include "fuzzyControl.h"


void on_service_0x01(String line_in);
void save_on_flash_serv1();
void com_0x01_0x00(int command);
void com_0x01_0x1(int command);
void com_0x01_0x2(int command);
void com_0x01_0x3(int command);
void com_0x01_0x4(int command);
void com_0x01_0x5(int command);
void com_0x01_0x06(int command);
void com_0x01_0x07(int command);
void com_0x01_0x08(int command);
void com_0x01_0x09(int command);
void com_0x01_0x0A(int command);
void com_0x01_0x0B(int command);
void com_0x01_0x0C(int command);
void com_0x01_0x0D(int command);
void com_0x01_0x0E(int command);
void com_0x01_0x0F(int command);
void com_0x01_0x10(int command);
void com_0x01_0x11(int command);
void com_0x01_0x12(int command);
void com_0x01_0x13(int command);
void com_0x01_0x14(int command);
void com_0x01_0x15(int command);
void com_0x01_0x16(int command);
void com_0x01_0x17(int command);
void com_0x01_0x18(int command);
void com_0x01_0x19(int command);
void com_0x01_0x1A(int command);
void com_0x01_0x1B(int command);
void com_0x01_0x1C(int command);
void com_0x01_0x1D(int command);
void com_0x01_0x1E(int command);
void com_0x01_0x1F(int command);
void com_0x01_0x20(int command);
void com_0x01_0x21(int command);
void com_0x01_0x22(int command);
void com_0x01_0x23(int command);
void com_0x01_0x24(int command);
void com_0x01_0x25(int command);
void com_0x01_0x26(int command);
void com_0x01_0x27(int command);
void com_0x01_0x28(int command);
void com_0x01_0x29(int command);
void com_0x01_0x2A(int command);
void com_0x01_0x2B(int command);
void com_0x01_0x2C(int command);
void com_0x01_0x2D(int command);
void com_0x01_0x2E(int command);
void com_0x01_0x2F(int command);
void com_0x01_0x30(int command);
void com_0x01_0x31(String command);
void com_0x01_0x32(String command);
void com_0x01_0x33(int command);
void com_0x01_0x34(int command);


void com_ser01_0xFF(int command);

extern byte minutes;
extern byte hours; 
extern byte weekDay;
extern byte day;
extern byte month;
extern byte year;

extern bool first_run;

extern int language;

//Service 01

extern int temp_int_min_stp;
extern int temp_int_max_stp;

extern int hum_int_on_stp;

extern int hum_int_min_stp;
extern int hum_int_max_stp;

extern int vpd_int_min_stp;
extern int vpd_int_max_stp;

extern int co2_min_stp;
extern int co2_max_stp;

extern int soil_hum_min_stp;
extern int soil_hum_max_stp;
extern int ph_irrig_stp;
extern int ph_hum_stp;

extern int light_hr_on_stp;
extern int light_min_on_stp;
extern int light_hr_off_stp;
extern int light_min_off_stp;

extern int pump_irr_on_stp;
extern int pump_hr_irr_on_stp;
extern int pump_min_irr_on_stp;
extern int pump_hr_irr_off_stp;
extern int pump_min_irr_off_stp;

extern int irr_interval_stp;
extern int irr_time_stp;
extern int irr_interval_on_stp;
extern int irr_on_stp; 
extern int irr_1_hr_stp ;
extern int irr_1_min_stp;
extern int irr_2_hr_stp;
extern int irr_2_min_stp;


extern int light_pwm_stp;
extern int fan1_inf_pwm_stp;
extern int fan2_inf_pwm_stp;
extern int fan3_inf_pwm_stp;

extern int fan1_inf_pwm_light_stp;
extern int fan2_inf_pwm_light_stp;
extern int fan3_inf_pwm_light_stp;

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

extern String line1;
extern String retMsg5[5];

extern int relay_1_on_hr_stp;
extern int relay_1_on_min_stp;
extern int relay_1_off_hr_stp;
extern int relay_1_off_min_stp;
extern int relay_2_on_hr_stp;
extern int relay_2_on_min_stp;
extern int relay_2_off_hr_stp;
extern int relay_2_off_min_stp;
extern int relay_3_on_hr_stp;
extern int relay_3_on_min_stp;
extern int relay_3_off_hr_stp;
extern int relay_3_off_min_stp;
extern int relay_4_on_hr_stp;
extern int relay_4_on_min_stp;
extern int relay_4_off_hr_stp;
extern int relay_4_off_min_stp;
extern int relay_1_red_stp;
extern int relay_2_red_stp;
extern int relay_3_red_stp;
extern int relay_4_red_stp;

extern int vpd_int_min_stp;
extern int vpd_int_max_stp;

extern var_grow var_grow_1[60];



void on_service_0x01(String line_in){
    split_msg_5(line1);
    int i = toHexc(retMsg5[2]);
    Serial.print("Receive Service 1: ");
    Serial.print(i, HEX);
    Serial.print(",");
    Serial.println(retMsg5[2]);
     switch (i) {
        case 0x00:
            Serial.println("Status Temp Ext 0x03 0x00");
            com_0x01_0x00(retMsg5[3].toInt()); 
            break;
        case 0x01:
            Serial.println("Status Temp int 0x03 0x01");
            com_0x01_0x1(retMsg5[3].toInt());
            break;    
        case 0x02:
            Serial.println("Status Hum Ext 0x03 0x02");
            com_0x01_0x2(retMsg5[3].toInt());
            break;
        case 0x03:
            Serial.println("Status Hum Ext 0x03 0x03");
            com_0x01_0x3(retMsg5[3].toInt());
            break;    
        case 0x04:
            Serial.println("Status C02 Ext 0x03 0x04");
            com_0x01_0x4(retMsg5[3].toInt());
            break;    
        case 0x05:
            // Serial.println("Status C02 int 0x03 0x05");
            com_0x01_0x5(retMsg5[3].toInt());
            break;    
        case 0x06:
            // Serial.println("Status Fan desum 0x03 0x06");
            com_0x01_0x06(retMsg5[3].toInt());
            break;    
        case 0x07:
            // Serial.println("Status Fan1 0x03 0x07");
            com_0x01_0x07(retMsg5[3].toInt());
            break;    
        case 0x08:
            // Serial.println("Status Fan2 0x03 0x08");
            com_0x01_0x08(retMsg5[3].toInt());
            break;    
        case 0x09:
            // Serial.println("Status Light 0x03 0x09");
            com_0x01_0x09(retMsg5[3].toInt());
            break;    
        case 0x0A:
            // Serial.println("Status Fan Peltier Insu 0x03 0x0A");
            com_0x01_0x0A(retMsg5[3].toInt());
            break;    
        case 0x0B:
            // Serial.println("Status Fan Peltier Desum 0x03 0x0B");
            com_0x01_0x0B(retMsg5[3].toInt());
            break;    
        case 0x0C:
            // Serial.println("Status Light 0x03 0x0C");
            com_0x01_0x0C(retMsg5[3].toInt());
            break;
        case 0x0D:
            // Serial.println("Status Door 0x03 0x0D");
            com_0x01_0x0D(retMsg5[3].toInt());
            break;       
        case 0x0E:
            // Serial.println("Status Water Level irrigation 0x03 0x0E");
            com_0x01_0x0E(retMsg5[3].toInt());
            break;
        case 0x0F:
            // Serial.println("Status Water Level Hum 0x03 0x0F");
            com_0x01_0x0F(retMsg5[3].toInt());
            break;         
        case 0x10:
            // Serial.println("Status Fan Petier 0x03 0x10");
            com_0x01_0x10(retMsg5[3].toInt());
            break;
        case 0x11:
            // Serial.println("Status Fan Petier 0x03 0x11");
            com_0x01_0x11(retMsg5[3].toInt());
            break;
        case 0x12:
            // Serial.println("Status Pump Desum 0x03 0x12");
            com_0x01_0x12(retMsg5[3].toInt());
            break;
        case 0x13:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x13(retMsg5[3].toInt());
            break;
        case 0x14:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x14(retMsg5[3].toInt());
            break;    
        case 0x15:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x15(retMsg5[3].toInt());
            break;    
        case 0x16:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x16(retMsg5[3].toInt());
            break;    
        case 0x17:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x17(retMsg5[3].toInt());
            break;    
        case 0x18:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x18(retMsg5[3].toInt());
            break;    
        case 0x19:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x19(retMsg5[3].toInt());
            break;    
        case 0x1A:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x1A(retMsg5[3].toInt());
            break;    
        case 0x1B:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x1B(retMsg5[3].toInt());
            break;    
        case 0x1C:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x1C(retMsg5[3].toInt());
            break;    
        case 0x1D:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x1D(retMsg5[3].toInt());
            break;    
        case 0x1E:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x1E(retMsg5[3].toInt());
            break;    
        case 0x1F:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x1F(retMsg5[3].toInt());
            break;    
        case 0x20:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x20(retMsg5[3].toInt());
            break;    
        case 0x21:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x21(retMsg5[3].toInt());
            break;    
        case 0x22:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x22(retMsg5[3].toInt());
            break;    
        case 0x23:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x23(retMsg5[3].toInt());
            break;    
        case 0x24:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x24(retMsg5[3].toInt());
            break;    
        case 0x25:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x25(retMsg5[3].toInt());
            break;    
        case 0x26:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x26(retMsg5[3].toInt());
            break;    
        case 0x27:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x27(retMsg5[3].toInt());
            break;    
        case 0x28:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x28(retMsg5[3].toInt());
            break;    
        case 0x29:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x29(retMsg5[3].toInt());
            break;    
        case 0x2A:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x2A(retMsg5[3].toInt());
            break;    
        case 0x2B:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x2B(retMsg5[3].toInt());
            break;    
        case 0x2C:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x2C(retMsg5[3].toInt());
            break;    
        case 0x2D:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x2D(retMsg5[3].toInt());
            break;            
         case 0x2E:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x2E(retMsg5[3].toInt());
            break;            
        case 0x2F:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x2F(retMsg5[3].toInt());
            break;            
        case 0x30:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x30(retMsg5[3].toInt());
            break;            
        case 0x31:
            Serial.print(" 0x01 0x31 : ");
            Serial.print(retMsg5[3]);
            Serial.print(".");
            Serial.println(retMsg5[3].toInt());
            // int vpd = (int)(retMsg5[3].toFloat()*100);
            com_0x01_0x31(retMsg5[3]);
            break;        

        case 0x32:
            Serial.print("0x01 0x32 : ");
            Serial.print(retMsg5[3]);
            Serial.print(".");
            Serial.println(retMsg5[3].toInt());
            com_0x01_0x32(retMsg5[3]);
            break; 

        case 0x33:
            // Serial.println("Status Pump Insu 0x03 0x13");
            com_0x01_0x33(retMsg5[3].toInt());
            break;       

        case 0x34:
            Serial.print(" 0x01 0x31 : ");
            Serial.print(retMsg5[3]);
            Serial.print(".");
            Serial.println(retMsg5[3].toInt());
            // int vpd = (int)(retMsg5[3].toFloat()*100);
            com_0x01_0x34(retMsg5[3].toInt());
            break;                  
            
                   
        case 0xFF:
            Serial.println("Save Flash");
            com_ser01_0xFF(retMsg5[3].toInt());
            // beginFuzzy();
            schedule_check();
            break;              
        
     }
   
}

void save_on_flash_serv1(){
    Serial.print("Save Flash");
    uint32_t addr;
    uint32_t data = 0;
    if (eraseSector(16384)){
        for (int i = 0; i <= 52; i++){
            addr = var_grow_1[i].eprom_address;
            data = *var_grow_1[i].var_int; 
            // Serial.print("Eprom 1 ");
            // Serial.print(i);
            // delay(50);
           
            if((writeShort(addr, data))){
                    Serial.print("Write 1 OK ");
                    Serial.print("save flash: ");
                    Serial.print(i);
                    Serial.print(" Eprom 1 ");
                    Serial.print(var_grow_1[i].descr);
                    Serial.print(" - ");
                    Serial.print(data);
                    Serial.print(" - ");
                    Serial.print(addr);
                    uint8_t ret = read_Byte(addr);
                    Serial.print(" - ");
                    Serial.println(ret);
                    delay(50);
            }else{
                    Serial.println("Write 1 not OK");
                    // Serial.print("Eprom 1 ");
                    // Serial.print(var_grow_1[i].descr);
                    // Serial.print(" - ");
                    // Serial.print(data);
                    // Serial.print(" - ");
                    // Serial.print(addr);
            }
        }
    }
}

void com_0x01_0x00(int command){
    Serial.println("serv 01 - 00");
    temp_int_max_stp = command;    
}

void com_0x01_0x1(int command){
    // Serial.println("serv 01 - 01");
    temp_int_min_stp = command;
}

void com_0x01_0x2(int command){
    // Serial.println("serv 01 - 02");
    hum_int_max_stp = command;
}

void com_0x01_0x3(int command){
    // Serial.println("serv 01 - 03");
    hum_int_min_stp = command;    
}

void com_0x01_0x4(int command){
    // Serial.println("serv 01 - 04");
    soil_hum_max_stp = command;
}

void com_0x01_0x5(int command){
    // Serial.println("serv 01 - 05");
    soil_hum_min_stp = command;
}

void com_0x01_0x06(int command){
    // Serial.println("serv 01 - 06");
    light_hr_on_stp  = command;
}

void com_0x01_0x07(int command){
    // Serial.println("serv 01 - 07");
    light_min_on_stp = command;
}

void com_0x01_0x08(int command){
    // Serial.println("serv 01 - 08");
    light_hr_off_stp = command;
}

void com_0x01_0x09(int command){
    // Serial.println("serv 01 - 09");
    light_min_off_stp = command;
}

void com_0x01_0x0A(int command){
    // Serial.println("serv 01 - 0A");
    pump_hr_irr_on_stp = command;
}

void com_0x01_0x0B(int command){
    // Serial.println("serv 01 - 0B");
    pump_min_irr_on_stp = command;
}

void com_0x01_0x0C(int command){
    // Serial.println("serv 01 - 0C");
    pump_hr_irr_off_stp = command;
}

void com_0x01_0x0D(int command){
    // Serial.println("serv 01 - 0D");
    pump_min_irr_off_stp = command;    
}

void com_0x01_0x0E(int command){
    // Serial.println("serv 01 - 0E");
    irr_interval_stp = command;
}

void com_0x01_0x0F(int command){
    // Serial.println("serv 01 - 0F");
    irr_time_stp = command*1000;
}

void com_0x01_0x10(int command){
    // Serial.println("serv 01 - 10");
    irr_1_hr_stp = command;
}

void com_0x01_0x11(int command){
    // Serial.println("serv 01 - 11");
    irr_1_min_stp = command*1000;    
}

void com_0x01_0x12(int command){
    // Serial.println("serv 01 - 11");
    irr_2_hr_stp = command;    
}

void com_0x01_0x13(int command){
    // Serial.println("serv 01 - 11");
    irr_2_min_stp = command;    
}

void com_0x01_0x14(int command){
    // Serial.println("serv 01 - 11");
    light_pwm_stp = command;    
}

void com_0x01_0x15(int command){
    // Serial.println("serv 01 - 11");
    fan1_inf_pwm_stp = command;    
}

void com_0x01_0x16(int command){
    // Serial.println("serv 01 - 16");
    fan2_inf_pwm_stp = command;
}

void com_0x01_0x17(int command){
    // Serial.println("serv 01 - 17");
    fan3_inf_pwm_stp = command;
}

void com_0x01_0x18(int command){
    // Serial.println("serv 01 - 18");
    fan1_inf_pwm_light_stp = command;
}

void com_0x01_0x19(int command){
    // Serial.println("serv 01 - 19");
   fan2_inf_pwm_light_stp = command;
}

void com_0x01_0x1A(int command){
    // Serial.println("serv 01 - 1A");
    fan3_inf_pwm_light_stp = command;
}

void com_0x01_0x1B(int command){
    // Serial.println("serv 01 - 1B");
    irr_on_stp = command;
}

void com_0x01_0x1C(int command){
    // Serial.println("serv 01 - 1C");
    hum_int_on_stp = command;
}

void com_0x01_0x1D(int command){
    // Serial.println("serv 01 - 1D");
    relay_1_on_hr_stp = command;
}

void com_0x01_0x1E(int command){
    // Serial.println("serv 01 - 1E");
    relay_1_on_min_stp = command;
}

void com_0x01_0x1F(int command){
    // Serial.println("serv 01 - 1F");
    relay_1_off_hr_stp = command;
}

void com_0x01_0x20(int command){
    // Serial.println("serv 01 - 20");
    relay_1_off_min_stp = command;    
}

void com_0x01_0x21(int command){
    // Serial.println("serv 01 - 21");
    relay_2_on_hr_stp = command;
}

void com_0x01_0x22(int command){
    // Serial.println("serv 01 - 22");
    relay_2_on_min_stp = command;    
}

void com_0x01_0x23(int command){
    // Serial.println("serv 01 - 23");
    relay_2_off_hr_stp = command;
}

void com_0x01_0x24(int command){
    // Serial.println("serv 01 - 24");
    relay_2_off_min_stp = command;
}

void com_0x01_0x25(int command){
    // Serial.println("serv 01 - 25");
    relay_3_on_hr_stp = command;
}

void com_0x01_0x26(int command){
    // Serial.println("serv 01 - 26");
    relay_3_on_min_stp= command;
}

void com_0x01_0x27(int command){
    // Serial.println("serv 01 - 27");
    relay_3_off_hr_stp = command;
}

void com_0x01_0x28(int command){
    // Serial.println("serv 01 - 28");
    relay_3_off_min_stp = command;
}

void com_0x01_0x29(int command){
    // Serial.println("serv 01 - 29");
    relay_4_on_hr_stp = command;
}

void com_0x01_0x2A(int command){
    // Serial.println("serv 01 - 2A");
    relay_4_on_min_stp = command;
}

void com_0x01_0x2B(int command){
    // Serial.println("serv 01 - 2B");
    relay_4_off_hr_stp = command;
}

void com_0x01_0x2C(int command){
    // Serial.println("serv 01 - 2C");
    relay_4_off_min_stp = command;
}

void com_0x01_0x2D(int command){
    // Serial.println("serv 01 - 2D");
   relay_1_red_stp = command;
}

void com_0x01_0x2E(int command){
    // Serial.println("serv 01 - 2E");
    relay_2_red_stp = command;
}

void com_0x01_0x2F(int command){
    // Serial.println("serv 01 - 2F");
    relay_3_red_stp = command;
}

void com_0x01_0x30(int command){
    // Serial.println("serv 01 - 30");
    relay_4_red_stp = command;
}

void com_0x01_0x31(String command){
    Serial.print("serv 01 - 31: ");
    Serial.println(command);
    vpd_int_max_stp = (int)(command.toFloat()*100);;
}

void com_0x01_0x32(String command){
    Serial.print("serv 01 - 32: ");
    Serial.println(command);

    vpd_int_min_stp = (int)(command.toFloat()*100);
}

void com_0x01_0x33(int command){
    Serial.print("serv 01 - 33: ");
    Serial.println(command);

    co2_max_stp =  command;
}

void com_0x01_0x34(int command){
    Serial.print("serv 01 - 34: ");
    Serial.println(command);

    co2_min_stp  = command;
}

void com_ser01_0xFF(int command){
    // Serial.println("serv 01 - FF");
    save_on_flash_serv1();
}  

