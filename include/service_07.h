/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>

#ifndef __service_07_H__
#define __service_07_H__

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

void com_0x07_0xFF(String command);


#endif