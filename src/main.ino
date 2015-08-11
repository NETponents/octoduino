/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

// No need for <Arduino.h>
#include <SD.h>
#include <SPI.h> // Required for PlatformIO
#include "bootstrap.h"
#include "output.h"

/**
 * Set up the system (required by Arduino).
 */
void setup()
{
  // Status LED
  pinMode(13, OUTPUT);
  // Open serial
  Serial.begin(9600);
  while(!Serial)
  {
    ; // Leonardo: wait for serial to connect
  }
  // Initialize output class
  outinit();
  outwrite("Octoduino v0.1.3. Build: " + BUILDPIPE_BNUM);
  outwrite("Copyright 2015 - NETponents");
  outwrite("Distributed under the GNU GPL v2.0 license");
  outwrite("Commercial use with this build of Octoduino is prohibited");
  // Start the bootloader
  initBootstrap();
}
/**
 * Loop (required by Arduino). Not used.
 */
void loop()
{
  // Do nothing until power is cut
}
