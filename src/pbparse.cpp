#include <Arduino.h>
#include <SD.h>
#include <SPI.h>


void PBstart(String filename)
{
  File bootloader = SD.open(filename.c_str());
  if(bootloader)
  {
    char terminator = ';';
    while (bootloader.available())
    {
      String cmd = "";
      while (char(bootloader.peek()) != terminator)
      {
        cmd += bootloader.read();
      }
      bootloader.read();
      PBparse(cmd);
    }
    bootloader.close();
  }
  else
  {
    Serial.println("ERR: 0x4");
    PBcrash();
  }
}
void PBparse(String line)
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
void PBstop()
{
  Serial.println("Program has finished. Terminating.");
  while(true)
  {
    
  }
}
void PBcrash()
{
  Serial.println("ParseBasic parser has encountered an error. Terminating.");
  while(true)
  {
    
  }
}
