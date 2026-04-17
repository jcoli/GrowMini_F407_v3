/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#ifndef __CAN_CONTROL_H__
#define __CAN_CONTROL_H__


void can_begin();
void can_read();
void can_write(uint16_t  canTXId, int frame_type, int data_lenght, byte send_data[8]);
void sendValuesFloat(int  destId,  int service,int pid, float sensorValue);
void sendValuesBoolean(int  destId,  int service,int pid, uint8_t sensorValue);



#endif