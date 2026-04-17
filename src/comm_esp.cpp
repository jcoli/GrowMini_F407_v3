/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#include <Arduino.h>
#include <STM32RTC.h>


#include "display.h"
#include "defines.h"
#include "io_defines.h"
#include "defines_protocol.h"
#include "tools.h"
#include "eprom.h"
#include "pitches.h"
#include "sounds.h"
#include "program.h"
#include "receive_data_can.h"
#include "program.h"

#include "service_00.h"
#include "service_01.h"
#include "service_02.h"
#include "service_03.h"
#include "service_04.h"
#include "service_05.h"
#include "service_06.h"
#include "service_07.h"
#include "service_09.h"



void init_wifi();
void init_ble();
void init_mqtt();
void on_ser_comm(String line_in);
void addlistNetworks();
void listNetworks();
void call_list_net();
void send_esp_bt(String dest, String svc, String pid, String value);
void send_esp_mqtt(String dest, String svc, String pid, String value);

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

extern String Ssid[2][10];
extern String ssid_name;
extern String ssid_pwd;
extern String ha_ip;
extern String ha_user;
extern String ha_pwd;

extern int list_size;
extern int ind_list_size;

extern var_grow var_grow_1[60];
extern var_grow var_grow_2[20];
extern var_grow var_grow_3[20];
extern var_grow var_grow_4[20];
extern var_grow var_grow_5[20];


extern var_grow var_grow_6[20];
extern var_grow var_grow_7[20];
extern var_grow var_grow_8[20];
extern var_grow var_grow_9[20];
extern var_grow var_grow_A[20];

extern STM32RTC& rtc;

extern uint32_t subSec;
extern byte seconds;
extern byte minutes;
extern byte hours; 
extern byte weekDay;
extern byte day;
extern byte month;
extern byte year;


extern var_grow var_grow_6[20];
extern var_grow var_grow_7[20];
extern var_grow var_grow_8[20];
extern var_grow var_grow_9[20];
extern var_grow var_grow_A[20];

extern STM32RTC& rtc;

extern uint32_t subSec;
extern byte seconds;
extern byte minutes;
extern byte hours; 
extern byte weekDay;
extern byte day;
extern byte month;
extern byte year;

void init_wifi(){
    String LOCAL_SSID="";
    String LOCAL_PASS=""; 
    String USERNAME_BROKER="";
    String PASSWORD_BROKER="";
    String IP_BROKER="";
    // Serial.println("on_wifi_init 1");
    uint32_t addr = var_grow_7[0].eprom_address;
    LOCAL_SSID = read_String(addr);
    
    addr = var_grow_7[1].eprom_address;
    LOCAL_PASS = read_String(addr);
    
    if ((LOCAL_PASS == NULL) ||(LOCAL_SSID == NULL) || (LOCAL_PASS == "FF") ||(LOCAL_SSID == "FF") ||(LOCAL_SSID == "0") || (LOCAL_PASS == "0" )){
      // Serial.println("sem dados de wifi");
    }else{
      ssid_pwd=LOCAL_PASS;
      ssid_name=LOCAL_SSID;
      ESP_SERIAL.print("0x00,0x07,0x00,"+ssid_name+",#");
      delay(50);
      ESP_SERIAL.print("0x00,0x07,0x01,"+ssid_pwd+",#");
      delay(50);
      ESP_SERIAL.print("0x06,0x00,0,#");
      delay(50);
    }  
      
}


void init_ble(){
  String BT_NAME="";
  // Serial.println("on_wifi_init 1");
  uint32_t addr = var_grow_7[12].eprom_address;
  BT_NAME = read_String(addr);

  if (BT_NAME == NULL){
    Serial.println("sem dados de bluetooth");
  }else{
    
    ESP_SERIAL.print("0x00,0x07,0x0C,"+BT_NAME+",#");
    delay(50);
    ESP_SERIAL.print("0x06,0x01,0,#");
    delay(50);
  }

}

void init_mqtt(){
  String ip_broker ="";
  String username_broker="";
  String password_broker="";
  String name_device = "";
  uint32_t addr = var_grow_7[5].eprom_address;
  ip_broker = read_String(addr);
  addr = var_grow_7[6].eprom_address;
  username_broker = read_String(addr);
  addr = var_grow_7[7].eprom_address;
  password_broker = read_String(addr);
  addr = var_grow_7[8].eprom_address;
  name_device = read_String(addr);
  ESP_SERIAL.print("0x00,0x07,5,"+ip_broker+",#");
  delay(50);
  ESP_SERIAL.print("0x00,0x07,6,"+username_broker+",#");
  delay(50);
  ESP_SERIAL.print("0x00,0x07,7,"+password_broker+",#");
  delay(50);
  ESP_SERIAL.print("0x00,0x07,8,"+name_device+",#");
  delay(150);
  ESP_SERIAL.print("0x06,0x02,0,#");
  delay(50);

}


void call_list_net(){
    // Serial.println("on_call_list");
    ESP_SERIAL.print("1,0,0,0,#");
} 

void send_esp_bt(String dest, String svc, String pid, String value){
  String msg,buffer = "";
  ESP_SERIAL.print(dest+","+svc+","+pid+","+value+",#");

}

void send_esp_mqtt(String dest, String svc, String pid, String value){

}

void on_ser_comm(String line_in){
    Serial.print("on_ser_comm: ");
    Serial.println(line_in); 
    int i;
    // Serial.println("substring: "+line1.substring(0,1));
    if (line_in.substring(0,1)!="9"){
      split_msg_5(line_in);
      i = toHexc(retMsg5[1]);
      Serial.println("on_ser_comm: "+i);
    }else{
      split_msg_10(line_in);
      i = 9;
      Serial.print("on_ser_comm: == 9");
    }
    switch (i) {
        case 0:
          // Serial.println("esp- case 0"); 
          on_service_0x00(line_in);
          break;
        case 1:
          // Serial.println("esp - case 1");
          on_service_0x01(line_in);
          break;
        case 2:
          // Serial.println("esp - case 2");
          on_service_0x02(line_in);
          break;
        case 3:
          // Serial.println("esp - case 3");
          on_service_0x03(line_in);
          break;
        case 4:
          // Serial.println("esp - case 4");
          on_service_0x04(line_in);
          break; 
        case 5:
          // Serial.println("esp - case 5");
          on_service_0x05(line_in);
          break;  
        case 6:
          // Serial.println("esp - case 6");
          on_service_0x06(line_in);
          break;    
        case 7:
          // Serial.println("esp - case 7");
          on_service_0x07(line_in);
          break;    
        case 8:
          // Serial.println("esp - case 8"); 
          // service_0x08_ser(line_in);
          break;      
        case 9:
          // Serial.println("esp - case 9");
          on_service_0x09(line_in);
          break;    
    }    
}


void addlistNetworks() {
    // Serial.println("wifi - case 0: "+retMsg5[3]+" - "+ list_size+" - "+ ind_list_size);
    if (ind_list_size <= list_size){
      Ssid[0][ind_list_size] = retMsg5[2];
      Ssid[1][ind_list_size] = retMsg5[3];
      ind_list_size++;
    }
        // Serial.println("SSID: "+Ssid[0][ind_list_size-1]+" RSSI: "+Ssid[1][ind_list_size-1]); 
        // Serial.print(ind_list_size);
        // Serial.print("::::");
        // Serial.println(list_size);
    // }
}  

void listNetworks(){    
      delay(500);
      for (int i = 0; i<list_size; i++ ){
          // Serial.println("SSID: "+Ssid[0][i]+" RSSI: "+Ssid[1][i]);
          // HC05_SERIAL.println("SSID: "+Ssid[0][i]+" RSSI: "+Ssid[1][i]); 
      }
      // HC05_SERIAL.println("4,1,0,0,#");
      // Serial.println("===================");
      // Serial.println("");
}





