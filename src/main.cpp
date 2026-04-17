/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>
#include "stm32yyxx_ll_adc.h"
#include <SPI.h>
#include <STM32RTC.h>
#include <HardwareTimer.h>
#include <IWatchdog.h>

#include "io_defines.h"
#include "variables.h" 
#include "defines.h"
#include "eprom.h" 
#include "struc_mount.h"
#include "structures.h"
#include "tools.h"
#include "sounds.h"
#include "pitches.h"
#include "defines_protocol.h"
#include "fuzzyControl.h"
#include "icons.h"
#include "program.h"
#include "can_control.h"
#include "output_control.h"
#include "input_control.h"
#include "schedule.h"
#include "comm_esp.h"
#include "display.h"
#include "display_rtc.h"
#include "send_to_esp.h"

void serialEvent2();
void serialEventRun(void); 
void configureRTC();
void checkRTCConfig();

static int32_t readVref();
static int32_t readTempSensor(int32_t VRef);

HardwareSerial ESP_SERIAL(RX_BT, TX_BT);
STM32RTC& rtc = STM32RTC::getInstance();

void serialEventRun(void)
{
  // #if defined(HAVE_HWSERIAL2)
    if (serialEvent2 && ESP_SERIAL.available()) {
      serialEvent2();
     
    }
}

void setup() {
    Serial.begin(115200); //PC
    ESP_SERIAL.begin(115200);
    delay(1000); 

    output_begin();
    display_begin();

    Serial.println("");
    Serial.println("");
    Serial.println("===================================");
    Serial.println("===================================");
    Serial.println("Main ");

    analogReadResolution(12);
    configureRTC();
    STM32RTC& rtc = STM32RTC::getInstance();
    rtc.setClockSource(STM32RTC::LSE_CLOCK);
    rtc.begin();

    can_begin();
    delay(200);
    struc_mount_begin();
    delay(200);

    input_begin();
    delay(200);
    
    flash_begin();
    schedule_read();
    delay(200);
    beginFuzzy();
    delay(200);

    IWatchdog.begin(50000000);
    loopDelay_watchdog = millis();
    rtc.getDate(&weekDay, &day, &month, &year);
    rtc.getTime(&hours, &minutes, &seconds, &subSec);
    lastMinutes = minutes;
    checkRTCConfig();
    loopDelay_first = millis();
    first_run = true;
    play_sleep_sound();
  
}

void loop() {
  if ((level_hum_h) && (pump_hum_on)) pump_hum_off();

  if (millis() - loopDelay_watchdog  > TIMER_WATCHDOG){ 
    loopDelay_watchdog  = millis();
    
    IWatchdog.reload();
    sendValuesBoolean(CANID_OUTPUT , 0x04, 0x02, 85);
    if (level_hum_h) pump_hum_off();
    Serial.println("loopDelay_watchdog");
    
  //  digitalWrite(BT_POWER,!(digitalRead(BT_POWER)));
  }

  if (millis() - loopDelay_led > TIMER_LED){
    loopDelay_led = millis();
    digitalWrite(LED_PIN, !digitalRead(LED_PIN));
  }


  if (millis() - loopDelay > TIMER_ANALOG){
    // Serial.println("loopDelay");
    rtc.getDate(&weekDay, &day, &month, &year);
    rtc.getTime(&hours, &minutes, &seconds, &subSec);
    
    // Serial.printf("%02d/%02d/%02d ", day, month, year);
    // Serial.printf("%02d:%02d\n", hours, minutes);
    VRef = readVref();
    intTemp = readTempSensor(VRef);
    // Serial.print("Tempertura Processador: ");
    // Serial.println(intTemp);
    
    delay(200);
    input_read();
    send_ana_values();
    
    // input_read();
    // printValues();
    display_to_show++;
    if (display_to_show>3) display_to_show=1;  
    switch (display_to_show) {
        case 1:
            // Serial.println("display case 1");
            show_display_1();
            break;
        case 2:
            // Serial.println("display case 2");
            show_display_2();
            break;    
        case 3:
            // Serial.println("display case 3");
            show_display_rtc();
            break;      
    }
    send_esp_bt("1","5","7", "5");
    // play_star_wars_sound();
    loopDelay = millis();
    // Serial.println("loopDelay 4");
    }
          
    if ((millis() - loopDelay_first > TIMER_FIRST) && first_run){
          Serial.println("=================================");
          Serial.println("=================================");
          Serial.println("loopDelay_first");
          Serial.println("=================================");
          Serial.println("=================================");
          rtc.getDate(&weekDay, &day, &month, &year);
          rtc.getTime(&hours, &minutes, &seconds, &subSec);
          loopDelay_first = millis();
          init_ble();
          delay(500);
          init_wifi();
          delay(1500);
          // init_mqtt();
          delay(500);
          program_begin();
          delay(500); 
          schedule_check();
          first_run = false;
          play_finish_sound();
          
    }

    

    if ((millis() - loopDelay_schedule > TIMER_SCHEDULE) && (scheduleRun)){
      // Serial.println("loopDelay_schedule");
    // if ((millis() - loopDelay_schedule > TIMER_SCHEDULE) ){
          loopDelay_schedule = millis();
          rtc.getDate(&weekDay, &day, &month, &year);
          rtc.getTime(&hours, &minutes, &seconds, &subSec);
          Serial.printf("%02d/%02d/%02d ", day, month, year);
          Serial.printf("%02d:%02d\n", hours, minutes);
          // Serial.println("");
          // Serial.println(lastMinutes);
          schedule_run();
          relay_1_control();
          relay_2_control();
          relay_3_control();
          relay_4_control();
          
          alarm_control();
          // airHumidityControl();
          // soilHumidityControl();
          hum_control();
          level_hum_control();
          // schedule_read();
          // play_door_sound();
          // play_finish_sound();
          
      }

  if ((millis() - loopDelay_pump > irr_time_stp) && (pump_irr_on)){ 
      pump_irr_on = false;
      digitalWrite(PUMP1, pump_irr_on );
      loopDelay_pump = millis();
      // Serial.println("##########################################");
      // Serial.println("PUMP IRRIG OFF ");
      // Serial.println(irr_time_stp);
      // Serial.println("##########################################");
      // Serial.println(irr_time_stp);
      play_door_sound();
      
  } 
  
  if ((millis() - loopDelay_hum_pump_start > 30000) && (!pump_hum_on)){
    loopDelay_hum_pump_start = millis();
    level_hum_control();

  }

  if ((millis() - loopDelay_hum_pump > hum_pump_time_stp) && (pump_hum_on)){ 
      pump_hum_on = false;
      digitalWrite(PUMP2, LOW );
      loopDelay_hum_pump = millis();
      loopDelay_hum_pump_start = millis();
      Serial.println("##########################################");
      Serial.println("PUMP HUM OFF ");
      Serial.println("##########################################");
      send_esp_bt("1","4","5", "0");
      // Serial.println(irr_time_stp);
  }    
  
   
  
}

void serialEvent2(){
  // Serial.print("serial 1: ");
  while(ESP_SERIAL.available()){
    char inChar = (char)ESP_SERIAL.read();
    line1 += inChar;
    // Serial.println(line1);
    if (inChar == '#'){
      string1Complete = true;
      // on_loop();
    }
    if (string1Complete){
      Serial.print("serial 2: ");
      Serial.println(line1);
      on_ser_comm(line1);
      string1Complete = false;
      line1 = "";
    }
  }
}


void configureRTC() {
    // Habilitar clock para PWR
    __HAL_RCC_PWR_CLK_ENABLE();
    HAL_PWR_EnableBkUpAccess();
    
    // Configurar LSE
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
    RCC_OscInitStruct.LSEState = RCC_LSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
    
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
        // Tratar erro
        return;
    }
    
    // Configurar prescalers diretamente nos registradores RTC
    // Para LSE 32768Hz: PREDIV_A = 127, PREDIV_S = 255
    // Resulta em: 32768 / (127+1) = 256Hz -> 256 / (255+1) = 1Hz
    RTC->PRER = (127 << 16) | 255;
}

void checkRTCConfig() {
    // Ler registradores do RTC diretamente
    uint32_t prer = RTC->PRER;
    uint32_t prediv_a = (prer >> 16) & 0x7F;
    uint32_t prediv_s = prer & 0x7FFF;
    
    // Serial.print("PREDIV_A: ");
    // Serial.println(prediv_a);
    // Serial.print("PREDIV_S: ");
    // Serial.println(prediv_s);
    
    // Calcular frequência resultante
    float freq = 32768.0 / ((prediv_a + 1) * (prediv_s + 1));
    // Serial.print("Frequência do RTC: ");
    // Serial.print(freq);
    // Serial.println(" Hz");
}

static int32_t readVref()
{
#ifdef __LL_ADC_CALC_VREFANALOG_VOLTAGE
#ifdef STM32U5xx
  return (__LL_ADC_CALC_VREFANALOG_VOLTAGE(ADC1, analogRead(AVREF), LL_ADC_RESOLUTION));
#else
  return (__LL_ADC_CALC_VREFANALOG_VOLTAGE(analogRead(AVREF), LL_ADC_RESOLUTION));
#endif
#else
  return (VREFINT * ADC_RANGE / analogRead(AVREF)); // ADC sample to mV
#endif
}

#ifdef ATEMP
static int32_t readTempSensor(int32_t VRef)
{
#ifdef __LL_ADC_CALC_TEMPERATURE
#ifdef STM32U5xx
  return (__LL_ADC_CALC_TEMPERATURE(ADC1, VRef, analogRead(ATEMP), LL_ADC_RESOLUTION));
#else
  return (__LL_ADC_CALC_TEMPERATURE(VRef, analogRead(ATEMP), LL_ADC_RESOLUTION));
#endif
#elif defined(__LL_ADC_CALC_TEMPERATURE_TYP_PARAMS)
  return (__LL_ADC_CALC_TEMPERATURE_TYP_PARAMS(AVG_SLOPE, V25, CALX_TEMP, VRef, analogRead(ATEMP), LL_ADC_RESOLUTION));
#else
  return 0;
#endif
}
#endif

static int32_t readVoltage(int32_t VRef, uint32_t pin)
{
#ifdef STM32U5xx
  return (__LL_ADC_CALC_DATA_TO_VOLTAGE(ADC1, VRef, analogRead(pin), LL_ADC_RESOLUTION));
#else
  return (__LL_ADC_CALC_DATA_TO_VOLTAGE(VRef, analogRead(pin), LL_ADC_RESOLUTION));
#endif
}