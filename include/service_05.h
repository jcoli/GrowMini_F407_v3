/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>

#ifndef __service_05_H__
#define __service_05_H__

void on_service_0x05(String line_in);
void com_0x05_0x00(float com_pwm);
void com_0x05_0x01(float com_pwm);
void com_0x05_0x02(float com_pwm);
void com_0x05_0x03(float com_pwm);


#endif