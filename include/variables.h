/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/


#ifndef __VARIABLES_H__
#define __VARIABLES_H__
#include <Arduino.h>
#include "structures.h"

unsigned long loopDelay = millis();
unsigned long loopDelay_live = millis();
unsigned long loopDelay_ack = millis();
unsigned long loopDelay_first = millis(); 
unsigned long loopDelay_analog = millis();
unsigned long loopDelay_input = millis();
unsigned long lastAvailabilityToggleAt = millis();
unsigned long loopDelay_watchdog = millis();
unsigned long loopDelay_pump = millis();
unsigned long loopDelay_hum_pump = millis();
unsigned long loopDelay_irrig = millis();
unsigned long loopDelay_lifebit = millis();
unsigned long loopDelay_schedule = millis();
unsigned long loopDelay_led = millis();
unsigned long loopDelay_hum_pump_start = millis();

String retMsg2[2] = {"", ""};
String retMsg3[3] = {"", "", ""};
String retMsg4[4] = {"", "", "", ""};
String retMsg5[5] = {"", "", "", "", ""};
String retMsg6[6] = {"", "", "", "", "", ""};
String retMsg7[7] = {"", "", "", "", "", "", ""};
String retMsg8[8] = {"", "", "", "", "", "", "", ""};
String retMsg9[9] = {"", "", "", "", "", "", "", "", ""};
String retMsg10[10] = {"", "", "", "", "", "", "", "", "", ""}; 


String name_device = "Grow Mini";
String manufacturer = "GreenTomato";

var_grow var_grow_1[60];
var_grow var_grow_2[20];
var_grow var_grow_3[20];
var_grow var_grow_4[20];
var_grow var_grow_5[20];
var_grow var_grow_6[20];
var_grow var_grow_7[20];
var_grow var_grow_8[20];
var_grow var_grow_9[20];
var_grow var_grow_A[20];

//TimeStamp
uint32_t subSec;
byte seconds;
byte minutes;
byte hours;
byte weekDay ;
byte day;
byte month;
byte year;

byte lastMinutes;
byte lastHours;
byte lastWeekDay ;
byte lastDay;
byte lastMonth;
byte lastYear;

byte pump_interval;

//Service 7 
String ipaddress = "";
String gateway = "";
String subnet = "";
String ssid_name = "";
String ssid_pwd = "";
String ha_ip = "";
String ha_user = "";
String ha_pwd = "";
String ha_device_name = "";
String owner_name = "";
String user_name = "";
String user_pwd = "";
String bt_name;

String timeStampSchedule = "";

//System
bool is_watchdog = false;
bool led_out = false;
bool first_run = true;
bool flash_ok = false;
bool scheduleRun = false; 
bool alarm_on = false;

bool bt_enabled = false;
bool bt_connected = false;
bool wifi_connected = false;
bool ha_connected = false;
bool bt_alive = false;
bool bt_rec = false;
bool pauseSensorSends = false;

String line = "";
String line1 = "";
String line2 = "";

bool stringComplete = false;
bool string1Complete = false;
bool string2Complete = false;

String flag_set = "false";
String flag_schedule = "false";

float VRef = 0.00;
float intTemp = 0.00;

int display_to_show = 0;

float temp_int = 0.00;
float temp_ext = 0.00;
float hum_int = 0.00;
float hum_ext = 0.00;
float vpd_int = 0.00;
float soil_1_hum = 0.00;
float soil_2_hum = 0.00;
float soil_3_hum = 0.00;
float light_1_int = 0.00;
float co2_int = 0.00;
float co2_ext = 0.00;

bool level_irrig_l = false;
bool level_irrig_ll = false;
bool level_hum_l = false;
bool level_hum_h = false;

bool light_on = false;
bool pump_irr_on = false;
bool pump_hum_on = false;
bool pump_dehum_on = false;
bool relay_1_on = false;
bool relay_2_on = false;
bool relay_3_on = false;
bool relay_4_on = false;
bool relay_5_on = false;
bool relay_6_on = false;
bool fan1_inf_on = false;
bool fan2_inf_on = false;
bool fan3_inf_on = false;
bool hum_1_on = false;
bool dehum_1_on = false;

bool light_on_set = false;
bool pump_irr_on_set = false;
bool pump_hum_on_set = false;
bool relay_1_on_set = false;
bool relay_2_on_set = false;
bool relay_3_on_set = false;
bool relay_4_on_set = false;
bool fan1_inf_on_set = false;
bool fan2_inf_on_set = false;
bool fan3_inf_on_set = false;
bool hum_1_on_set = false;

bool fan1_inf_pwm_set = false;
bool fan2_inf_pwm_set = false;
bool light_pwm_set = false;

int fan1_inf_pwm = 0;
int fan2_inf_pwm = 0;
int fan3_inf_pwm = 0;
int light_pwm = 0;
int hum_pwm = 0;

int hum_pump_time_stp = 3000;

bool zeroChangeDetect = false;
bool lastZeroState = false;
bool run_on = false;


bool pwm_bool = false;
int pwm1 = 0;

//Service 01

int temp_int_min_stp = 0;
int temp_int_max_stp = 0;

int hum_int_on_stp = 0;
int hum_int_on_light_stp = 0;

int hum_int_min_stp = 0;
int hum_int_max_stp = 0;

int hum_on_stp = 0;

int vpd_int_min_stp = 0;
int vpd_int_max_stp = 0;

int co2_min_stp = 0;
int co2_max_stp = 0;

int soil_hum_min_stp = 0;
int soil_hum_max_stp = 0;
int ph_irrig_stp = 0;
int ph_hum_stp = 0;

int light_hr_on_stp = 0;
int light_min_on_stp = 0;
int light_hr_off_stp = 0;
int light_min_off_stp = 0;

int pump_irr_on_stp = 0;
int pump_hr_irr_on_stp = 0;
int pump_min_irr_on_stp = 0;
int pump_hr_irr_off_stp = 0;
int pump_min_irr_off_stp = 0;

int irr_on_stp = 0;
int irr_interval_stp = 0;
int irr_interval_last_hour = 0;
int irr_time_stp = 0;
int irr_interval_on_stp = 0;
int irr_1_hr_stp = 0;
int irr_1_min_stp = 0;
int irr_2_hr_stp = 0;
int irr_2_min_stp = 0;

int relay_1_on_hr_stp = 0;
int relay_1_on_min_stp = 0;
int relay_1_off_hr_stp = 0;
int relay_1_off_min_stp = 0;
int relay_2_on_hr_stp = 0;
int relay_2_on_min_stp = 0;
int relay_2_off_hr_stp = 0;
int relay_2_off_min_stp = 0;
int relay_3_on_hr_stp = 0;
int relay_3_on_min_stp = 0;
int relay_3_off_hr_stp = 0;
int relay_3_off_min_stp = 0;
int relay_4_on_hr_stp = 0;
int relay_4_on_min_stp = 0;
int relay_4_off_hr_stp = 0;
int relay_4_off_min_stp = 0;
int relay_1_red_stp = 0;
int relay_2_red_stp = 0;
int relay_3_red_stp = 0;
int relay_4_red_stp = 0;

int relay_red[40];

//service 02 AVG
float eco2_int_avg = 0.00;
float eco2_ext_avg = 0.00;
float hum_int_avg = 0.00;
float hum_ext_avg = 0.00;
float temp_int_avg = 0.00;
float temp_ext_avg = 0.00;
float soil_hum_avg = 0.00;
float light_int_avg = 0.00;
float level_irrig_l_avg = 0.00;

float actual_vpd = 0.00;
float avg_vpd_int = 0.00;
float avg_temp_int = 0.00;
float avg_hum_int = 0.00;
float sum_vpd_int = 0.00;
float sum_temp_int = 0.00;
float sum_hum_int = 0.00;

//
int light_pwm_stp = 0;
int fan1_inf_pwm_stp = 0;
int fan2_inf_pwm_stp = 0;
int fan3_inf_pwm_stp = 0;

int fan1_inf_pwm_light_stp = 0;
int fan2_inf_pwm_light_stp = 0;
int fan3_inf_pwm_light_stp = 0;

#endif
