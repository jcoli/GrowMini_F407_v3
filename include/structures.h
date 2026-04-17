/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#ifndef __STRUCTURES_H__
#define __STRUCTURES_H__

/* structures internal */

#include <Arduino.h>

typedef struct _var_grow var_grow; 
struct _var_grow
{
    int pid;
    uint8_t service; 
    uint8_t device;
    uint16_t eprom_address;
    uint16_t eprom_size;
    float value;
    float oldValue;
    float* var_float;
    int* var_int;
    bool* var_bool;
    int relay_red;
    String* var_string;
    String eprom_val;
    String stringValue;
    String var_name;
    String mqtt_name;
    String descr;
    String type;
    String unity;    
    String desc_por;
    String desc_eng;
    String desc_esp;
};

typedef struct _life_bit life_bit;
struct _life_bit
{
    int ind;
    int can_id_remote;
    bool ackReceived;
    int network;
    unsigned long timeoutInterval;

};

#define MAX_OUT_ANA 


#endif