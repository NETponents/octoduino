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
  // Get time (HH:MM:SS)
  unsigned long ms = millis();
  unsigned long mi = ms / 1000;
  ms = ms % 1000;
  unsigned long hr = mi / 60;
  mi = mi % 60;
  // Print message to serial
  Serial.print("[");
  Serial.print(hr);
  Serial.print(":");
  Serial.print(mi);
  Serial.print(":");
  Serial.print(ms);
  Serial.print("] ");
  Serial.println(msg);
  // Also print message to logger
  File logger = SD.open("/log.txt");
  logger.println(msg);
  logger.close();
}
