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
// #include "receive_data_can.h"
#include "structures.h"

void can_begin(); 
void can_read();
void can_write(uint16_t  canTXId, int frame_type, int data_lenght, byte send_data[8]);
void sendValuesFloat(int  destId,  int service,int pid, float sensorValue);
void sendValuesBoolean(int  destId,  int service,int pid, uint8_t sensorValue);

STM32_CAN Can( CAN1, ALT);
// STM32_CAN Can( CAN1, DEF );  //Use PA11/12 pins for CAN1.
//STM32_CAN Can( CAN1, ALT );  //Use PB8/9 pins for CAN1.
//STM32_CAN Can( CAN1, ALT_2 );  //Use PD0/1 pins for CAN1.
//STM32_CAN Can( CAN2, DEF );  //Use PB12/13 pins for CAN2.
//STM32_CAN Can( CAN2, ALT );  //Use PB5/6 pins for CAN2
//STM32_CAN Can( CAN3, DEF );  //Use PA8/15 pins for CAN3.
//STM32_CAN Can( CAN3, ALT );  //Use PB3/4 pins for CAN3

static CAN_message_t CAN_RX_msg; 
static CAN_message_t CAN_TX_msg;

long unsigned int rxId; 
unsigned char len = 0;
unsigned char rxBuf[8];
char msgString[128];   
byte data[8] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07};  

void can_begin(){
   Serial.println("CAN BEGIN");  
   Can.begin();
   Can.setBaudRate(500000);  //250KBPS
   Can.enableFIFO(); 
   Can.enableMBInterrupts();
   Serial.println("CAN BEGIN 1");    
}

void can_read(){
    // Serial.println("Can read 1");
    if (Can.read(CAN_RX_msg) ) {
      int my_id= CAN_RX_msg.id;   
      if (my_id == CANID_MASTER){
        Serial.print("Can read: ");
        Serial.println(my_id, HEX);
        for (int i=0; i<8;i++){
          data[i] = CAN_RX_msg.buf[i];
        }
        // receive_can(my_id, CAN_RX_msg.buf[0], CAN_RX_msg.buf);
        Serial.println("Can read ");
      }
    }
}
    
void can_write(uint16_t canTXId, int frame_type, int data_lenght, byte send_data[8]){
    CAN_TX_msg.id = (canTXId);
    CAN_TX_msg.len = 8;
    CAN_TX_msg.buf[0] =  send_data[0];
    CAN_TX_msg.buf[1] =  send_data[1];
    CAN_TX_msg.buf[2] =  send_data[2];
    CAN_TX_msg.buf[3] =  send_data[3];
    CAN_TX_msg.buf[4] =  send_data[4];
    CAN_TX_msg.buf[5] =  send_data[5];
    CAN_TX_msg.buf[6] =  send_data[6];
    CAN_TX_msg.buf[7] =  send_data[7];
    if (Can.write(CAN_TX_msg)){
      // Serial.println("Write ok");
    }else{
      Serial.println("Write not ok");
    }
}

void sendValuesFloat(int destId,  int service,int pid, float sensorValue) {
    // Serial.print("Send Value Float ");
    uint16_t temp_can;
    temp_can = sensorValue;
    int lowByteCan;
    int highByteCan;
    lowByteCan = lowByte(temp_can);
    highByteCan = highByte(temp_can);
    unsigned char stmp[8] = {service, pid, lowByteCan, highByteCan, 0x00, 0x00, 0x00, 0x00};
    can_write(destId, 0, 8, stmp);
}

void sendValuesBoolean(int destId,  int service,int pid, uint8_t sensorValue) {
    // Serial.print("Send Value Boolean ");
    // Serial.print(service, HEX);
    // Serial.print(", ");
    // Serial.print(pid, HEX);
    // Serial.print(", ");
    // Serial.println(sensorValue, BIN);
    if (sensorValue){
      unsigned char stmp[8] = {service, pid, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
      // Serial.println("send 1");
      can_write(destId, 0, 8, stmp);  
    }else{
      unsigned char stmp[8] = {service, pid, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
      // Serial.println("send 0");
      can_write(destId, 0, 8, stmp);
    } 
}




