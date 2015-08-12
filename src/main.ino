/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

// No need for <Arduino.h>
#include <SD.h>
#include <SPI.h> // Required for PlatformIO
#include "core.h"
#include "output.h"

#ifndef BUILDPIPE_BNUM
  #define BUILDPIPE_BNUM "local"
#endif

/**
 * Set up the system (required by Arduino).
 */
void setup()
{
  // Status LED
  pinMode(13, OUTPUT);
  // Initialize output class
  Output::init();
  Output::write("Octoduino v0.1.3. Build: " + BUILDPIPE_BNUM);
  Output::write("Copyright 2015 - NETponents");
  Output::write("Distributed under the GNU GPL v2.0 license");
  Output::write("Commercial use with this build of Octoduino is prohibited");
  // Start the bootloader
  Core::init();
}
/**
 * Loop (required by Arduino). Not used.
 */
void loop()
{
  // Do nothing until power is cut
}
