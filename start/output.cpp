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
#ifdef IO_LOG_LCD
  #include <LiquidCrystal.h>
  
  LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
#endif

void outinit()
{
  // Initialize text logs on SD card
  #ifdef IO_LOG_SD
    File logger = SD.open("/log.txt");
    if(logger)
    {
      logger.println("Logging started");
      Serial.println("IO Channel: SD [OK]");
    }
    else
    {
      Serial.println("IO Channel: SD [FAIL]");
    }
  #endif
  #ifdef IO_LOG_LCD
    lcd.begin(16, 2);
    lcd.noCursor();
    Serial.println("IO Channel: LCD [OK]");
  #endif
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
  #ifdef IO_LOG_SD
    File logger = SD.open("/log.txt");
    logger.println(msg);
    logger.close();
  #endif
  #ifdef IO_LOG_SD
    lcd.clear();
    lcd.home();
    lcd.print("[");
    lcd.print(hr);
    lcd.print(":");
    lcd.print(mi);
    lcd.print(":");
    lcd.print(ms);
    lcd.print("] ");
    lcd.setCursor(0, 1);
    lcd.print(msg);
  #endif
}
