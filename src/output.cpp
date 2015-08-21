/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Protected under the GPL   //
// v2.0 license. Copyright 2015 NETponents.    //
/////////////////////////////////////////////////

#include <Arduino.h>
#include <SD.h>
#include <SPI.h> // Required for PlatformIO
#include "output.h"
#include "crash.h"
#ifdef IO_LOG_LCD
  #include <LiquidCrystal.h>
#endif

  /**
  * Initializes the output stream(s).
  * The included streams are determined at compile-time to minimize memory use.
  * See *build options* docs page.
  */
  void Output::init()
  {
    // Initialize channels
    if(ch_Serial::init() != 0)
    {
      #ifdef CRASH_MSG_DETAIL
        Crash::forceHalt("Error initializing Serial output channel.");
      #else
        Crash::forceHalt("Ex001");
      #endif
    }
    #ifdef IO_LOG_SD
      if(ch_SD::init() != 0)
      {
        #ifdef CRASH_MSG_DETAIL
          Crash::forceHalt("Error initializing SD log output channel.");
        #else
          Crash::forceHalt("Ex002");
        #endif
      }
    #endif
    #ifdef IO_LOG_LCD
      if(ch_LCD::init() != 0)
      {
        #ifdef CRASH_MSG_DETAIL
          Crash::forceHalt("Error initializing LCD output channel.");
        #else
          Crash::forceHalt("Ex003");
        #endif
      }
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
    char buffer[12] = "";
    sprintf(buffer, "[%ld:%ld:%ld] ", hr, mi, ms);
    String timestamp = buffer;
    timestamp.trim();
    ch_Serial::write(timestamp, msg);
    #ifdef IO_LOG_SD
      if(ch_SD::write(timestamp, msg) != 0)
      {
        #ifdef CRASH_MSG_DETAIL
          Crash::forceHalt("Error writing to log on SD card.");
        #else
          Crash::forceHalt("Ex004");
        #endif
      }
    #endif
    #ifdef IO_LOG_LCD
      if(ch_LCD::write(timestamp, msg) != 0)
      {
        #ifdef CRASH_MSG_DETAIL
          Crash::forceHalt("Error outputting to LCD screen");
        #else
          Crash::forceHalt("Ex005");
        #endif
      }
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
  int ch_Serial::write(String timestamp, String msg)
  {
    Serial.print(timestamp);
    Serial.println(msg);
    return 0;
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
    int ch_SD::write(String timestamp, String msg)
    {
      File logger = SD.open("/log.txt");
      if(!logger)
      {
        return 1;
      }
      msg = timestamp + msg;
      logger.println(msg);
      logger.flush();
      logger.close();
      return 0;
    }
#endif
#ifdef IO_LOG_LCD
  /**
   * Output stream for Hitachi LCD screens
   */
  
    LiquidCrystal lcd(12, 11, 5, 6, 3, 2);
    
    /**
     * Initialize LCD object.
     */
    int ch_LCD::init()
    {
      lcd.begin(16, 2);
      lcd.noCursor();
      return 0;
    }
    /**
     * Clears the screen, then writes output to the screen.
     */
    int ch_LCD::write(String timestamp, String msg)
    {
      lcd.clear();
      lcd.home();
      lcd.print(timestamp);
      lcd.setCursor(0, 1);
      lcd.print(msg);
      return 0;
    }

#endif
