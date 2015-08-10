/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

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
  PBstart("/boot.pba");
}
