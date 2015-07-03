#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "pbparse.h"
#include "output.h"

void initBootstrap()
{
  pinMode(10, OUTPUT);
  SD.begin(4);
  //Begin parsing the PARSEBASIC main script
  outwrite("Launching bootloader");
  PBstart("boot/bootloader.pba");
  ///////////////////////////////////////////
}
