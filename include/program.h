/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "structures.h"

void program_begin();
void vpd_calculate();
void append_struct_life_bit();
bool eraseDataSetup();
void avg_calculate();
void hum_control();
void relay_1_control();
void relay_2_control();
void relay_3_control();
void relay_4_control();
void irrig_control();
void alarm_control();
void level_hum_control();



#endif