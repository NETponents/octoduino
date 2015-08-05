/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#include <Arduino.h>
#include <SD.h>
#include <SPI.h> // Required for PlatformIO
#include "output.h"

void outinit()
{
  // Initialize text logs on SD card
  File logger = SD.open("/log.txt");
  logger.println("Logging started");
}
void outwrite(String msg)
{
  // Print message to serial
  Serial.println(msg);
  // Also print message to logger
  File logger = SD.open("/log.txt");
  logger.println(msg);
  logger.close();
}
