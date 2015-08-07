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
  // Get time
  unsigned long ms = millis();
  unsigned long mi = ms / 1000;
  ms = ms % 1000;
  unsigned long hr = mi / 60;
  mi = mi % 60;
  String timestamp = "[" + hr.c_str() + ":" + mi.c_str() + ":" + ms.c_str() + "] ";
  msg = timestamp + msg;
  // Print message to serial
  Serial.println(msg);
  // Also print message to logger
  File logger = SD.open("/log.txt");
  logger.println(msg);
  logger.close();
}
