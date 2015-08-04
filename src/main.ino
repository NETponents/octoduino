#include <SD.h>
#include <SPI.h> // Required for PlatformIO
#include "bootstrap.h"
#include "output.h"

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
  outwrite("Octoduino v0.1.0");
  outwrite("Copyright 2015 - NETponents");
  outwrite("Distributed under the GNU GPL v2.0 license");
  outwrite("Commercial use with this build of Octoduino is prohibited");
  // Start the bootloader
  initBootstrap();
}
void loop()
{
  //Do nothing, fatal crash or end of program execution
}
