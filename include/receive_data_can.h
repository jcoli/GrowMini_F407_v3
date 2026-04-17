/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>

#ifndef __RECEIVE_DATA_CAN_H__
#define __RECEIVE_DATA_CAN_H__

void receive_can(int rxId, int service,  byte rec_data[8]);
void service_0x01_can(byte rec_data[8]);
void service_0x02_can(byte rec_data[8]);
void service_0x03_can(byte rec_data[8]);
void service_0x04_can(byte rec_data[8]);
void service_0x05_can(byte rec_data[8]);



#endif