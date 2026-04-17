/**
Version: 1a
Tecnocoli - 04/2026
jcoli - Jeferson Coli - jcoli@tecnocoli.com.br
STM32F407VET6 - Grown
**/
#include <Arduino.h>
#include<SPIMemory.h>

#include "defines.h"
#include "io_defines.h"
#include "tools.h"
#include "structures.h"

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

void save_on_flash_serv1a();

SPIFlash flash(EP_CS);
bool first = true;

uint8_t data_p[10] = {0,1,2,3,4,5,6,7,8,9};

extern var_grow var_grow_1[60];


bool flash_begin() {
  Serial.println("Flash begin ");
  flash.begin();
  // if (getID()){
  //   // eraseFlash();
  //   return true;
  // }else{
  //   return false;
  // }

  if (getID()) {
    // printLine();
    // printTab(7);
    // Serial.print("Testing library code");
    // printTab(3);
    // Serial.print("Function");
    // printTab(2);
    // Serial.print("Test result");
    // printTab(3);
    // Serial.print("Runtime");
    // eraseFlash();
    // Serial.println();
    // eraseSection(0, 72);
    // Serial.println();
    // eraseBlock64K(256);
    // Serial.println();
    // eraseBlock32K(256);
    // Serial.println();
    // eraseSector(512);
    // Serial.println();
    // writeArray(512, data_p, 10); 
    // Serial.println();
    // String d = "Shady&#@*!6565";
    // writeString(1024, d);
    // Serial.println();
    // writeFloat(512, 456.67);
    // Serial.println();
    // writeLong(512, 45879);
    // Serial.println();
    // writeShort(1024, 4578);
    // Serial.println();
    // writeByte(1048, 250);
    // save_on_flash_serv1a();
    return true;

  }else{
    Serial.println("Flash begin 1");
    return false;
  }

  

}

void save_on_flash_serv1a(){
    Serial.print("Save Flash");
    uint32_t addr;
    uint32_t data = 0;
    if (eraseSector(16384)){
        for (int i = 0; i <= 52; i++){
            addr = var_grow_1[i].eprom_address;
            data = 0;
            // Serial.print("Eprom 1 ");
            // Serial.print(i);
            // delay(50);
           
            if((writeShort(addr, data))){
                    Serial.print("Write 1 OK ");
                    Serial.print("save flash: ");
                    Serial.print(i);
                    Serial.print(" Eprom 1 ");
                    Serial.print(var_grow_1[i].descr);
                    Serial.print(" - ");
                    Serial.print(data);
                    Serial.print(" - ");
                    Serial.print(addr);
                    uint8_t ret = read_Byte(addr);
                    Serial.print(" - ");
                    Serial.println(ret);
                    delay(50);
            }else{
                    Serial.println("Write 1 not OK");
                    // Serial.print("Eprom 1 ");
                    // Serial.print(var_grow_1[i].descr);
                    // Serial.print(" - ");
                    // Serial.print(data);
                    // Serial.print(" - ");
                    // Serial.print(addr);
            }
        }
    }
}

bool eraseFlash() {
  bool ret= false;
  if (flash.eraseChip()) {
    ret = true;
  }else{
    ret = true;
  }
  
  return ret;
}

bool eraseBlock64K(u_int32_t addr) {
  bool ret= false;
  if (flash.eraseBlock64K(addr)) {
    ret = true;
  }else{
    ret = false;
  }
  return ret;
}

bool eraseBlock32K(u_int32_t addr) {
  bool ret= false;
  if (flash.eraseBlock32K(addr)) {
    ret = true;
  }else{
    ret = false;
  }
  return ret;
}

bool eraseSection(u_int32_t addr, uint16_t size) {
  bool ret= false;
  if (flash.eraseSection(addr, KB(size))) {
    ret = true;
  }else{
    ret = false;
  }
  return ret;
}

bool eraseSector(u_int32_t addr) {
  bool ret= false;
  if (flash.eraseSector(addr)) {
    ret = true;
  }else{
    ret = false;
  }
  return ret;
}

bool eraseBlock(u_int32_t addr, uint8_t size) {
  // Serial.println("erase block");
  bool ret = false;
  uint8_t data_read[size], data[size];
  for (uint16_t i = 0; i < size; i++) {
    data[i] = 0xFF;
    // Serial.print(data[i], HEX);
    // Serial.print(",");
  }
  //  Serial.println("");
  // Serial.println("erase block 2");
  flash.writeByteArray(addr, data, size);
  // delay(1000);
  flash.readByteArray(addr, data_read, size);
  for (uint16_t i = 0; i < size; i++) {
    if (data[i] != data_read[i]) {
      // Serial.print(data[i], HEX);
      // Serial.print(",");
      // Serial.println(data_read[i], HEX);
      // // ret = false;
    }
  }
  ret = true;
  return ret;
}



String read_String(uint32_t addr) {
  // Serial.println("read String");
  uint32_t char_test;
  char_test = flash.readChar(addr); 
  String data_read = "0";
  Serial.println(char_test, HEX);
  if ((char_test == 0xFF) || (char_test == NULL) || (char_test == 0xFFFFFFFF) ){
    return data_read;  
    // Serial.println("NULL");
  }else{
    // Serial.println("read String 2");
    flash.readStr(addr, data_read);
    return data_read;
  }
  return data_read;
  
}

uint8_t read_Byte(uint32_t addr){
  // Serial.println("read byte");
  uint8_t data_read, char_test;
  char_test = flash.readByte(addr); 
  // Serial.println(char_test, BIN);
  data_read = flash.readByte(addr);
  return data_read;
}

uint16_t read_long(uint32_t addr){
  // Serial.println("read byte");
  uint16_t data_read, char_test;
  char_test = flash.readByte(addr); 
  // Serial.println(char_test, BIN);
  data_read = flash.readShort(addr);
  return data_read;
}

uint32_t read_int(uint32_t addr){
  // Serial.println("read byte");
  uint32_t data_read, char_test;
  char_test = flash.readByte(addr); 
  // Serial.println(char_test, BIN);
  data_read = flash.readLong(addr);
  return data_read;
}

bool writeArray(u_int32_t addr, uint8_t data[], uint8_t size) {
  bool ret = false;
  uint8_t data_read[size];
  
  flash.writeByteArray(addr, data, size);
  flash.readByteArray(addr, data_read, size);
  for (uint16_t i = 0; i < size; i++) {
    if (data[i] != data_read[i]) {
      ret = false;
    }
  }
  ret = true;
  return ret;
}

bool writeString(uint32_t addr, String data) {
  bool ret= false;
  String data_read;
  flash.writeStr(addr, data);
  flash.readStr(addr, data_read);
  if (data == data_read) {
    ret = true;
  }else{
    ret = false;
  }
  return ret;
}

bool writeFloat(uint32_t addr, float data) {
  bool ret= false;
  float data_read;
  flash.writeFloat(addr, data);
  data_read = flash.readFloat(addr);
  if (data == data_read) {
    ret = true;
  }else{
    ret = false;
  }
  return ret;
}

bool writeLong(u_int32_t addr, long data) {
  bool ret= false;
  int32_t data_read;
  flash.writeLong(addr, data);
  data_read = flash.readLong(addr);
  if (data == data_read) {
    ret = true;
  }else{
    ret = false;
  }
  return ret;
}

bool writeShort(u_int32_t addr, int16_t data) {
  bool ret= false;
  int16_t data_read;
  flash.writeShort(addr, data);
  data_read = flash.readShort(addr);
  if (data == data_read) {
    ret = true;
  }else{
    ret = false;
  }
  return ret;
}

bool writeByte(u_int32_t addr, uint8_t data) {
  bool ret= false;
  u_int8_t data_read;
  flash.writeByte(addr, data);
  data_read = flash.readByte(addr);
  if (data == data_read) {
    ret = true;
  }else{
    ret = false;
  }
  // Serial.print("write byte");
  // Serial.print(", ");
  // Serial.print(data, BIN);
  // Serial.print(", ");
  // Serial.print(addr);
  // Serial.print(", ");
  // Serial.println(data_read, BIN);
   
  return ret;
}

bool powerDown() {
  bool ret= false;
  if (flash.powerDown()) {
    ret = true;
  }else{
    ret = false;
  }
  return ret;
}

bool powerUp() {
  bool ret= false;
  if (flash.powerUp()) {
    ret = true;
  }else{
    ret = false;
  }
  return ret;
}


//=========================================
//=========================================
//=========================================
//=========================================
//=========================================

void printLine() {
  Serial.println();
  for (uint8_t i = 0; i < 125; i++) {
    Serial.print("-");
  }
  Serial.println();
}

void printTab(uint8_t _times) {
  for (uint8_t i = 0; i < _times; i++) {
    Serial.print("\t");
  }
}

void pass(bool _status) {
  printTab(1);
  Serial.print("   ");
  if (_status) {
    Serial.print("PASS");
  }
  else {
    Serial.print("FAIL");
  }
  printTab(1);
}

void printUniqueID(void) {
  long long _uniqueID = flash.getUniqueID();
  if (_uniqueID) {
    Serial.print("Unique ID: ");
    Serial.print(uint32_t(_uniqueID / 1000000L));
    Serial.print(uint32_t(_uniqueID % 1000000L));
    Serial.print(", ");
    Serial.print("0x");
    Serial.print(uint32_t(_uniqueID >> 32), HEX);
    Serial.println(uint32_t(_uniqueID), HEX);
  }
}

bool getID() {
  Serial.println();
  Serial.print("SPIMemory Library version: ");
#ifdef LIBVER
  uint8_t _ver, _subver, _bugfix;
  flash.libver(&_ver, &_subver, &_bugfix);
  Serial.print(_ver);
  Serial.print(".");
  Serial.print(_subver);
  Serial.print(".");
  Serial.println(_bugfix);
#else
  Serial.println(F("< 2.5.0"));
#endif
  Serial.println();
  uint32_t JEDEC = flash.getJEDECID();
  if (!JEDEC) {
    Serial.println("No comms. Check wiring. Is chip supported? If unable to fix, raise an issue on Github");
    return false;
  }
  else {
    Serial.print("JEDEC ID: 0x");
    Serial.println(JEDEC, HEX);
    Serial.print("Man ID: 0x");
    Serial.println(uint8_t(JEDEC >> 16), HEX);
    Serial.print("Memory ID: 0x");
    Serial.println(uint8_t(JEDEC >> 8), HEX);
    Serial.print("Capacity: ");
    Serial.println(flash.getCapacity());
    Serial.print("Max Pages: ");
    Serial.println(flash.getMaxPage());
    printUniqueID();

  }
  return true;
}

void structTest() {
  struct Test {
    uint16_t s1;
    float s2;
    int32_t s3;
    bool s4;
    uint8_t s5;
    struct structOfStruct {
      uint8_t b1;
      float f2;
    } structofstruct;
  };
  Test _d;
  Test _data;

  _d.s1 = 31325;
  _d.s2 = 4.84;
  _d.s3 = 880932;
  _d.s4 = true;
  _d.s5 = 5;
  _d.structofstruct.b1 = 234;
  _d.structofstruct.f2 = 6.28;

  uint32_t wTime = 0;
  uint32_t addr, rTime;

  addr = random(0, 0xFFFFF);

  if (flash.writeAnything(addr, _d)) {
    wTime = flash.functionRunTime();
  }


  flash.readAnything(addr, _data);
  rTime = flash.functionRunTime();

  printTab(3);
  Serial.print ("Struct");
  printTab(2);
  if ((_d.s1 == _data.s1) && (_d.s2 == _data.s2) && (_d.s3 == _data.s3) && (_d.s4 == _data.s4) && (_d.s5 == _data.s5) && (_d.structofstruct.b1 == _data.structofstruct.b1) && (_d.structofstruct.b1 == _data.structofstruct.b1)) {
    pass(true);
  }
  else {
    pass(false);
  }
}


void uLongTest() {
  uint32_t wTime = 0;
  uint32_t rTime, addr;
  uint32_t _data, _d;
  _d = 876532;

  addr = random(0, 0xFFFFF);

  if (flash.writeULong(addr, _d)) {
    wTime = flash.functionRunTime();
  }


  _data = flash.readULong(addr);
  rTime = flash.functionRunTime();

  printTab(3);
  Serial.print ("ULong");
  printTab(2);
  if (_data == _d) {
    pass(true);
  }
  else {
    pass(false);
  }

}

void wordTest() {
  uint32_t wTime = 0;
  uint32_t rTime, addr;
  uint16_t _data, _d;
  _d = 4520;

  addr = random(0, 0xFFFFF);

  if (flash.writeWord(addr, _d)) {
    wTime = flash.functionRunTime();
  }


  _data = flash.readWord(addr);
  rTime = flash.functionRunTime();

  printTab(3);
  Serial.print ("Word");
  printTab(2);
  if (_data == _d) {
    pass(true);
  }
  else {
    pass(false);
  }
}

void charTest() {
  uint32_t wTime = 0;
  uint32_t rTime, addr;
  int8_t _data, _d;
  _d = -110;

  addr = random(0, 0xFFFFF);

  if (flash.writeChar(addr, _d)) {
    wTime = flash.functionRunTime();
  }


  _data = flash.readChar(addr);
  rTime = flash.functionRunTime();

  printTab(3);
  Serial.print ("Char");
  printTab(2);
  if (_data == _d) {
    pass(true);
  }
  else {
    pass(false);
  }

}






