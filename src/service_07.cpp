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
#include "eprom.h"

void on_service_0x07(String line_in);
void save_on_flash_serv7();
void com_0x07_0x00(String command);
void com_0x07_0x01(String command);
void com_0x07_0x02(String command);
void com_0x07_0x03(String command);
void com_0x07_0x04(String command);
void com_0x07_0x05(String command);
void com_0x07_0x06(String command);
void com_0x07_0x07(String command);
void com_0x07_0x08(String command);
void com_0x07_0x09(String command);
void com_0x07_0x0A(String command);
void com_0x07_0x0B(String command);
void com_0x07_0x0C(String command);
void com_0x07_0xFF(String command);


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
// extern int fan3_inf_pwm_stp;

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

extern String ipaddress;
extern String gateway;
extern String subnet;
extern String ssid_name;
extern String ssid_pwd;
extern String ha_ip;
extern String ha_user;
extern String ha_pwd;
extern String ha_device_name;
extern String owner_name;
extern String user_name;
extern String user_pwd;
extern String bt_name;

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


extern var_grow var_grow_7[20];

void on_service_0x07(String line_in){
   // Serial.println("Serv 7");
    split_msg_5(line1);
    int i = toHexc(retMsg5[2]);
    Serial.print("Receive Service 7: ");
    Serial.print(i, HEX);
    Serial.print(",");
    Serial.println(retMsg5[2]);
    switch (i) {
        case 0x00:
            com_0x07_0x00(retMsg5[3]);      
            break;
         case 0x01:
            com_0x07_0x01(retMsg5[3]);      
            break;   
         case 0x02:
            com_0x07_0x02(retMsg5[3]);      
            break;      
         case 0x03:
            com_0x07_0x03(retMsg5[3]);      
            break;
         case 0x04:
            com_0x07_0x04(retMsg5[3]);      
            break;
         case 0x05:
            com_0x07_0x05(retMsg5[3]);      
            break;
         case 0x06:
            com_0x07_0x06(retMsg5[3]);      
            break;
         case 0x07:
            com_0x07_0x07(retMsg5[3]);      
            break;
         case 0x08:
            com_0x07_0x08(retMsg5[3]);      
            break;
         case 0x09:
            com_0x07_0x09(retMsg5[3]);      
            break;
         case 0x0A:
            com_0x07_0x0A(retMsg5[3]);      
            break;
         case 0x0B:
            com_0x07_0x0B(retMsg5[3]);      
            break;
          case 0x0C:
            com_0x07_0x0C(retMsg5[3]);      
            break;   
         case 0xFF:
            com_0x07_0xFF(retMsg5[3]);      
            break;   
    }
}

void save_on_flash_serv7(){
    Serial.println("Save Flash serv 7");
    uint32_t addr;
    String data = "0";
   //  eraseSector(0);
    eraseSector(var_grow_7[0].eprom_address);
   //  eraseSector(4096); 
    for (int i = 0; i <= 12; i++){
        addr = var_grow_7[i].eprom_address;
        data = *var_grow_7[i].var_string; 
         if(writeString(addr, data)){
               Serial.print("Write 1 OK ");
               //  Serial.print("save flash: ");
               //  Serial.print(i);
               //  Serial.print(" - ");
               //  Serial.print("Eprom 1 ");
               //  Serial.print(var_grow_7[i].descr);
               //  Serial.print(" - ");
               //  Serial.print(data);
               //  Serial.print(" - ");
               //  Serial.print(addr);
               // String ret = read_String(addr);
               // Serial.print(" - ");
               // Serial.println(ret);
         }else{
               Serial.println("Write 1 not OK");
         }
    }
}

 void com_0x07_0x00(String command){
   //  var_grow_7[0].stringValue = command;  
    ssid_name = command;  
    Serial.println("serv 7 ssid");
 }    

 void com_0x07_0x01(String command){   
   //  var_grow_7[1].stringValue = command;     
    ssid_pwd = command;
    Serial.println("serv 7 pwd");
 }    

 void com_0x07_0x02(String command){     
   //  var_grow_7[2].stringValue = command;     
    ipaddress = command;
 }    

 void com_0x07_0x03(String command){
   //  var_grow_7[3].stringValue = command;     
    gateway = command;Serial.print(" - ");
 }    

 void com_0x07_0x04(String command){
   //  var_grow_7[4].stringValue = command;    
    subnet = command;
 }    

 void com_0x07_0x05(String command){ 
   //  var_grow_7[5].stringValue = command;     
    ha_ip = command;
    Serial.println("serv 7 ha_ip");
 }    

 void com_0x07_0x06(String command){  
   //  var_grow_7[6].stringValue = command;     
    ha_user = command;
    Serial.println("serv 7 ha_user");
 }    

 void com_0x07_0x07(String command){   
   //  var_grow_7[7].stringValue = command;     
    ha_pwd = command;
    Serial.println("serv 7 ha_pwd");
 }    

 void com_0x07_0x08(String command){   
   //  var_grow_7[8].stringValue = command;     
    ha_device_name = command;
    Serial.println("serv 7 ha_device");
 }    

 void com_0x07_0x09(String command){   
   //  var_grow_7[9].stringValue = command;     
    owner_name = command;
 }    

 void com_0x07_0x0A(String command){   
   //  var_grow_7[10].stringValue = command;     
    user_name = command;
 }    

 void com_0x07_0x0B(String command){     
   //  var_grow_7[11].stringValue = command;     
    user_pwd = command;
 }  

 void com_0x07_0x0C(String command){     
   //  var_grow_7[11].stringValue = command;     
    bt_name = command;
 }  

 

 void com_0x07_0xFF(String command){
   //  Serial.println("serv 01 - 25");
    save_on_flash_serv7();
}    