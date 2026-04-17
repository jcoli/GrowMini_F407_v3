/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>

#ifndef __SERVICE_04_ESP_H__
#define __SERVICE_04_ESP_H__

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
void com_0x04_0x09(String command);
void com_0x04_0x0A(String line_in);
void com_0x04_0x0B(String line_in);
void com_0x04_0x0C(String line_in);
void com_0x04_0x0D(String line_in);
void com_0x04_0x0E(String line_in);
void com_ser04_0x0F(String line_in);

#endif