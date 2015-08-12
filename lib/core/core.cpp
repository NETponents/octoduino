/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#include <Arduino.h>
#include <SD.h>
#include <SPI.h> //Required for PlatformIO
#include "pbparse.h"
#include "output.h"

/**
 * Class that contains the core functions for controling threads on the system.
 */
class Core
{
  /**
  * Initializes the system to execute the main PB file
  */
  static void Core::init()
  {
    // Pre-req for SD class
    pinMode(10, OUTPUT);
    //Open SD card
    SD.begin(4);
    Swap::init();
    //Begin parsing the PARSEBASIC main script
    Output::write("Launching bootloader");
    Parse::start("/boot.pba");
  }
}
