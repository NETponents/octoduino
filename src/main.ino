#include <SD.h>
#include <SPI.h>
#include "bootstrap.h"
#include "output.h"

void setup()
{
  pinMode(13, OUTPUT);
  Serial.begin(9600);
  while(!Serial)
  {
    ;
  }
  outinit();
  outwrite("Octoduino v0.1.0");
  outwrite("Copyright 2015 - NETponents");
  outwrite("Distributed under the GNU GPL v2.0 license");
  outwrite("Commercial use with this build of Octoduino is prohibited");
  initBootstrap();
}
void loop()
{
  //Do nothing, fatal crash or end of program execution
}
