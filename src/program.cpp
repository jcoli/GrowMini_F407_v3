/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#include <Arduino.h>

#include "eprom.h"
#include "defines.h"
#include "tools.h"
#include "structures.h"
#include "io_defines.h"
#include "output_control.h"

void program_begin();
void vpd_calculate();
void append_struct_life_bit(); 
bool eraseDataSetup();
void avg_calculate();
void send_bool_command(int ind);
void send_float_command(int ind);
void hum_control();
void relay_1_control();
void relay_2_control();
void relay_3_control();
void relay_4_control();
void irrig_control();
void alarm_control();
void level_hum_control();


extern byte minutes;
extern byte hours;
extern byte weekDay ;
extern byte day;
extern byte month;
extern byte year;

extern unsigned long loopDelay_pump;
extern unsigned long loopDelay_hum_pump;


extern byte lastMinutes;
extern byte lastHours;
extern byte lastWeekDay ;
extern byte lastDay;
extern byte lastMonth;
extern byte lastYear;

extern float eco2_ext;
extern float eco2_int;
extern float temp_ext;
extern float hum_ext;
extern float temp_ext;
extern float temp_int;
extern float hum_int;
extern float soil_1_hum;
extern float soil_2_hum;
extern float soil_3_hum;
extern float soil_4_hum;
extern float light_1_int;

extern bool level_irrig_l; 
extern bool level_hum_l;
extern bool level_hum_h;
extern bool level_irrig_ll;

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

extern bool soil_hum_dig;

extern bool door;
extern bool wifi_connected;
extern bool mqtt_connected;
extern bool bt_connected;

extern int fan1_inf_pwm;
extern int fan2_inf_pwm;
extern int light_pwm;
extern int hum_1_pwm;


extern float VRef;
extern float intTemp;

extern bool first_run;
extern bool scheduleRun;
extern bool alarm_on;


extern float actual_vpd;
extern float avg_vpd_int;
extern float sum_vpd_int;

extern float avg_temp_int;
extern float sum_temp_int;

extern float avg_hum_int;
extern float sum_hum_int;

extern int temp_int_min_stp;
extern int temp_int_max_stp;
extern int hum_int_on_stp;
extern int hum_int_on_light_stp;
extern int hum_int_min_stp;
extern int hum_int_max_stp;
extern int vpd_int_min_stp;
extern int vpd_int_max_stp;
extern int soil_hum_min_stp;
extern int soil_hum_max_stp;
extern int ph_irrig_stp;
extern int ph_hum_stp;
extern int light_hr_on_stp;
extern int light_min_on_stp;
extern int light_hr_off_stp;
extern int light_min_off_stp;
extern int pump_irr_on_stp;
extern int pump_hr_irr_on_stp;
extern int pump_min_irr_on_stp;
extern int pump_hr_irr_off_stp;
extern int pump_min_irr_off_stp;
extern int irr_interval_stp;
extern int irr_time_stp;
extern int irr_interval_on_stp;
extern int irr_1_hr_stp;
extern int irr_1_min_stp;
extern int irr_2_hr_stp;
extern int irr_2_min_stp;
extern int irr_3_hr_stp;
extern int irr_3_min_stp;
extern int irr_4_hr_stp;
extern int irr_4_min_stp;
extern int irr_5_hr_stp;
extern int irr_5_min_stp;
extern int irr_6_hr_stp;
extern int irr_6_min_stp;
extern int light_pwm_stp;
extern int fan1_inf_pwm_stp;
extern int fan2_inf_pwm_stp;
extern int fan1_inf_pwm_light_stp;
extern int fan2_inf_pwm_light_stp;

extern int relay_1_red_stp;
extern int relay_2_red_stp;
extern int relay_3_red_stp;
extern int relay_4_red_stp;

extern HardwareTimer *tim1;

extern var_grow var_grow_1[60];
extern var_grow var_grow_2[10];
extern var_grow var_grow_3[10];
extern var_grow var_grow_4[10];
extern var_grow var_grow_5[10];
extern var_grow var_grow_6[10];
extern var_grow var_grow_7[10];
extern var_grow var_grow_8[10];
extern var_grow var_grow_9[10];
extern var_grow var_grow_A[10];

bool eraseDataSetup(){
    uint16_t addr = var_grow_4[0].eprom_address;
    eraseSector(addr);
    return true;
}




void program_begin(){
   
    uint16_t addr;
    uint8_t data = 0;
    uint32_t data_int = 0;
    // sendValuesFloat(CANID_OUTPUT , 0x05, 0x01, 100);
    // sendValuesFloat(CANID_OUTPUT , 0x05, 0x02, 100);
     for (int i = 0; i <= 6; i++){ 
        addr = var_grow_4[i].eprom_address;
        uint8_t data = read_Byte(addr);
        *var_grow_4[i].var_bool = data;
        send_bool_command(i);
        // Serial.print("Program ON/OFF ");
        // Serial.print(var_grow_4[i].descr);
        // Serial.print(", ");
        // Serial.print(addr);
        // Serial.print(", ");
        // Serial.println(data, BIN);
        send_bool_command(i);
    }  
    for (int i = 0; i <= 2; i++){
        addr = var_grow_5[i].eprom_address;
        data_int = read_long(addr);
        *var_grow_5[i].var_int = data_int;
        // Serial.print("Program PWM ");
        // Serial.print(var_grow_5[i].descr);
        // Serial.print(", ");
        // Serial.print(addr);
        // Serial.print(", ");
        // Serial.println(data_int);
        send_float_command(i);
        // Serial.print(" - ");
        // Serial.print(var_grow_5[i].service, HEX);
        // Serial.print(" - ");
        // Serial.print(var_grow_5[i].pid, HEX);
        // Serial.print(" - ");
        // Serial.println(*var_grow_5[i].var_int);
    }
   
    
    scheduleRun = true;  
    // sendValuesBoolean(CANID_OUTPUT , 0x04, 0x02, ret);
}



void hum_control(){
    // Serial.println("hum control");
    if (hum_int_min_stp>hum_int){
        hum_1_on = true;
        Serial.println("hum control on");
    }
    if (hum_int_max_stp<hum_int){
        hum_1_on = false;
        // Serial.println("hum control off 1");
    }
    if (!level_hum_l){
        hum_1_on = false;
        // Serial.println("hum control off 2");
    }
    if (hum_1_on){
        digitalWrite(HUM, HIGH); 
        Serial.println("digitalWrite(HUM, HIGH)");   
    }else{
        digitalWrite(HUM, LOW);
    }
    
}

void irrig_control(){
    Serial.println("irrig control");
    if (soil_hum_min_stp>soil_1_hum){
        pump_irr_on = true;
        Serial.println("irrig control on");
    }
    if (level_irrig_ll){
        pump_irr_on = false;
        // Serial.println("irrig control off");
    }
    if (pump_irr_on){
        digitalWrite(PUMP1, HIGH); 
        loopDelay_pump = millis();   
    }else{
        digitalWrite(PUMP1, LOW);
    }
    
    
    
}

void level_hum_control(){
    // Serial.println("hum level control");
    if (!level_hum_l){
        pump_hum_on = true;
        Serial.println("hum level L on");
        // attachInterrupt(digitalPinToInterrupt(LV_H_HUM), pump_hum_off, RISING);
    }
    if (level_hum_h){
        pump_hum_on = false;
        // Serial.println("hum level off");
        // detachInterrupt(digitalPinToInterrupt(LV_H_HUM));
    }else{
        pump_hum_on = true;
        Serial.println("hum level H on");
    }
    if ((pump_hum_on) && (level_irrig_ll)){
        Serial.println("+++++++++++++++++++++++++++++++++++++++++++==");
        Serial.println("digitalWrite(PUMP2, HIGH);");
        digitalWrite(PUMP2, HIGH);    
        loopDelay_hum_pump = millis();
        Serial.println("+++++++++++++++++++++++++++++++++++++++++++==");
    }else{
        // Serial.println("hum level off 1");
        digitalWrite(PUMP2, LOW);
    }
    

}



void alarm_control(){
    // Serial.println("alarm control");
    if ((!level_hum_l) || (!level_irrig_l) || (!level_irrig_ll) ){
        alarm_on = true;
        // Serial.println("alarm control on");
    }else{
        alarm_on = false;
        // Serial.println("alarm control off");
    }
    if (alarm_on){
        digitalWrite(LED_ALARM, HIGH);    
    }else{
        digitalWrite(LED_ALARM, LOW);
    }
}

void relay_1_control(){
    // Serial.println("Relay Control 1");
    if (relay_1_red_stp == 1){
        if ((fan1_inf_pwm>0) && (fan1_inf_on)){
            relay_1_on = true;
        }else{
            relay_1_on = false;
        }
    }else if (relay_1_red_stp == 2){
        if ((fan2_inf_pwm>0) && (fan2_inf_on)){
            relay_1_on = true;
        }else{
            relay_1_on = false;
        }
    }else if (relay_1_red_stp == 3){
        if ((light_pwm>0) && (light_on)){
            relay_1_on = true;
        }else{
            relay_1_on = false;
        }
    }else if (relay_1_red_stp == 4){
        if (pump_irr_on){
            relay_1_on = true;
        }else{
            relay_1_on = false;
        }
    }else if (relay_1_red_stp == 5){
        if (hum_1_on){
            relay_1_on = true;
        }else{
            relay_1_on = false;
        }
    }
    // Serial.print("Relay 1: ");
    // Serial.println(relay_1_on);
    digitalWrite(RELAY1, relay_1_on);

}

void relay_2_control(){
    if (relay_2_red_stp == 1){
        if ((fan1_inf_pwm>0) && (fan1_inf_on)){
            relay_2_on = true;
        }else{
            relay_2_on = false;
        }
    }else if (relay_2_red_stp == 2){
        if ((fan2_inf_pwm>0) && (fan2_inf_on)){
            relay_2_on = true;
        }else{
            relay_2_on = false;
        }
    }else if (relay_2_red_stp == 3){
        if ((light_pwm>0) && (light_on)){
            relay_2_on = true;
        }else{
            relay_2_on = false;
        }
    }else if (relay_2_red_stp == 4){
        if (pump_irr_on){
            relay_2_on = true;
        }else{
            relay_2_on = false;
        }
    }else if (relay_2_red_stp == 5){
        if (hum_1_on){
            relay_2_on = true;
        }else{
            relay_2_on = false;
        }
    }
    digitalWrite(RELAY2, relay_2_on);
}

void relay_3_control(){
    if (relay_3_red_stp == 1){
        if ((fan1_inf_pwm>0) && (fan1_inf_on)){
            relay_3_on = true;
        }else{
            relay_3_on = false;
        }
    }else if (relay_1_red_stp == 2){
        if ((fan2_inf_pwm>0) && (fan2_inf_on)){
            relay_3_on = true;
        }else{
            relay_3_on = false;
        }
    }else if (relay_3_red_stp == 3){
        if ((light_pwm>0) && (light_on)){
            relay_3_on = true;
        }else{
            relay_3_on = false;
        }
    }else if (relay_3_red_stp == 4){
        if (pump_irr_on){
            relay_3_on = true;
        }else{
            relay_3_on = false;
        }
    }else if (relay_3_red_stp == 5){
        if (hum_1_on){
            relay_3_on = true;
        }else{
            relay_3_on = false;
        }
    }
    digitalWrite(RELAY3, relay_3_on);
}

void relay_4_control(){
    if (relay_4_red_stp == 1){
        if ((fan1_inf_pwm>0) && (fan1_inf_on)){
            relay_4_on = true;
        }else{
            relay_4_on = false;
        }
    }else if (relay_4_red_stp == 2){
        if ((fan2_inf_pwm>0) && (fan2_inf_on)){
            relay_4_on = true;
        }else{
            relay_4_on = false;
        }
    }else if (relay_4_red_stp == 3){
        if ((light_pwm>0) && (light_on)){
            relay_4_on = true;
        }else{
            relay_4_on = false;
        }
    }else if (relay_4_red_stp == 4){
        if (pump_irr_on){
            relay_4_on = true;
        }else{
            relay_4_on = false;
        }
    }else if (relay_4_red_stp == 5){
        if (hum_1_on){
            relay_4_on = true;
        }else{
            relay_4_on = false;
        }
    }
    digitalWrite(RELAY4, relay_4_on);
}

void send_bool_command(int ind){
    switch (ind) {
        case 4:
            digitalWrite(HUM, hum_1_on);     
            break;
        case 5:
            digitalWrite(RELAY1, relay_1_on);         
            break;  
        case 6:
            digitalWrite(RELAY2, relay_2_on);        
            break;         

    }
}

void send_float_command(int ind){
    switch (ind) {
        case 0:
            tim1->setCaptureCompare(1, *var_grow_5[ind].var_int, PERCENT_COMPARE_FORMAT);
            break;
        case 1:
            tim1->setCaptureCompare(2, *var_grow_5[ind].var_int, PERCENT_COMPARE_FORMAT);
            break; 
        case 2:
            tim1->setCaptureCompare(3, *var_grow_5[ind].var_int, PERCENT_COMPARE_FORMAT);
            break;           
    }
    
}

void avg_calculate(){
     if ((hum_int>0) && (temp_int>0)){
        if (sum_hum_int == 0){
            sum_hum_int = hum_int * 100;
        }
        if (sum_temp_int==0){
            sum_temp_int = temp_int *100; 
        }
        if (sum_vpd_int==0){
           sum_vpd_int = actual_vpd * 100;
        }
        if (sum_hum_int>0){
            avg_hum_int = sum_hum_int/100;
        }
        if (sum_temp_int>0){
            avg_temp_int = sum_temp_int/100;
        }
        if (sum_vpd_int>0){
            avg_vpd_int = sum_vpd_int/100;
        }
    }
} 

void vpd_calculate(){ 
    if ((temp_int>0) && (hum_int>0)){
        float es = 0.6108 * exp((17.27 * temp_int) / (temp_int + 237.3));
        float ea = es * (hum_int / 100.0);
        actual_vpd = es - ea;
    
        if ((sum_hum_int>0) && (sum_temp_int>0) && (sum_vpd_int>0)){
            sum_hum_int = sum_hum_int - avg_hum_int + hum_int;
            sum_temp_int = sum_temp_int - avg_temp_int + temp_int;
            sum_vpd_int = sum_vpd_int - avg_vpd_int + actual_vpd;
        }    
        if ((avg_hum_int>0) && (avg_temp_int>0) && (avg_vpd_int>0)){

            avg_hum_int = sum_hum_int/100;
            avg_temp_int = sum_temp_int/100;
            avg_vpd_int = sum_vpd_int/100;

            // Serial.print("hum medio: ");
            // Serial.print(avg_hum_int);
            // Serial.println(" %");
            // Serial.print("temp medio: ");
            // Serial.print(avg_temp_int);
            // Serial.println(" C");
            // Serial.print("VPD: ");
            // Serial.print(actual_vpd);
            // Serial.println(" kPa");
            // Serial.print("VPD Medio: ");
            // Serial.print(avg_vpd_int);
            // Serial.println(" kPa");
        }  
    }
    

}

// void append_struct_life_bit(){

//     life_bit_com[0].ind = 0;
//     life_bit_com[0].can_id_remote = CANID_MASTER;
//     life_bit_com[0].ackReceived = false;
//     life_bit_com[0].network = net_can;
//     life_bit_com[0].timeoutInterval = 0;
    
//     life_bit_com[1].ind = 1;
//     life_bit_com[1].can_id_remote = CANID_SENSOR;
//     life_bit_com[1].ackReceived = false;
//     life_bit_com[1].network = net_can;
//     life_bit_com[1].timeoutInterval = 0;

//     life_bit_com[2].ind = 2;
//     life_bit_com[2].can_id_remote = CANID_LIGHTS;
//     life_bit_com[2].ackReceived = false;
//     life_bit_com[2].network = net_can;
//     life_bit_com[2].timeoutInterval = 0;

//     life_bit_com[3].ind = 3;
//     life_bit_com[3].can_id_remote = CANID_OUTPUT;
//     life_bit_com[3].ackReceived = false;
//     life_bit_com[3].network = net_can;
//     life_bit_com[3].timeoutInterval = 0;

//     life_bit_com[4].ind = 4;
//     life_bit_com[4].can_id_remote = CANID_IRRIG;
//     life_bit_com[4].ackReceived = false;
//     life_bit_com[4].network = net_can;
//     life_bit_com[4].timeoutInterval = 0;

//     life_bit_com[5].ind = 5;
//     life_bit_com[5].can_id_remote = CANID_WIFI_BT;
//     life_bit_com[5].ackReceived = false;
//     life_bit_com[5].network = net_can;
//     life_bit_com[5].timeoutInterval = 0;

//     life_bit_com[6].ind = 6;
//     life_bit_com[6].can_id_remote = CANID_WIFI;
//     life_bit_com[6].ackReceived = false;
//     life_bit_com[6].network = net_can;
//     life_bit_com[6].timeoutInterval = 0;

//     life_bit_com[7].ind = 7;
//     life_bit_com[7].can_id_remote = CANID_BT;
//     life_bit_com[7].ackReceived = false;
//     life_bit_com[7].network = net_can;
//     life_bit_com[7].timeoutInterval = 0;

//     life_bit_com[8].ind = 8;
//     life_bit_com[8].can_id_remote = SERID_ESP;
//     life_bit_com[8].ackReceived = false;
//     life_bit_com[8].network = net_ser;
//     life_bit_com[8].timeoutInterval = 0;


// }


 