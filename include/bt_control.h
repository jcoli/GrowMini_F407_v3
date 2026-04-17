/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#ifndef __BT_CONTROL_H__
#define __BT_CONTROL_H__
 
void bt_begin();
void on_receive_bt(String line_in);
void setup_rtc(String msg);
void BTconnectionCheck();
void sendMsgBT();


#endif
