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


void display_begin();
void show_display_1();
void show_display_2(); 
void drawLogo();
void scan_i2c();

#define OLED_RESET -1  


#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels


Adafruit_SH1106 display( OLED_RESET);

#define LOGO_HEIGHT   64
#define LOGO_WIDTH    128

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



void display_begin(){
    Serial.println("start display");
    Wire.setSDA(SDA1);
    Wire.setSCL(SCL1);
    Wire.begin();

    display.begin(SH1106_SWITCHCAPVCC, 0x3c);
    display.setRotation(4);
    // display.invertDisplay(false);
    display.clearDisplay();
    display.display();
    display.setTextSize(2); 
    display.setTextColor(WHITE);
    display.setCursor(0, 10);
    // Display static text
    
    display.setCursor(30, 10);
    display.print("Green");
    display.setCursor(20, 40);
    display.print("Tomato!");
    display.display();
    delay(3000);
    // display.invertDisplay(false);

    // delay(2000);
    drawLogo();
    
    Serial.println("finish display");
        

}

// void show_display_rtc(){
//     Serial.println("show_display_rtc");
//     // rtc.getDate(&weekDay, &day, &month, &year);
//     // rtc.getTime(&hours, &minutes, &seconds, &subSec);
//     display.clearDisplay();
//     // display.setTextColor(WHITE);
//     // display.setCursor(15, 10);
//     // display.setTextSize(2);
//     display.setTextColor(WHITE);
//         display.setCursor(25, 0);
//         display.setTextSize(2);
//         display.print("Temp");
//     Serial.println("show_display_rtc 1");
//     // // display.printf("%02d/%02d/%02d ", day, month, year);
//     // Serial.println("show_display_rtc 1a");
//     // display.setCursor(30, 40);
//     // Serial.println("show_display_rtc 1b");
//     // // display.printf("%02d:%02d", hours, minutes);
//     Serial.println("show_display_rtc 1c");
//     display.display(); 
//     Serial.println("show_display_rtc 2");
// }



void show_display_1(){
        display.clearDisplay();
        display.setTextColor(WHITE);
        display.setCursor(25, 0);
        display.setTextSize(2);
        display.print("Temp");
        display.setCursor(85, 0);
        display.print("Hum");
        display.setCursor(0, 20);
        display.print("I");
        display.setCursor(0, 40);
        display.print("E");

        display.setCursor(22, 20);
        display.print(temp_int,1);
        display.setCursor(22, 40);
        display.print(temp_ext,1);

        display.setCursor(80, 20);
        display.print(hum_int,1);
        display.setCursor(80, 40);
        display.print(hum_ext,1);

        display.display(); 
}

void show_display_2(){
        int y = 0;
        int d_y=9;
        display.clearDisplay();
        display.setTextColor(WHITE);
        display.setCursor(0, y);
        display.setTextSize(1);
        display.print("Temp In:");
        display.setCursor(53, y);
        display.print(temp_int,0);
        display.setCursor(82, y);
        display.print("Ex:");
        display.setCursor(108, y);
        display.print(temp_ext,0);

        y=y+d_y;

        display.setCursor(0, y);
        display.print("Hum In:");
        display.setCursor(53, y);
        display.print(hum_int,0);
        display.setCursor(82, y);
        display.print("Ex:");
        display.setCursor(108, y);
        display.print(hum_ext,0);

        y=y+d_y;

        display.setCursor(0, y);
        display.print("Soil Hum:");
        display.setCursor(53, y);
        display.print(soil_1_hum,0);
        display.setCursor(82, y);
        display.print("Pump:");
        display.setCursor(108, y);
        if (pump_irr_on){
            display.print("ON");                
        }else{
            display.print("OFF");
        }

        y=y+d_y;

        display.setCursor(0, y);
        display.print("Fan 1:");
        display.setCursor(53, y);
        if (fan1_inf_on){
            display.print("ON");                
        }else{
            display.print("OFF");
        }
        display.setCursor(82, y);
        display.print("PWM:");
        display.setCursor(108, y);
        display.print(fan1_inf_pwm);

        y=y+d_y;

        display.setCursor(0, y);
        display.print("Fan 2:");
        display.setCursor(53, y);
        if (fan2_inf_on){
            display.print("ON");                
        }else{
            display.print("OFF");
        }
        display.setCursor(82, y);
        display.print("PWM:");
        display.setCursor(108, y);
        display.print(fan2_inf_pwm);

        y-y+d_y;        

        // display.setCursor(0, y);
        // display.print("Fan 3:");
        // display.setCursor(53, y);
        // if (fan2_inf_on){
        //     display.print("ON");                
        // }else{
        //     display.print("OFF");
        // }
        // display.setCursor(82, y);
        // display.print("PWM:");
        // display.setCursor(104, y);
        // display.print(fan3_inf_pwm);

        y=y+d_y;

        display.setCursor(0, y);
        display.print("Light:");
        display.setCursor(53, y);
        if (light_on){
            display.print("ON");                
        }else{
            display.print("OFF");
        }
        display.setCursor(82, y);
        display.print("PWM:");
        display.setCursor(108, y);
        display.print(light_pwm);

        y=y+d_y;

        display.setCursor(0, y);
        display.print("Relay 1:");
        display.setCursor(53, y);
        if (relay_1_on){
            display.print("ON");                
        }else{
            display.print("OFF");
        }
        display.setCursor(82, y);
        display.print("2:");
        display.setCursor(108, y);
        if (relay_2_on){
            display.print("ON");               
        }else{
            display.print("OFF");
        }


        display.display(); 
}

void drawLogo() {
    display.clearDisplay();

    display.drawBitmap(
    (display.width()  - LOGO_WIDTH ) / 2,
    (display.height() - LOGO_HEIGHT) / 2,
    GrowTomato_white_pcb, LOGO_WIDTH, LOGO_HEIGHT, 1);
    display.display();
  
}

void scan_i2c(){
    byte error, address;  
    int nDevices;

    Serial.println("Scanning...");

    nDevices = 0;
    for(address = 1; address < 127; address++) {
        // The i2c_scanner uses the return value of
        // the Write.endTransmisstion to see if
        // a device did acknowledge to the address.

        Wire.beginTransmission(address);
        error = Wire.endTransmission();

        if (error == 0) {
        Serial.print("I2C device found at address 0x");
        if (address < 16)
            Serial.print("0");
        Serial.println(address, HEX);

        nDevices++;
        }
        else if (error == 4) {
        Serial.print("Unknown error at address 0x");
        if (address < 16)
            Serial.print("0");
        Serial.println(address, HEX);
        }
    }
    if (nDevices == 0){
        Serial.println("No I2C devices found");
    }else{
        Serial.println("done");
    }
    // delay(5000);           // wait 5 seconds for next scan
    //     digitalWrite(PB2, !digitalRead(PB2));
    
}


