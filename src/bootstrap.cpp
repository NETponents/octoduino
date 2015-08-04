#include <Arduino.h>
#include <SD.h>
#include <SPI.h> //Required for PlatformIO
#include "pbparse.h"
#include "output.h"

void initBootstrap()
{
  // Pre-req for SD class
  pinMode(10, OUTPUT);
  //Open SD card
  SD.begin(4);
  //Begin parsing the PARSEBASIC main script
  outwrite("Launching bootloader");
  PBstart("boot/bootloader.pba");
}
