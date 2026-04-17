/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>
#include <Bounce2.h>


#include "display.h"
#include "defines.h"
#include "io_defines.h"
#include "tools.h"
#include "program.h" 


void buttons_begin();
void checkPosition();
void check_button();

// RotaryEncoder encoder1(ENC1_CLK, ENC1_DT, RotaryEncoder::LatchMode::TWO03);
// RotaryEncoder encoder2(ENC2_CLK, ENC2_DT, RotaryEncoder::LatchMode::TWO03);

const uint8_t BUTTON_PINS[NUM_BUTTONS] = {BD_0};
Bounce * buttons = new Bounce[NUM_BUTTONS];

extern bool ch_page;
extern bool ch_page_ana;
extern int tft_page;
extern int tft_page_ant;
extern int tft_sub_page;
extern int tft_sub_page_ant;

void buttons_begin(){
    for (int i = 0; i < NUM_BUTTONS; i++) {
      buttons[i].attach( BUTTON_PINS[i] , INPUT_PULLUP  );       //setup the bounce instance for the current button
      buttons[i].interval(55);              // interval in ms
    }
    // attachInterrupt(digitalPinToInterrupt(ENC1_DT), checkPosition, CHANGE);
    // attachInterrupt(digitalPinToInterrupt(ENC1_CLK), checkPosition, CHANGE);
    // // attachInterrupt(digitalPinToInterrupt(ENC2_DT), checkPosition, CHANGE);
    // // attachInterrupt(digitalPinToInterrupt(ENC2_CLK), checkPosition, CHANGE);
}

void checkPosition(){
  // // Serial.println("checkPosition");
  // encoder1.tick();
  // // encoder2.tick(); 
  // check_button();
} 

void check_button(){


    for (int i = 0; i < NUM_BUTTONS; i++)  {
    buttons[i].update();
    if ( buttons[i].fell() ) {
      switch (i) {
        case 0:
          tft_page++;
          if (tft_page>1) tft_page=1;
          
          // Serial.println("button0");
          break;
        case 1:
          tft_page--;
          if (tft_page<0) tft_page=0;
          
          // Serial.println("button1");
          break;
        case 2:
          // Serial.println("button2");
          //<<
          break;
        case 3:
          // Serial.println("button3");
          //||
          break;
        case 4:
          // Serial.println("button4");
          //>>
          break;
        case 5:
          // Serial.println("button5");
          //center
          break;  
        case 6:
          // Serial.println("button6");
          //^^
          break;
  
      }
      
      
    } 
  }        


}
