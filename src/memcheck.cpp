///////////////////////////////////////////////////////////
// This software is provided "as is" with                //
// no warranty of any kind. Use this software            //
// at your own risk. Parts of this file were copied from //
// http://playground.arduino.cc/Code/AvailableMemory     //
// Protected under the GPL v2.0 license.                 //
// Copyright 2015 NETponents.                            //
///////////////////////////////////////////////////////////

#include <Arduino.h>
#include "crash.h"

int MEMCHECK::freeRam()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
}
void MEMCHECK::MEMCHECK(int _ID) : Task(_ID)
{
    // Nothing to initialize here
}
void MEMCHECK::step()
{
    if(freeRam() <= 20)
    {
        #ifdef CRASH_MSG_DETAIL
          Crash::forceHalt(F("Error: Out of RAM!"));
        #else
          Crash::forceHalt(F("Ex018"));
        #endif
    }
}