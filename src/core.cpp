/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Protected under the GPL   //
// v2.0 license. Copyright 2015 NETponents.    //
/////////////////////////////////////////////////

#include <Arduino.h>
#include <SD.h>
#include <SPI.h> //Required for PlatformIO
#include "pbparse.h"
#include "output.h"
#include "swap.h"
#include "core.h"
#include "task.h"
#include "memcheck.h"


  /**
  * Initializes a task manager to control all processes
  */
  void Core::init()
  {
    // Pre-req for SD class
    pinMode(10, OUTPUT);
    //Open SD card
    SD.begin(4);
    // Initialize SWAP
    Swap::init();
    //Begin parsing the PARSEBASIC main script
    Serial.println("Starting task manager...");
    #ifndef CORE_STACKSIZE
      Task stack[4];
    #else
      Task stack[CORE_STACKSIZE];
    #endif
    int _stackcounter = -1;
    Serial.println("Loading system tasks.");
    // Initialize class objects
    _stackcounter++;
    stack[_stackcounter] = MEMCHECK(_stackcounter);
    _stackcounter++;
    stack[_stackcounter] = Parser(_stackcounter);
    //_stackcounter++;
    //stack[_stackcounter] = new Ethernet(_stackcounter);
    //_stackcounter++;
    //stack[_stackcounter] = new Firmata(_stackcounter);
    
    // Init class objects
    for(int i = -1; i <= _stackcounter; i++)
    {
      stack[i].step();
    }
    // Loop step() class objects
    while(true)
    {
      for(int i = -1; i <= _stackcounter; i++)
      {
        stack[i].step();
      }
    }
    
    // Included for debugging purposes
    // Parse::start("/boot.pba");
  }

