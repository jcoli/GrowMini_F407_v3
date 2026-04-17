/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
// #include <Adafruit_SSD1306.h>
#include <Adafruit_SH1106.h>
#include <STM32RTC.h>


#include "io_defines.h"
#include "icons.h"

void show_display_rtc();

extern uint32_t subSec;
extern byte seconds;
extern byte minutes;
extern byte hours;
extern byte weekDay ;
extern byte day;
extern byte month;
extern byte year;

extern float celsius;
extern int pwm1;
extern int pwm2;
extern int spValue;
extern int program_cycle;

extern float temp_int;
extern float temp_ext;
extern float hum_int;
extern float hum_ext;
extern float soil_1_hum;
extern float light_1_int;

extern bool level_irrig_l;
extern bool level_hum_l;

extern bool light_on;
extern bool pump_irr_on;

extern bool relay_1_on;
extern bool relay_2_on;

extern bool fan1_inf_on;
extern bool fan2_inf_on;

extern int fan1_inf_pwm;
extern int fan2_inf_pwm;
extern int light_pwm;

extern STM32RTC& rtc;

extern Adafruit_SH1106 display;


void show_display_rtc(){
    // Serial.println("show_display_rtc");
    rtc.getDate(&weekDay, &day, &month, &year);
    rtc.getTime(&hours, &minutes, &seconds, &subSec);
    display.clearDisplay();
    display.setTextColor(WHITE);
    display.setCursor(15, 10);
    display.setTextSize(2);
    display.setTextColor(WHITE);
    // Serial.println("show_display_rtc 1");
    display.printf("%02d/%02d/%02d ", day, month, year);
    // Serial.println("show_display_rtc 1a");
    display.setCursor(30, 40);
    // Serial.println("show_display_rtc 1b");
    display.printf("%02d:%02d", hours, minutes);
    // Serial.println("show_display_rtc 1c");
    display.display(); 
    // Serial.println("show_display_rtc 2");
}
