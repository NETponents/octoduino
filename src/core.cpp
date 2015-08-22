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


  /**
  * Initializes the system to execute the main PB file
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
    Output::write("Starting task manager...");
    #ifndef CORE_STACKSIZE
      #define CORE_STACKSIZE = 10
    #endif
    Task stack[CORE_STACKSIZE]
    // Included for debugging purposes
    Parse::start("/boot.pba");
  }
  void Task::init()
  {
    
  }
  void Task::step()
  {
    
  }
  }
  }

