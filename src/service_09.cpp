/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#include <Arduino.h>
#include <STM32RTC.h>

#include "eprom.h"
#include "defines.h"
#include "io_defines.h"
#include "display.h"
#include "structures.h"
#include "defines_protocol.h"
#include "tools.h" 
#include "program.h"
#include "comm_esp.h"



void on_service_0x09(String line_in);
void com_0x09_0x00(String line_in);
void com_0x09_0x01(String line_in);
void com_0x09_0x02(String line_in);
void com_0x09_0x03(String line_in);
void com_0x09_0x09(String line_in);
void sendAck(int ackValue);
void sendPong();
void setup_rtc(String msg);

void save_on_flash_serv5();

extern unsigned long loopDelay_live;
extern unsigned long loopDelay_ack;

extern uint32_t subSec;
extern byte seconds;
extern byte minutes;
extern byte hours; 
extern byte weekDay;
extern byte day;
extern byte month;
extern byte year;

extern bool first_run;

extern bool wifi_connected;
extern bool mqtt_connected;
extern bool bt_connected;
extern bool pauseSensorSends;

extern STM32RTC& rtc;

extern String retMsg5[5];
extern String retMsg10[10];

void on_service_0x09(String line_in){
    // Serial.println("on service 5");
    // int i;
    
    // if (line_in.substring(0,1)!="9"){
    //   split_msg_5(line_in);
    //   i = toHexc(retMsg5[1]);
    //   // Serial.println("on_ser_comm: "+i);
    // }else{
    //   split_msg_10(line_in);
    //   i = 9;
    //   // Serial.print("on_ser_comm: == 7");
    // }
    split_msg_5(line_in);
    int i = toHexc(retMsg5[2]);
    // Serial.println("");
    switch (i) {
        case 0x00:
            Serial.println("com_0x09_0x00");
            com_0x09_0x00(line_in);
            break;
        case 0x01:
            Serial.println("com_0x09_0x01");
            com_0x09_0x01(line_in);
            break;       
         case 0x02:
            Serial.println("com_0x09_0x02");
            com_0x09_0x02(line_in);
            break;           
        case 0x03:
            Serial.println("com_0x09_0x03 ");
            com_0x09_0x03(line_in);
            break;
        case 0x09:
            Serial.println("com_0x09_0x09 ");
            com_0x09_0x09(line_in);
            break;    
    }
}


void com_0x09_0x00(String line_in){
    
}

void com_0x09_0x01(String line_in){
    
    // HANDSHAKE: Start/End transmission
    if (retMsg5[3] == "1") {
        Serial.println("🔒 Handshake: START - pausando sensores");
        pauseSensorSends = true;
        sendAck(1);  
    } else if (retMsg5[3] == "0") {
        Serial.println("🔓 Handshake: END - retomando sensores");
        pauseSensorSends = false;
        sendAck(0);  
    }
    
    
}

void com_0x09_0x02(String line_in){
        
}

void com_0x09_0x03(String line_in){
    sendPong();
 
}

void com_0x09_0x09(String line_in){
    setup_rtc(line_in);
    Serial.println("SETUP RTC");
}

void sendAck(int ackValue) {
    // ✅ Ecoar o valor: START=1→ACK=1, END=0→ACK=0
    String msg = "1,0x09,0x02," + String(ackValue) + ",#";
    loopDelay_ack = millis();
    send_esp_bt("1","0x09","0x02",String(ackValue));
    Serial.println("📤 ACK_" + String(ackValue ? "START" : "END") + " enviado: " + msg);
}

void sendPong() {
    String msg = "1,0x09,0x03,1,#";
    // txChar->setValue(msg.c_str());
    // txChar->notify();
    loopDelay_live = millis();
    send_esp_bt("1","0x09","0x03","1");
    Serial.println("📤 PONG enviado: " + msg);
}

void setup_rtc(String msg){
  split_msg_10(msg); 
  Serial.println("setup rtc");
  Serial.println(retMsg10[3]);
  Serial.println(retMsg10[4]);
  Serial.println(retMsg10[5]);
  Serial.println(retMsg10[6]);
  Serial.println(retMsg10[7]);
  Serial.println(retMsg10[8]);

  rtc.setHours(retMsg10[6].toInt());
  rtc.setMinutes(retMsg10[7].toInt());
  rtc.setSeconds(retMsg10[8].toInt());
  rtc.setWeekDay(retMsg10[2].toInt());
  rtc.setDay(retMsg10[5].toInt());
  rtc.setMonth(retMsg10[4].toInt());
  rtc.setYear(retMsg10[3].toInt()-2000); 

  rtc.getDate(&weekDay, &day, &month, &year);
  rtc.getTime(&hours, &minutes, &seconds, &subSec);
//   Serial.printf("%02d/%02d/%02d ", day, month, year);
//   Serial.printf("%02d:%02d\n", hours, minutes);
}