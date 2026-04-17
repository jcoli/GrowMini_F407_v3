/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#ifndef __COMM_ESP_H__
#define __COMM_ESP_H__

void init_wifi();
void init_ble();
void init_mqtt();
void on_ser_comm(String line_in);
void addlistNetworks();
void listNetworks();
void call_list_net();
void send_esp_bt(String dest, String svc, String pid, String value);

#endif
