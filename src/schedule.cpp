/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#include <Arduino.h>

#include "defines.h"
#include "tools.h"
#include "eprom.h"
#include "structures.h"
#include "io_defines.h"
#include "program.h"
#include "fuzzyControl.h"


void schedule_read();
void schedule_save();
void schedule_run();
void schedule_check();
void schedule_run_light_off();
void schedule_run_light_on();

extern byte minutes;
extern byte hours;
extern byte weekDay ;
extern byte day;
extern byte month;
extern byte year;

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

extern bool fan_dehum_on;
extern bool fan1_inf_on;
extern bool fan2_inf_on;
extern bool fan3_inf_on;
extern bool fan_hum_on;
extern bool light_on;
extern bool pump_irr_on;
extern bool hum_1_on;
extern bool relay_1_on;
extern bool relay_2_on;
extern bool relay_3_on;
extern bool relay_4_on;
extern bool output_1_on;
extern bool output_2_on;

extern bool light_on_set;
extern bool pump_irr_on_set;
extern bool pump_hum_on_set;
extern bool relay_1_on_set;
extern bool relay_2_on_set;
extern bool relay_3_on_set;
extern bool relay_4_on_set;
extern bool fan1_inf_on_set;
extern bool fan2_inf_on_set;
extern bool hum_1_on_set;

extern bool fan1_inf_pwm_set;
extern bool fan2_inf_pwm_set;
extern bool light_pwm_set;

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
extern int irr_interval_last_hour;
extern int light_pwm_stp;
extern int fan1_inf_pwm_stp;
extern int fan2_inf_pwm_stp;
extern int fan1_inf_pwm_light_stp;
extern int fan2_inf_pwm_light_stp;

extern String owner_name;
extern String user_name;
extern String user_pwd;
extern String bt_name;

extern String timeStampSchedule;
extern String flag_set;
extern String flag_schedule;

extern HardwareTimer *tim1;

extern unsigned long loopDelay_pump;
extern unsigned long loopDelay_hum_pump;
extern unsigned long loopDelay_pump;
extern unsigned long loopDelay_irrig;
extern unsigned long loopDelay_hum_pump;

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
 
void schedule_read(){
    Serial.println("Schedule read");
    uint32_t addr;
    uint8_t data = 0;
    uint16_t data_int = 0;
    for (int i = 0; i <= 50; i++){
        addr = var_grow_1[i].eprom_address;
        data_int = read_Byte(addr);
        *var_grow_1[i].var_int = data_int;
        // Serial.print("Schedule ");
        // Serial.print(var_grow_1[i].descr);
        // Serial.print(", ");
        // Serial.print(addr);
        // Serial.print(", ");
        // Serial.println(data_int);
        // delay(500);
    }
    Serial.println("Schedule 1"); 
 
    for (int i = 0; i <= 12; i++){
        // Serial.println("Schedule 1a");
        addr = var_grow_7[i].eprom_address;
        // Serial.println("Schedule 1b");
        // String data = "Bunda";
        String data = read_String(addr);
        if (data == NULL){
            data = "NULL";
        }
        delay(500);
        // if (i==3){
        //     bt_name = data;
        // }
        // Serial.println("Schedule 1c");
        *var_grow_7[i].var_string = data;
        // Serial.print(i);
        // Serial.print(" Data: ");
        // Serial.print(var_grow_7[i].descr);
        // Serial.print(", ");
        // Serial.print(addr);
        // Serial.print(", ");
        // Serial.print(data);
        // Serial.print(", ");
        // Serial.print(*var_grow_7[i].var_string);
        // Serial.print(", ");
        // Serial.println(bt_name);
        // delay(500);
    }  
    // Serial.println("Schedule 2");
      
}

void schedule_save(){
    // Serial.println("Schedule Save");
    uint32_t addr;
    uint32_t data = 0;
    if (eraseSector(16384)){
        for (int i = 0; i <= 50; i++){
            addr = var_grow_1[i].eprom_address;
                data = *var_grow_1[i].var_int; 
                if(writeLong(addr, data)){
                    // Serial.println("Schedule Write OK");
                    // Serial.print("save flash: ");
                    // Serial.println(i);
                    // Serial.print("Eprom 1 ");
                    // Serial.println(data);
                    // Serial.print(", ");
                    // Serial.println(addr);
                    uint8_t ret = read_Byte(addr);
                    // Serial.print("Eprom 1 ");
                    // Serial.println(ret);
                }else{
                    Serial.println("Schedule Write 1 not OK");
                }
        }        
    }

    if (eraseSector(16384)){
        for (int i = 0; i <= 2; i++){
            addr = var_grow_1[i].eprom_address;
                data = *var_grow_1[i].var_int; 
                if(writeLong(addr, data)){
                    // Serial.println("Schedule Write OK");
                    // Serial.print("save flash: ");
                    // Serial.println(i);
                    // Serial.print("Eprom 1 ");
                    // Serial.println(data);
                    // Serial.print(", ");
                    // Serial.println(addr);
                    uint8_t ret = read_Byte(addr);
                    // Serial.print("Eprom 1 ");
                    // Serial.println(ret);
                }else{
                    Serial.println("Schedule Write 1 not OK");
                }
        }        
    }


}

void schedule_check(){
    // Serial.println("Schedule Check");
    // Serial.printf("%02d/%02d/%02d ", day, month, year);
    // Serial.printf("%02d:%02d\n", hours, minutes);
    // Serial.print("Light setup: ");
    // Serial.print(light_hr_on_stp);
    // Serial.print(":");
    // Serial.print(light_min_on_stp);
    // Serial.print(" , ");
    // Serial.print(light_hr_off_stp);
    // Serial.print(":");
    // Serial.println(light_min_off_stp);
    
   if (light_hr_on_stp<light_hr_off_stp){
        Serial.println("Schedule Check Light 1");
        if((light_hr_on_stp<=hours) && (light_hr_off_stp>=hours)){
            //light_on
            // if (light_min_on_stp<=minutes){
                Serial.println("Schedule Check Light on 1");
                schedule_run_light_on();
            // }
        }else if((light_hr_on_stp<=hours) && (light_hr_off_stp<=hours)){
            //light_off
            // if (light_min_off_stp<=minutes){
                Serial.println("Schedule Check Light off 1");
                schedule_run_light_off();
            // }
        }else if((light_hr_on_stp>hours) && (light_hr_off_stp>hours)){
            //light_off
            // if (light_min_off_stp<=minutes){
                Serial.println("Schedule Check Light off 1a");
                schedule_run_light_off();
            // }
        }
    }
    if (light_hr_on_stp>light_hr_off_stp){
        Serial.println("Schedule Check Light 2");
        if((light_hr_off_stp<=hours) ){
            Serial.println("Schedule Check Light 2a");
        }        
        if((light_hr_on_stp<=hours)){
            Serial.println("Schedule Check Light 2b");
        }
        if((light_hr_off_stp<hours) && (light_hr_on_stp<hours)){
            //light_on
            // if (light_min_on_stp<=minutes){
                Serial.println("Schedule Check Light on 2");
                schedule_run_light_on();
            // }
        }else if((light_hr_off_stp>hours) && (light_hr_on_stp<hours)){
            //light_off
            // if (light_min_off_stp<=minutes){
                Serial.println("Schedule Check Light off 2");
                schedule_run_light_off();
            // }
        }else if((light_hr_off_stp<hours) && (light_hr_on_stp>hours)){
            //light_off
            // if (light_min_off_stp<=minutes){
                Serial.println("Schedule Check Light off 2a");
                schedule_run_light_off();
            // }
        }
    }

}

void schedule_run_light_on(){
        // Serial.println("+++++++++++++++++++++++++++++++++++++++");
        // Serial.println("+++++++++++++++++++++++++++++++++++++++");
        Serial.println("schedule_run_light_on");
        // Serial.println("+++++++++++++++++++++++++++++++++++++++");
        // Serial.println("+++++++++++++++++++++++++++++++++++++++");
        
        light_pwm = *var_grow_1[20].var_int;
        light_on = true;
        tim1->setCaptureCompare(3, light_pwm, PERCENT_COMPARE_FORMAT);
        
        // Serial.println("Fan");
        fan1_inf_pwm = fan1_inf_pwm_light_stp; 
        // Serial.print("Fan 1 PWM Light ON: "); 
        // Serial.println(fan1_inf_pwm);   
        if (fan1_inf_pwm>0){
            fan1_inf_on = true;
            tim1->setCaptureCompare(1, fan1_inf_pwm_light_stp, PERCENT_COMPARE_FORMAT);
        }else{
            fan1_inf_on = false;
            tim1->setCaptureCompare(1, 0, PERCENT_COMPARE_FORMAT);
        }             
        // sendValuesFloat(CANID_OUTPUT, 0x05, 0x01, fan1_inf_pwm);
        
        fan2_inf_pwm = fan2_inf_pwm_light_stp; 
        // Serial.print("Fan 2: ");
        // Serial.println("fan2_inf_pwm");
        if (fan2_inf_pwm>0){
            fan2_inf_on = true;
            tim1->setCaptureCompare(2, fan2_inf_pwm_light_stp, PERCENT_COMPARE_FORMAT);
        }else{
            fan2_inf_on = false;
            tim1->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT);
        }
        // hum_1_on = *var_grow_1[27].var_int;
        // digitalWrite(HUM, hum_1_on);    
        soilHumidityControl();        
    
}

void schedule_run_light_off(){
        Serial.println("schedule_run_light_off");
        
        light_pwm = *var_grow_1[20].var_int;
        light_on = false;
        tim1->setCaptureCompare(3, 0, PERCENT_COMPARE_FORMAT);

        fan1_inf_pwm = fan1_inf_pwm_stp; 
        Serial.print("Fan 1 PWM Light ON: ");  
        Serial.println(fan1_inf_pwm);  
        if (fan1_inf_pwm>0){
            fan1_inf_on = true;
            tim1->setCaptureCompare(1, fan1_inf_pwm, PERCENT_COMPARE_FORMAT);
        }else{
            fan1_inf_on = false;
            tim1->setCaptureCompare(1, 0, PERCENT_COMPARE_FORMAT);
        }   
        fan2_inf_pwm = fan2_inf_pwm_stp;     
        Serial.print("Fan 2 PWM Light ON: ");
        Serial.println(fan2_inf_pwm);
        
        if (fan2_inf_pwm>0){
            fan2_inf_on = true;
            tim1->setCaptureCompare(2, fan2_inf_pwm, PERCENT_COMPARE_FORMAT);
        }else{
            fan2_inf_on = false;
            tim1->setCaptureCompare(2, 0, PERCENT_COMPARE_FORMAT);
        }
        // hum_1_on = *var_grow_1[28].var_int;
        // digitalWrite(HUM, hum_1_on);
            

    
}



void schedule_run(){
    Serial.println("Schedule Run");
    Serial.printf("%02d/%02d/%02d ", day, month, year);
    Serial.printf("%02d:%02d\n", hours, minutes);
    Serial.print("Light setup: ");
    Serial.print(light_hr_on_stp);
    Serial.print(":");
    Serial.print(light_min_on_stp);
    Serial.print(" , ");
    Serial.print(light_hr_off_stp);
    Serial.print(":");
    Serial.println(light_min_off_stp);
   
    if (lastHours != hours){
        lastHours = hours;
        // if ((millis() - loopDelay_irrig > (irr_interval_stp*3600000)) && (scheduleRun)){
        // soilHumidityControl();
        // loopDelay_irrig = millis();
        // Serial.println("+++++++++++++++++++++++++++++");
        // Serial.println("loopDelay_irrig");
        // Serial.print("Interval: ");
        // Serial.println(irr_interval_stp*3600000);
        // Serial.println("+++++++++++++++++++++++++++++");
        // Serial.println("+++++++++++++++++++++++++++++");
    // }
    }
    if ((lastMinutes != minutes)){
        lastMinutes = minutes;
        schedule_read(); 
        // Serial.print("Light setup 1: ");
        // Serial.printf("%02d/%02d/%02d ", day, month, year);
        // Serial.printf("%02d:%02d\n", hours, minutes);
        // Serial.print(light_hr_on_stp);
        // Serial.print(":");
        // Serial.print(light_min_on_stp);
        // Serial.print(" , ");
        // Serial.print(light_hr_off_stp);
        // Serial.print(":");
        // Serial.println(light_min_off_stp);
        if ((light_hr_on_stp==hours) && (light_min_on_stp==minutes)){
            Serial.println("Light ON 1");
            schedule_run_light_on();
        }
        if ((light_hr_off_stp==hours) && (light_min_off_stp==minutes)){
            Serial.println("Light OFF 1");
            schedule_run_light_off();
        }
        
        if (irr_interval_last_hour<hours){
            irr_interval_last_hour=hours;
        }
        
    }

}