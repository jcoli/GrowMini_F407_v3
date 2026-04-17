/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#ifndef __IO_DEFINES_H__
#define __IO_DEFINES_H__

//Serial BlueTooth
#define TX_BT       PA2 //check
#define RX_BT       PA3 //check

//I2C display
#define SDA1        PB11 //check
#define SCL1        PB10 //check

//CAN
//STM32_CAN Can( CAN1, ALT );  //Use PB8/9 pins for CAN1.
#define CAN_RX      PB8 //check
#define CAN_TX      PB9 //check

#define BT_POWER    PC2 //check
#define HT_POWER    PC0 //check

// EPROM WINBOND W25Q16BV
#define EP_CS       PA15 //check
#define EP_DO       PB4  //check
#define EP_DI       PB5  //check
#define EP_CLK      PB3 //check

//Leds
#define LED_PIN     PA1 //check
#define LED_ALARM   PC3 //check
#define BUZZER_PIN  PC1 //check

// #define LED_FAN     PC5 // running
// #define LED_HUM     PC4 // running
// #define LED_LIGHT   PA7 // running 

//Sensor Analogic
#define SOIL_HUM_1  PA4     //check
#define SOIL_HUM_2  PA5     //check
// #define SOIL_HUM_3  PA2     //ana
// #define SOIL_HUM_4  PA3     //ana

//Sensor Digital
#define LV_L_IRR    PE2    //check
#define LV_L_HUM    PE1    //check
#define LV_LL_IRR   PE3   //check
#define LV_H_HUM    PE0  //check

// //Sensor 1-wire
#define INT_DHT     PC6     //check
#define EXT_DHT     PC7     //check

//Output
#define FAN01       PE11    //check
#define FAN02       PE13    //check
#define FAN03       PE14    //check
#define LIGHTS      PE9     //check
#define PUMP1       PD5     //check
#define PUMP2       PD4     //check
#define HUM         PD3     //check
#define DEHUM       PD10    //check

//Relay output 
#define RELAY1      PD6     //check
#define RELAY2      PD7     //check
#define RELAY3      PD8     //check
#define RELAY4      PD9     //check
// #define RELAY5      PC11   //Relay
// #define RELAY6      PA12   //Relay



//buttons 
#define BD_0       PE4      //check

#endif