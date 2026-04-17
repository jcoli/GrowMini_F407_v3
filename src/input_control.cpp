/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>
#include <Adafruit_Sensor.h>
#include "DHT.h"
// #include <DHT_U.h>
#include <Wire.h>


#include "defines.h"
#include "io_defines.h"
#include "program.h"
#include "output_control.h"


void input_begin(); 
void input_read(); 
void printValues();

#define DHTTYPE DHT22
#define DHTTYPE1 DHT22


DHT dht_interno(INT_DHT, DHTTYPE);
DHT dht_externo(EXT_DHT, DHTTYPE);

// DHT dht[2] = { dht_interno, dht_externo };

extern byte minutes;
extern byte hours;
extern byte weekDay ;
extern byte day;
extern byte month;
extern byte year;

extern float temp_int;
extern float temp_ext;
extern float hum_int;
extern float hum_ext;
extern float soil_1_hum;
extern float soil_2_hum;
extern float soil_3_hum;
extern float light_1_int;
extern float vpd_int;
extern float avg_vpd_int;
extern float sum_vpd_int;
extern float co2_int;
extern float co2_ext;

extern bool level_irrig_l;
extern bool level_hum_l;
extern bool level_irrig_ll;
extern bool level_hum_h;

extern bool light_on;
extern bool pump_irr_on;

extern bool relay_1_on;
extern bool relay_2_on;

extern bool fan1_inf_on;
extern bool fan2_inf_on;

extern int fan1_inf_pwm;
extern int fan2_inf_pwm;
extern int light_pwm;

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

extern bool zeroChangeDetect;
extern bool lastZeroState;
extern bool run_on;

extern bool pwm_bool;
extern int pwm1;

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
extern int irr_on_stp;
extern int irr_interval_stp;
extern int irr_interval_last_hour;
extern int irr_time_stp;
extern int irr_interval_on_stp;
extern int irr_on_hr_stp;
extern int irr_on_min_stp;
extern int irr_off_hr_stp;
extern int irr_off_min_stp;



float my_map(float val, float li, float ls, float lio, float lso);
void test_dht(int idx);

// const uint8_t INP_PINS[NUM_INP] = {LUMI_ANA_DIG, DOOR, SOIL_HUM_DIG};

void input_begin(){
    Serial.println("Input Begin "); 
    dht_interno.begin();
    dht_externo.begin();
    
    pinMode(LV_L_IRR, INPUT_PULLDOWN);
    pinMode(LV_L_HUM, INPUT_PULLDOWN);
    pinMode(LV_LL_IRR, INPUT_PULLDOWN);
    pinMode(LV_H_HUM, INPUT_PULLDOWN);

    

    // attachInterrupt(digitalPinToInterrupt(LV_H_HUM), pump_hum_off, RISING);
    
}

void input_read(){
    // Serial.println("Input Read "); 
    float soil_hum_temp = 0.00;
    soil_hum_temp=analogRead(SOIL_HUM_1);
    // Serial.println(soil_hum_temp); 
    soil_1_hum = map(soil_hum_temp, 1450, 4095, 100, 0);
    if (soil_1_hum>100) soil_1_hum = 100;
    if (soil_1_hum<0) soil_1_hum = 0;
    // Serial.println(soil_1_hum);
    soil_hum_temp=analogRead(SOIL_HUM_2);
    // Serial.println(soil_hum_temp); 
    soil_2_hum = map(soil_hum_temp, 1450, 4095, 100, 0);
    if (soil_2_hum>100) soil_2_hum = 100;
    if (soil_2_hum<0) soil_2_hum = 0;
    // Serial.println(soil_2_hum);
    // soil_hum_temp=analogRead(SOIL_HUM_3);
    // soil_3_hum = map(soil_hum_temp, 1000, 4095, 100, 0);
    hum_int = dht_interno.readHumidity();
    hum_ext = dht_externo.readHumidity();
    temp_int = dht_interno.readTemperature();
    temp_ext = dht_externo.readTemperature();
    if ((isnan(temp_ext))|| (isnan(hum_ext))){
        dht_externo.begin();
        delay(500);    
        temp_ext = dht_externo.readTemperature();
        hum_ext = dht_externo.readHumidity();
    }
    if ((isnan(temp_int)) || (isnan(hum_int))){
        dht_interno.begin();
        delay(500);
        temp_int = dht_interno.readTemperature();
        hum_int = dht_interno.readHumidity();
    }

    level_irrig_l = digitalRead(LV_L_IRR); 
    // Serial.println(digitalRead(LV_L_IRR)); 
    level_hum_l = digitalRead(LV_L_HUM);
    // Serial.println(digitalRead(LV_L_HUM)); 
    level_irrig_ll = digitalRead(LV_LL_IRR);
    // Serial.println(digitalRead(LV_LL_IRR));
    level_hum_h = digitalRead(LV_H_HUM);
    if (level_hum_h) pump_hum_off();
    // Serial.println(digitalRead(LV_H_HUM));
    avg_calculate();
    vpd_calculate();
    printValues();
    
}

void printValues() {
    Serial.println("===========================");
    Serial.printf("%02d/%02d/%02d ", day, month, year);
    Serial.printf("%02d:%02d\n", hours, minutes);
    Serial.print("soil humidity 1: ");
    Serial.println(soil_1_hum);
    Serial.print("soil humidity 2: ");
    Serial.println(soil_2_hum);
    Serial.print("Temp Int: ");
    Serial.println(temp_int);
    Serial.print("Hum Int: ");
    Serial.print(hum_int);
    Serial.print(" : ");
    Serial.print(hum_int_min_stp);
    Serial.print(" : ");
    Serial.println(hum_int_max_stp);
    Serial.print("Temp Ext: ");
    Serial.println(temp_ext);
    Serial.print("Hum Ext: ");
    Serial.println(hum_ext);
    Serial.print("VPD: ");
    Serial.print(vpd_int);
    Serial.println(" kPa");
    Serial.print("VPD Medio: ");
    Serial.print(avg_vpd_int);
    Serial.println(" kPa");
    Serial.print("Level Irr. L: ");
    Serial.println(level_irrig_l);
    Serial.print("Level Irr. LL: ");
    Serial.println(level_irrig_ll);
    Serial.print("Level Hum. L: ");
    Serial.println(level_hum_l);
    Serial.print("Level Hum. h: ");
    Serial.println(level_hum_h);
    

    // Serial.println("===========================");
    // Serial.print("Light setup: ");
    // Serial.print(light_hr_on_stp);
    // Serial.print(":");
    // Serial.print(light_min_on_stp);
    // Serial.print(" , ");
    // Serial.print(light_hr_off_stp);
    // Serial.print(":");
    // Serial.println(light_min_off_stp);
    // Serial.print("Fan 1 setup: ");
    // Serial.print(fan1_inf_pwm);
    // Serial.print(" : ");
    // Serial.print(fan1_inf_pwm_stp);
    // Serial.print(" : ");
    // Serial.println(fan1_inf_pwm_light_stp);
    // Serial.print("Fan 2 setup: ");
    // Serial.print(fan2_inf_pwm);
    // Serial.print(" : ");
    // Serial.print(fan2_inf_pwm_stp);
    // Serial.print(" : ");
    // Serial.println(fan2_inf_pwm_light_stp);
    // Serial.print("Irrig. Interval: ");
    // Serial.println(irr_time_stp);
    // Serial.print("Irrig. ON/OFF: ");
    // Serial.println(pump_irr_on);
    
}

float my_map(float val, float li, float ls, float lio, float lso){
    float a =  (lso - lio) / (ls - li);
    float b = li-(a*lio);
    float ret_val = (val*a) - b;
    return ret_val;
}

void test_dht(int idx)
{
  // //  READ DATA
  // uint32_t start = micros();
  // int chk = dht[idx].read();
  // uint32_t stop = micros();

  // Serial.print(idx);
  // Serial.print(",\t");

  // switch (chk)
  // {
  //   case DHTLIB_OK:
  //     Serial.print("OK,\t");
  //     break;
  //   case DHTLIB_ERROR_CHECKSUM:
  //     Serial.print("Checksum error,\t");
  //     break;
  //   case DHTLIB_ERROR_TIMEOUT_A:
  //     Serial.print("Time out A error,\t");
  //     break;
  //   case DHTLIB_ERROR_TIMEOUT_B:
  //     Serial.print("Time out B error,\t");
  //     break;
  //   case DHTLIB_ERROR_TIMEOUT_C:
  //     Serial.print("Time out C error,\t");
  //     break;
  //   case DHTLIB_ERROR_TIMEOUT_D:
  //     Serial.print("Time out D error,\t");
  //     break;
  //   case DHTLIB_ERROR_SENSOR_NOT_READY:
  //     Serial.print("Sensor not ready,\t");
  //     break;
  //   case DHTLIB_ERROR_BIT_SHIFT:
  //     Serial.print("Bit shift error,\t");
  //     break;
  //   case DHTLIB_WAITING_FOR_READ:
  //     Serial.print("Waiting for read,\t");
  //     break;
  //   default:
  //     Serial.print("Unknown: ");
  //     Serial.print(chk);
  //     Serial.print(",\t");
  //     break;
  // }

  // //  DISPLAY DATA
  // Serial.print(dht[idx].getHumidity(), 1);
  // Serial.print(",\t");
  // Serial.print(dht[idx].getTemperature(), 1);
  // Serial.print(",\t");
  // uint32_t duration = stop - start;
  // Serial.print(duration);
  // Serial.print(",\t");
  // Serial.println(dht[idx].getType());
  // delay(500);
}

