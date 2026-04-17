/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#ifndef __EPROM_H__
#define __EPROM_H__

#include <Arduino.h>

bool flash_begin();

bool eraseFlash();
bool eraseBlock64K(u_int32_t addr);
bool eraseBlock32K(u_int32_t addr);
bool eraseSection(u_int32_t addr, uint16_t size);
bool eraseSector(u_int32_t addr);
bool eraseBlock(u_int32_t addr, uint8_t size);
bool writeArray(u_int32_t addr, uint8_t data[], uint8_t size);
bool writeString(uint32_t addr, String data);
bool writeFloat(uint32_t addr, float data);
bool writeLong(uint32_t addr, long data);
bool writeShort(u_int32_t addr, int16_t data);
bool writeByte(u_int32_t addr, uint8_t data);

uint8_t read_Byte(uint32_t addr);
uint16_t read_long(uint32_t addr);
uint32_t read_int(uint32_t addr);
String read_String(uint32_t addr);

bool powerDown();
bool powerUp();



void printLine();
void printTab(uint8_t _times);


void pass(bool _status);
void printUniqueID(void);
bool getID();
void charTest();
void wordTest();
void uLongTest();
void structTest();


#endif