/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Protected under the GPL   //
// v2.0 license. Copyright 2015 NETponents.    //
/////////////////////////////////////////////////

// No need for <Arduino.h>
#include <SD.h>
#include <SPI.h> // Required for PlatformIO
#include "core.h"
#include "output.h"

/**
 * Set up the system (required by Arduino).
 */
void setup()
{
  // Status LED
  pinMode(13, OUTPUT);
  // Initialize output class
  Output::init();
  #ifdef BUILDPIPE_BNUM
    Serial.println("Octoduino v0.2.0. Build: " + BUILDPIPE_BNUM);
  #else
    Serial.println("Octoduino v0.2.0. Build: local");
  #endif
  Serial.println("Copyright 2015 - NETponents");
  Serial.println("Distributed under the GNU GPL v2.0 license");
  Serial.println("Commercial use with this build of Octoduino is prohibited");
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
