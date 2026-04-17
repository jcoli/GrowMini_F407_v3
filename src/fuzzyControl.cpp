/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>
#include <Fuzzy.h>


#include "defines.h"
#include "tools.h"
#include "structures.h"
#include "io_defines.h"
#include "output_control.h"

void beginFuzzy();
void beginFuzzyAir();
void beginFuzzySoil();
void soilHumidityControl();
void airHumidityControl();

extern byte minutes;
extern byte hours;
extern byte weekDay ;
extern byte day;
extern byte month;
extern byte year;

extern unsigned long loopDelay_pump;

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


extern float vpd_int;
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
extern var_grow var_grow_2[20];
extern var_grow var_grow_3[20];
extern var_grow var_grow_4[20];
extern var_grow var_grow_5[20];
extern var_grow var_grow_6[20];
extern var_grow var_grow_7[20];
extern var_grow var_grow_8[20];
extern var_grow var_grow_9[20];
extern var_grow var_grow_A[20];

Fuzzy *fuzzyAir = new Fuzzy();
Fuzzy *fuzzySoil = new Fuzzy(); 

void beginFuzzy(){
    
    

    Serial.println("Sistema Fuzzy Iniciando");
    Serial.print("hum_int_min_stp: ");
    Serial.println(hum_int_min_stp);
    Serial.print("hum_int_max_stp: ");
    Serial.println(hum_int_min_stp);

    beginFuzzyAir();
    beginFuzzySoil();
    
}

void beginFuzzyAir(){
    FuzzyInput *airHhumidity = new FuzzyInput(1); // ID 1
    //Air Humidity
    FuzzySet *veryAirDry = new FuzzySet(0, 0, hum_int_min_stp, hum_int_min_stp+10);
    FuzzySet *airDry = new FuzzySet(hum_int_min_stp, hum_int_min_stp+10, hum_int_min_stp+20, hum_int_min_stp+30);
    FuzzySet *airIdeal = new FuzzySet(hum_int_min_stp+20, hum_int_min_stp+30, hum_int_max_stp-10, hum_int_max_stp);
    FuzzySet *airHumid = new FuzzySet(hum_int_max_stp-10, hum_int_max_stp, hum_int_max_stp+10, hum_int_max_stp+20);
    FuzzySet *veryAirHumid = new FuzzySet(hum_int_max_stp+10, hum_int_max_stp+20, 100, 100);

    
    // Adding the sets to the air input 
    airHhumidity->addFuzzySet(veryAirDry);
    airHhumidity->addFuzzySet(airDry);
    airHhumidity->addFuzzySet(airIdeal);
    airHhumidity->addFuzzySet(airHumid);
    airHhumidity->addFuzzySet(veryAirHumid);

    // Adding the input to the fuzzy system
    fuzzyAir->addFuzzyInput(airHhumidity);

    // Creating the output (airControl action)
    FuzzyOutput *airControl = new FuzzyOutput(1); // ID 1

    // Fuzzy sets for the action: Off, Hold, On
    FuzzySet *switchOffAir = new FuzzySet(0, 0, 0, 0.3);       // Singleton em 0, mas com uma pequena faixa para defuzzificação
    FuzzySet *maintainAir = new FuzzySet(0.4, 0.5, 0.5, 0.6);   // Triângulo em torno de 0.5
    FuzzySet *switchOnAir = new FuzzySet(0.7, 1, 1, 1);          // Singleton em 1, mas com uma pequena faixa

    // Adding the sets to the air output
    airControl->addFuzzySet(switchOffAir);
    airControl->addFuzzySet(maintainAir);
    airControl->addFuzzySet(switchOnAir);

    // Fuzzy air rules
    FuzzyRuleAntecedent *ifVeryAirDry = new FuzzyRuleAntecedent();
    ifVeryAirDry->joinSingle(veryAirDry);
    FuzzyRuleConsequent *thenSwitchOnAir = new FuzzyRuleConsequent();
    thenSwitchOnAir->addOutput(switchOnAir);
    FuzzyRule *ruleAir1 = new FuzzyRule(1, ifVeryAirDry, thenSwitchOnAir);
    fuzzyAir->addFuzzyRule(ruleAir1);

    FuzzyRuleAntecedent *ifAirDry = new FuzzyRuleAntecedent();
    ifAirDry->joinSingle(airDry);
    FuzzyRuleConsequent *thenAirKeep = new FuzzyRuleConsequent();
    thenAirKeep->addOutput(maintainAir);
    FuzzyRule *ruleAir2 = new FuzzyRule(2, ifAirDry, thenAirKeep);
    fuzzyAir->addFuzzyRule(ruleAir2);

    FuzzyRuleAntecedent *ifAirIdeal = new FuzzyRuleAntecedent();
    ifAirIdeal->joinSingle(airIdeal);
    FuzzyRule *ruleAir3 = new FuzzyRule(3, ifAirIdeal, thenAirKeep);
    fuzzyAir->addFuzzyRule(ruleAir3);

    FuzzyRuleAntecedent *ifAirHumid = new FuzzyRuleAntecedent();
    ifAirHumid->joinSingle(airHumid);
    FuzzyRule *ruleAir4 = new FuzzyRule(4, ifAirHumid, thenAirKeep);
    fuzzyAir->addFuzzyRule(ruleAir4);

    FuzzyRuleAntecedent *ifVeryAirHumid = new FuzzyRuleAntecedent();
    ifVeryAirHumid->joinSingle(veryAirHumid);
    FuzzyRuleConsequent *thenAirSwitchOff = new FuzzyRuleConsequent();
    thenAirSwitchOff->addOutput(switchOffAir);
    FuzzyRule *ruleAir5 = new FuzzyRule(5, ifVeryAirHumid, thenAirSwitchOff);
    fuzzyAir->addFuzzyRule(ruleAir5);

    Serial.println("✅ Sistema Fuzzy Air Inicializado");


}

void debugFuzzySoil() {
    Serial.println("\n🔍 DEBUG FUZZY SOIL CONFIGURATION:");
    Serial.print("Soil Humidity Value: ");
    Serial.println(soil_1_hum);
    Serial.print("Range: ");
    Serial.print(soil_hum_min_stp);
    Serial.print(" - ");
    Serial.println(soil_hum_max_stp);
    
    Serial.println("Expected Active Sets:");
    
    if (soil_1_hum <= soil_hum_min_stp + 10) {
        Serial.println("  ✅ verySoilDry should be active");
    }
    if (soil_1_hum >= soil_hum_min_stp && soil_1_hum <= soil_hum_min_stp + 30) {
        Serial.println("  ✅ soilDry should be active");
    }
    if (soil_1_hum >= soil_hum_min_stp + 20 && soil_1_hum <= soil_hum_max_stp) {
        Serial.println("  ✅ soilIdeal should be active");
    }
    if (soil_1_hum >= soil_hum_max_stp - 10 && soil_1_hum <= soil_hum_max_stp + 20) {
        Serial.println("  ✅ soilHumid should be active");
    }
    if (soil_1_hum >= soil_hum_max_stp + 10) {
        Serial.println("  ✅ verySoilHumid should be active");
    }
}

void beginFuzzySoil(){
    FuzzyInput *soilHumidity = new FuzzyInput(1);
    
    // CORREÇÃO: Ajuste dos conjuntos para valores baixos
    // Para umidade=1.00, precisamos de conjuntos que cubram essa faixa
    // FuzzySet *verySoilDry = new FuzzySet(0, 0, 15, 30);           // 0-30%
    // FuzzySet *soilDry = new FuzzySet(20, 30, 40, 50);             // 20-50%
    // FuzzySet *soilIdeal = new FuzzySet(45, 55, 65, 75);           // 45-75% 
    // FuzzySet *soilHumid = new FuzzySet(70, 75, 80, 85);           // 70-85%
    // FuzzySet *verySoilHumid = new FuzzySet(80, 85, 100, 100);     // 80-100%

    FuzzySet *verySoilDry = new FuzzySet(0, 0, soil_hum_min_stp, soil_hum_min_stp+10);
    FuzzySet *soilDry = new FuzzySet(soil_hum_min_stp, soil_hum_min_stp+10, soil_hum_min_stp+20, soil_hum_min_stp+30);
    FuzzySet *soilIdeal = new FuzzySet(soil_hum_min_stp+20, soil_hum_min_stp+30, soil_hum_max_stp-10, soil_hum_max_stp);
    FuzzySet *soilHumid = new FuzzySet(soil_hum_max_stp-10, soil_hum_max_stp, soil_hum_max_stp+10, soil_hum_max_stp+20);
    FuzzySet *verySoilHumid = new FuzzySet(soil_hum_max_stp+10, soil_hum_max_stp+20, 100, 100);

    // CORREÇÃO: Removida a duplicação e adicionado o conjunto correto
    soilHumidity->addFuzzySet(verySoilDry);
    soilHumidity->addFuzzySet(soilDry);
    soilHumidity->addFuzzySet(soilIdeal);
    soilHumidity->addFuzzySet(soilHumid);
    soilHumidity->addFuzzySet(verySoilHumid); // Este estava faltando!

    fuzzySoil->addFuzzyInput(soilHumidity);

    FuzzyOutput *soilControl = new FuzzyOutput(1);

    // CORREÇÃO: Conjuntos de saída mais adequados
    FuzzySet *switchOffSoil = new FuzzySet(0, 0, 10, 30);
    FuzzySet *maintainSoil = new FuzzySet(20, 40, 60, 80); 
    FuzzySet *switchOnSoil = new FuzzySet(70, 90, 100, 100);

    soilControl->addFuzzySet(switchOffSoil);
    soilControl->addFuzzySet(maintainSoil);
    soilControl->addFuzzySet(switchOnSoil);
    
    fuzzySoil->addFuzzyOutput(soilControl);

    // CORREÇÃO: Regras ajustadas
    // Rule 1: IF verySoilDry THEN switchOnSoil
    FuzzyRuleAntecedent *ifVerySoilDry = new FuzzyRuleAntecedent();
    ifVerySoilDry->joinSingle(verySoilDry);
    FuzzyRuleConsequent *thenSwitchOnSoil = new FuzzyRuleConsequent();
    thenSwitchOnSoil->addOutput(switchOnSoil);
    FuzzyRule *ruleSoil1 = new FuzzyRule(6, ifVerySoilDry, thenSwitchOnSoil);
    fuzzySoil->addFuzzyRule(ruleSoil1);

    // Rule 2: IF soilDry THEN switchOnSoil (mantém ligado)
    FuzzyRuleAntecedent *ifSoilDry = new FuzzyRuleAntecedent();
    ifSoilDry->joinSingle(soilDry);
    FuzzyRuleConsequent *thenSoilOn = new FuzzyRuleConsequent();
    thenSoilOn->addOutput(switchOnSoil);
    FuzzyRule *ruleSoil2 = new FuzzyRule(7, ifSoilDry, thenSoilOn);
    fuzzySoil->addFuzzyRule(ruleSoil2);

    // Rule 3: IF soilIdeal THEN maintainSoil
    FuzzyRuleAntecedent *ifSoilIdeal = new FuzzyRuleAntecedent();
    ifSoilIdeal->joinSingle(soilIdeal);
    FuzzyRuleConsequent *thenMaintainSoil = new FuzzyRuleConsequent();
    thenMaintainSoil->addOutput(maintainSoil);
    FuzzyRule *ruleSoil3 = new FuzzyRule(8, ifSoilIdeal, thenMaintainSoil);
    fuzzySoil->addFuzzyRule(ruleSoil3);

    // Rule 4: IF soilHumid THEN switchOffSoil
    FuzzyRuleAntecedent *ifSoilHumid = new FuzzyRuleAntecedent();
    ifSoilHumid->joinSingle(soilHumid);
    FuzzyRuleConsequent *thenSwitchOffSoil = new FuzzyRuleConsequent();
    thenSwitchOffSoil->addOutput(switchOffSoil);
    FuzzyRule *ruleSoil4 = new FuzzyRule(9, ifSoilHumid, thenSwitchOffSoil);
    fuzzySoil->addFuzzyRule(ruleSoil4);

    // Rule 5: IF verySoilHumid THEN switchOffSoil
    FuzzyRuleAntecedent *ifVerySoilHumid = new FuzzyRuleAntecedent();
    ifVerySoilHumid->joinSingle(verySoilHumid);
    FuzzyRuleConsequent *thenVerySwitchOff = new FuzzyRuleConsequent();
    thenVerySwitchOff->addOutput(switchOffSoil);
    FuzzyRule *ruleSoil5 = new FuzzyRule(10, ifVerySoilHumid, thenVerySwitchOff);
    fuzzySoil->addFuzzyRule(ruleSoil5);

    Serial.println("✅ Soil fuzzy rules initialized successfully");
}

void soilHumidityControl(){
    Serial.println("+++++++++++++++++++++++++++++++++++++");
    Serial.print("Soil Humidity: ");
    Serial.println(soil_1_hum);
    
    // DEBUG: Verifica qual conjunto deve estar ativo
    Serial.println("🔍 Fuzzy Set Analysis:");
    
    if (soil_1_hum <= 30) {
        Serial.println("  ✅ VERY_SOIL_DRY should be ACTIVE");
        Serial.println("  📌 Expected action: SWITCH ON PUMP");
    } else if (soil_1_hum <= 50) {
        Serial.println("  ✅ SOIL_DRY should be ACTIVE"); 
        Serial.println("  📌 Expected action: SWITCH ON PUMP");
    } else if (soil_1_hum <= 75) {
        Serial.println("  ✅ SOIL_IDEAL should be ACTIVE");
        Serial.println("  📌 Expected action: MAINTAIN");
    } else if (soil_1_hum <= 85) {
        Serial.println("  ✅ SOIL_HUMID should be ACTIVE");
        Serial.println("  📌 Expected action: SWITCH OFF");
    } else {
        Serial.println("  ✅ VERY_SOIL_HUMID should be ACTIVE");
        Serial.println("  📌 Expected action: SWITCH OFF");
    }

    // Configura e processa fuzzy
    fuzzySoil->setInput(1, soil_1_hum);
    fuzzySoil->fuzzify();
    float actionSoilHum = fuzzySoil->defuzzify(1);
    
    Serial.println("+++++++++++++++++++++++++++++++++++++");
    Serial.print("ActionSoilHum: ");
    Serial.println(actionSoilHum);
    Serial.print("Soil Hum: ");
    Serial.println(soil_1_hum);
    Serial.print("Min STP: ");
    Serial.println(soil_hum_min_stp);
    Serial.print("Max STP: ");
    Serial.println(soil_hum_max_stp);

    // Lógica de controle CORRIGIDA
    bool mustTurnOn = (actionSoilHum > 50.0); // Threshold de 50%

    Serial.print("Decision: ");
    Serial.println(mustTurnOn ? "TURN ON" : "TURN OFF");

    if (mustTurnOn && !pump_irr_on) {
        pump_irr_on = true;
        Serial.println("🚀 Switch On Pump Irrigation");
        loopDelay_pump = millis(); 
        
    } else if (!mustTurnOn && pump_irr_on) {
        pump_irr_on = false;
        Serial.println("💤 Switch Off Pump Irrigation");
    }

    // Safety override
    // if (!level_irrig_ll) {
    //     pump_irr_on = false;
    //     Serial.println("🛑 Safety: Low water level - Pump OFF");
    // }

    // Aplica controle físico
    // digitalWrite(PUMP1, pump_irr_on ? HIGH : LOW);
    
    Serial.println("+++++++++++++++++++++++++++++++++++++");
}
void airHumidityControl(){

     // Configura a entrada fuzzy
    fuzzyAir->setInput(1, hum_int);

    // Executa a fuzzyficação e a inferência
    fuzzyAir->fuzzify();

    // Obtém a saída defuzzyficada
    float actionHum = fuzzyAir->defuzzify(1);
    Serial.println("+++++++++++++++++++++++++++++++++++++");
    Serial.print("ActionHum: ");
    Serial.println(actionHum);
    Serial.print("Hum: ");
    Serial.println(hum_int);
    Serial.print("Min STP: ");
    Serial.println(hum_int_min_stp);
    Serial.print("Max STP: ");
    Serial.println(hum_int_max_stp);


    bool mustTurnOn = (actionHum > 0.5);

    // if (mustTurnOn && !hum_1_on) {
    //   hum_1_on = true;
    //   Serial.println("Ligando umidificador");
    // } else if (!mustTurnOn && hum_1_on) {
    //   hum_1_on = false;
    //   Serial.println("Desligando umidificador");
    // }

    // if (!level_hum_l){
    //     hum_1_on = false;
    //     Serial.println("hum fuzzy control off level L");
    // }


    // if (hum_1_on){
    //     digitalWrite(HUM, HIGH);
        
    // }else{
    //     digitalWrite(HUM, LOW);
    // }
    

    Serial.println("+++++++++++++++++++++++++++++++++++++");

}