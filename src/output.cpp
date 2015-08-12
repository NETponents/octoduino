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
#endif

  /**
  * Initializes the output stream(s). The included streams are determined at compile-time to minimize memory use.
  */
  void Output::init()
  {
    // Initialize channels
    ch_Serial::init();
    #ifdef IO_LOG_SD
      ch_SD::init();
    #endif
    #ifdef IO_LOG_LCD
      ch_LCD::init();
    #endif
  }
  /**
  * Writes a String to all initialized output streams.
  */
  void Output::write(String msg)
  {
    // Get time (HH:MM:SS)
    unsigned long ms = millis();
    unsigned long mi = ms / 1000;
    ms = ms % 1000;
    unsigned long hr = mi / 60;
    mi = mi % 60;
    //msg = "[" + hr + ":" + mi + ":" + ms + "] " + msg;
    msg = sprintf("[%l:%l:%l] %s", hr, mi, ms, msg.c_str())
    ch_Serial::write(msg);
    #ifdef IO_LOG_SD
      ch_SD::write(msg);
    #endif
    #ifdef IO_LOG_LCD
      ch_LCD::write(msg);
    #endif
  }
/**
 * Output stream wrapper for Serial class provided by Wiring
 */

  /**
   * Waits for serial connection (if set through build args)
   */
  int ch_Serial::init()
  {
    // Open serial
    Serial.begin(9600);
    #ifdef IO_LOG_SERIAL
      while(!Serial)
      {
        ; // Wait for serial to connect (required for Leonardo)
      }
    #endif
    return 0;
  }
  /**
   * Writes given String object to Serial output.
   */
  int ch_Serial::write(String msg)
  {
    Serial.println(msg);
  }
#ifdef IO_LOG_SD
  /**
   * Output stream for logging on SD card.
   */
  
    /**
     * Opens SD card access and creates log file.
     */
    int ch_SD::init()
    {
      SD.begin(4);
      File logger = SD.open("/log.txt");
      if(!logger)
      {
        return 1;
      }
      logger.close();
      return 0;
    }
    /**
     * Opens log file and writes buffer string.
     */
    int ch_SD::write(String msg)
    {
      File logger = SD.open("/log.txt");
      if(!logger)
      {
        return 1;
      }
      logger.writeln(msg);
      logger.flush();
      logger.close();
      return 0;
    }
#endif
#ifdef IO_LOG_LCD
  /**
   * Output stream for Hitachi LCD screens
   */
  
    LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
    
    /**
     * Initialize LCD object.
     */
    int ch_LCD::init()
    {
      lcd.begin(16, 2);
      lcd.noCursor();
    }
    /**
     * Clears the screen, then writes output to the screen.
     */
    int ch_LCD::write(String msg)
    {
      lcd.clear();
      lcd.home();
      lcd.print(msg);
    }

#endif
