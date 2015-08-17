/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#include <Arduino.h>
#include "stack.h"
#include "crash.h"

  /**
   * Forces a system halt (or reset if defined by compiler).
   */
  void Crash::forceHalt(String msg)
  {
    // Bad idea, may cause crash loop
    // Output::write(msg);
    Serial.println("");
    Serial.print("Error: ");
    Serial.println(msg);
    Serial.print("Stack dump: ");
    // Serial.println(Stack::dump());
    #ifdef CRASH_REBOOT
      Serial.println("Rebooting system...");
      asm volatile ("  jmp 0");
    #endif
    Serial.println("Halting system...");
    pinMode(13, OUTPUT);
    while(true)
    {
      digitalWrite(13, HIGH);
      delay(250);
      digitalWrite(13, LOW);
      delay(250);
    }
  }
