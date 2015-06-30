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
void parseBasic(String line)
{
  if(line.startsWith("//"))
  {
    //Do nothing, this is a comment
  }
  else if(line.startsWith("PRINT"))
  {
    while(true)
    {
      if(line.charAt(0) == '"')
      {
        line.remove(0);
        break;
      }
      else
      {
        line.remove(0);
      }
    }
    while(true)
    {
      if(line.charAt(0) == '"')
      {
        line.remove(0);
        break;
      }
      else
      {
        //Do nothing
      }
    }
    Serial.print(line);
  }
  else if(line.startsWith("NEWPRINT"))
  {
    Serial.print("\n");
  }
  else if(line.startsWith("CREATESWAP"))
  {
    if (SD.exists("core.swap"))
    {
      SD.remove("core.swap");
    }
    File swap = SD.open("core.swap", FILE_WRITE);
    swap.close();
  }
  else if(line.startsWith("EXTLOAD"))
  {
    line.replace("EXTLOAD ", "");
    File newFile = SD.open(line.c_str());
    if(newFile)
    {
      char terminator = ';';
      while (newFile.available())
      {
        String cmd = "";
        while (char(newFile.peek()) != terminator)
        {
          cmd += newFile.read();
        }
        newFile.read();
        parseBasic(cmd);
      }
      newFile.close();
    }
    else
    {
      Serial.println("ERR: 0x4");
      PBcrash();
    }
  }
  else if(line.startsWith("END"))
  {
    PBstop();
  }
  else
  {
    PBcrash();
  }
}
