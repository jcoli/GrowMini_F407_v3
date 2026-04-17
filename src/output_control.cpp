/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>
#include <HardwareTimer.h>

#include "defines.h"
#include "io_defines.h"


void output_begin();
void pump_hum_off();
void pump_irr_off(); 


extern bool light_on;
extern bool pump_irr_on;

extern bool fan1_inf_on;
extern bool fan2_inf_on;

extern bool relay_1_on;
extern bool relay_2_on;

extern int fan1_inf_pwm;
extern int fan2_inf_pwm;
extern int light_pwm;

extern bool level_irrig_l;
extern bool level_hum_l;

extern bool zeroChangeDetect;
extern bool lastZeroState;
extern bool run_on;

extern bool pwm_bool;
extern int pwm1;

extern bool fan_dehum_on;
extern bool fan1_inf_on;
extern bool fan2_inf_on;
extern bool fan3_inf_on;
extern bool fan_hum_on;
extern bool light_on;
extern bool pump_irr_on;
extern bool pump_hum_on;
extern bool hum_1_on;

extern bool relay_1_on;
extern bool relay_2_on;
extern bool relay_3_on;
extern bool relay_4_on;
extern bool output_1_on;
extern bool output_2_on;

HardwareTimer *tim1 = new HardwareTimer(TIM1);

#define TIMER_INTERVAL_0_3S           300L
#define TIMER_INTERVAL_1S             1000L
#define TIMER_INTERVAL_1_5S           1500L
#define TIMER_INTERRUPT_DEBUG         0
#define TIMERINTERRUPT_LOGLEVEL_     0
#define TIMER_INTERVAL_MS         100
#define HW_TIMER_INTERVAL_MS      50


void output_begin(){
    Serial.println("Output Begin ");
    pinMode(RELAY1, OUTPUT);
    pinMode(RELAY2, OUTPUT);
    pinMode(RELAY3, OUTPUT);
    pinMode(RELAY4, OUTPUT);
    // pinMode(RELAY5, OUTPUT);
    // pinMode(RELAY6, OUTPUT);
    // pinMode(FAN01, PWM);
    // pinMode(FAN02, OUTPUT);
    // pinMode(LIGHTS, OUTPUT);
    
    pinMode(PUMP1, OUTPUT);
    pinMode(PUMP2, OUTPUT);
    pinMode(HUM, OUTPUT);
    pinMode(BT_POWER, OUTPUT);
    pinMode(HT_POWER, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(LED_ALARM , OUTPUT);
    
    digitalWrite(RELAY1, LOW); 
    digitalWrite(RELAY2, LOW);
    digitalWrite(RELAY3, LOW); 
    digitalWrite(RELAY4, LOW);
    digitalWrite(PUMP1, LOW);
    digitalWrite(PUMP2, LOW);
    digitalWrite(HUM, LOW);
    digitalWrite(BT_POWER, HIGH);
    digitalWrite(HT_POWER, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    digitalWrite(LED_ALARM, HIGH);
    
    tim1->setPWM(1, LIGHTS, 10000, 0);
    tim1->setPWM(2, FAN01, 10000, 0);
    tim1->setPWM(3, FAN02, 10000, 0);
    
}
 
void pump_hum_off(){
    Serial.println("hum level off 2");
    digitalWrite(PUMP2, LOW);
    pump_hum_on = false;
}

void pump_irr_off(){
    Serial.println("Pump 1 off 4");
    digitalWrite(PUMP1, LOW);
}

// 
