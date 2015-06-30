#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "pbparse.h"

void initBootstrap()
{
  pinMode(10, OUTPUT);
  SD.begin(4);
  //Begin parsing the PARSEBASIC main script
  Serial.println("Launching bootloader");
  PBstart("boot/bootloader.pba");
  ///////////////////////////////////////////
}
