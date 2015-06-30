#include <SD.h>
#include <SPI.h>
#include "bootstrap.h"

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  sPrintLn("Octoduino build: ERR 0x1");
  sPrintLn("Copyright 2015 - NETponents");
  sPrintLn("Distributed under the GNU GPL v2.0 license");
  sPrintLn("Commercial use with this build of Octoduino is prohibited");
  initBootstrap();
}
void loop()
{
  //Do nothing, fatal crash or end of program execution
}
