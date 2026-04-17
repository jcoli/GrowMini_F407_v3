/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#ifndef __DEFINES_H__
#define __DEFINES_H__

#define TIME_OUT 8000000
#define TIMER_SLEEP 600000
#define TIMER_ANALOG 30000
#define TIMER_WATCHDOG 60000
#define TIMER_FIRST 40000 
#define TIMER_LED 2000
#define TIMER_SCHEDULE 30000

#define V03_MAX 3.6
#define V05_MAX 5.5
#define V12_MAX 14.5
#define V24_MAX 28.0

#define ESP_SERIAL Serial2

#define NUM_BUTTONS 1

#define LL_ADC_RESOLUTION LL_ADC_RESOLUTION_12B
#define ADC_RANGE 4096

static const char version[] = "2.0a";
static const char develop[] =  "jcoli-Tecnocoli";
static const char email_develop[] = "jcoli@tecnocoli.com.br";
static const char processor[] = "STM32F412CE";

#define CANID 0x31F

#define CANID_MASTER    0x310 
#define CANID_SENSOR    0x31F
#define CANID_LIGHTS    0X32A
#define CANID_OUTPUT    0X33A
#define CANID_IRRIG     0X34A
#define CANID_WIFI_BT   0X35A
#define CANID_WIFI      0X36A
#define CANID_BT        0X37A

#define SERVICE_0X01    0X004000
#define SERVICE_0X02    0X000
#define SERVICE_0X03    0X000
#define SERVICE_0X04    0X003000
#define SERVICE_0X05    0X005000
#define SERVICE_0X06    0X000
#define SERVICE_0X07    0X001000
#define SERVICE_0X08    0X000
#define SERVICE_0X09    0X006000
#define SERVICE_0X0A    0X007000

#define DEBUG_FLASH     true

#endif