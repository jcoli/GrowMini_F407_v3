/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>

#ifndef __service_09_H__
#define __service_09_H__

void on_service_0x09(String line_in);
void com_0x09_0x00(String line_in);
void com_0x09_0x01(String line_in);
void com_0x09_0x02(String line_in);
void com_0x09_0x03(String line_in);
void com_0x09_0x09(String line_in);
void sendAck(int ackValue);
void sendPong();
void setup_rtc(String msg);

#endif