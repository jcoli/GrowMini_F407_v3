/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/

#include <Arduino.h>

#include "defines.h"
#include "io_defines.h"


byte StrToHex(char str[]);
byte toHexc(String s);
void split_msg_2(String msg);
void split_msg_3(String msg);
void split_msg_4(String msg);
void split_msg_5(String msg);
void split_msg_6(String msg);
void split_msg_7(String msg);
void split_msg_8(String msg);
void split_msg_9(String msg);
void split_msg_10(String msg);

extern String retMsg2[2];
extern String retMsg3[3];
extern String retMsg4[4];
extern String retMsg5[5];
extern String retMsg6[6];
extern String retMsg7[7];
extern String retMsg8[8];
extern String retMsg9[9];
extern String retMsg10[10];

byte StrToHex(char str[])
  {return (byte) strtol(str, 0, 16);}

byte toHexc(String s){
  String tmp = "";
  char xhex[6];
  tmp = s;  xhex[tmp.length()+2]; tmp.toCharArray(xhex, tmp.length()+2);
  return (byte) StrToHex(xhex);
  
//  tmp = hex2str(xhex).toInt();
//  xhex[tmp.length()+2]; tmp.toCharArray(xhex, tmp.length()+2);
//  rchar[0] ;
//  xhex = (char*)tmp;
//  tmp.toCharArray(rchar, tmp.length());
//  return (byte) hex2str(xhex).toInt();
  
}

void split_msg_2(String msg){
    retMsg2[0] = "";
    retMsg2[1] = "";
    int j = 0;
    int p = 0;
    for(int i =0; i < msg.length(); i++){
       if(msg.charAt(i) == ','){
           retMsg2[p] = msg.substring(j, i);
           j = i +1;
           p++; 
       }
    }  
}

void split_msg_3(String msg){
    // Serial.println(msg);
    retMsg3[0] = "";
    retMsg3[1] = "";
    retMsg3[2] = "";
    int j = 0;
    int p = 0;
    for(int i =0; i < msg.length(); i++){
       if(msg.charAt(i) == ','){
           retMsg3[p] = msg.substring(j, i);
           j = i +1;
           p++;
       }
    }  
}

void split_msg_4(String msg){
    retMsg4[0] = "";
    retMsg4[1] = "";
    retMsg4[2] = "";
    retMsg4[3] = "";
    int j = 0;
    int p = 0;
    for(int i =0; i < msg.length(); i++){
       if(msg.charAt(i) == ','){
           String st = msg.substring(j, i);
           st.trim();
           retMsg4[p] = st;
           j = i +1;
           p++;
       }
    }  
}

void split_msg_5(String msg){
    retMsg5[0] = "";
    retMsg5[1] = "";
    retMsg5[2] = "";
    retMsg5[3] = "";
    retMsg5[4] = "";
    int j = 0;
    int p = 0;
    for(int i =0; i < msg.length(); i++){
       if(msg.charAt(i) == ','){
           retMsg5[p] = msg.substring(j, i);
           j = i +1;
           p++;
       }
    }  
}

void split_msg_6(String msg){
    retMsg6[0] = "";
    retMsg6[1] = "";
    retMsg6[2] = "";
    retMsg6[3] = "";
    retMsg6[4] = "";
    retMsg6[5] = "";
    int j = 0;
    int p = 0;
    for(int i =0; i < msg.length(); i++){
       if(msg.charAt(i) == ','){
           retMsg6[p] = msg.substring(j, i);
           j = i +1;
           p++;
       }
    }  
}

void split_msg_7(String msg){
    retMsg7[0] = "";
    retMsg7[1] = "";
    retMsg7[2] = "";
    retMsg7[3] = "";
    retMsg7[4] = "";
    retMsg7[5] = "";
    retMsg7[6] = "";
    int j = 0;
    int p = 0;
    for(int i =0; i < msg.length(); i++){
       if(msg.charAt(i) == ','){
           retMsg7[p] = msg.substring(j, i);
           j = i +1;
           p++;
       }
    }  
}

void split_msg_8(String msg){
    retMsg8[0] = "";
    retMsg8[1] = "";
    retMsg8[2] = "";
    retMsg8[3] = "";
    retMsg8[4] = "";
    retMsg8[5] = "";
    retMsg8[6] = "";
    retMsg8[7] = "";
    int j = 0;
    int p = 0;
    for(int i =0; i < msg.length(); i++){
       if(msg.charAt(i) == ','){
           retMsg8[p] = msg.substring(j, i);
           j = i +1;
           p++;
       }
    }  
}

void split_msg_9(String msg){
    retMsg9[0] = "";
    retMsg9[1] = "";
    retMsg9[2] = "";
    retMsg9[3] = "";
    retMsg9[4] = "";
    retMsg9[5] = "";
    retMsg9[6] = "";
    retMsg9[7] = "";
    retMsg9[8] = "";
    int j = 0;
    int p = 0;
    for(int i =0; i < msg.length(); i++){
       if(msg.charAt(i) == ','){
           retMsg9[p] = msg.substring(j, i);
           j = i +1;
           p++;
       }
    }  
}

void split_msg_10(String msg){
    // Serial.print("split 10: ");
    // Serial.println(msg); 
    retMsg10[0] = "";
    retMsg10[1] = "";
    retMsg10[2] = "";
    retMsg10[3] = "";
    retMsg10[4] = "";
    retMsg10[5] = "";
    retMsg10[6] = "";
    retMsg10[7] = "";
    retMsg10[8] = "";
    retMsg10[9] = "";
    // String msg = "9,0x09,4,1,10,2025,16,15,16,#";
    int j = 0;
    int p = 0;
    for(int i =0; i < msg.length(); i++){
       if(msg.charAt(i) == ','){
           retMsg10[p] = msg.substring(j, i);
        //    Serial.print(p);  
        //    Serial.print(" , ");     // Serial.print("split 10: ");
    // Serial.println(msg); 
        //    Serial.println(retMsg10[p]);  
           j = i +1;
           p++;
        //    Serial.println(msg.charAt(i)); 
       }
    
    }
    // Serial.println("split 10a"); 
    // Serial.println(retMsg10[0]);  
    // Serial.println(retMsg10[1]);
    // Serial.println(retMsg10[2]);
    // Serial.println(retMsg10[3]);
    // Serial.println(retMsg10[4]);
    // Serial.println(retMsg10[5]);
    // Serial.println(retMsg10[6]);
    // Serial.println(retMsg10[7]);
    // Serial.println(retMsg10[8]);
    // Serial.println(retMsg10[9]);
    
}

