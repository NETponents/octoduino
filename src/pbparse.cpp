#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "pbparse.h"
#include "swap.h"

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
    swapinit();
  }
  else if(line.startsWith("NEW"))
  {
    line.remove("NEW ");
    String vname;
    for (int i=0; i < line.length(); i++)
    {
      if(line.charAt(i) == ' ')
      {
        return;
      }
      vname += line.charAt(i);
    }
    vname.remove('$');
    line.replace(vname, "");
    if(line.length() <= 1)
    {
      swapcreate(vname, "");
    }
    else
    {
      String vval = "";
      for (int i=1; i < line.length(); i++)
      {
        vval += line.charAt(i);
      }
      swapcreate(vname, vval);
    }
  }
  else if(line.startsWith("DELETE"))
  {
    line.replace("DELETE $", "");
    swapdelete(line);
  }
  else if(line.startsWith("SET"))
  {
    line.replace("SET $", "");
    String vname = "";
    for (int i=0; i < line.length(); i++)
    {
      if(line.charAt(i) == ' ')
      {
        return;
      }
      vname += line.charAt(i);
    }
    String vval = "";
    for (int i=1; i < line.length(); i++)
    {
      vval += line.charAt(i);
    }
    swapupdate(vname, vval);
  }
  else if(line.startsWith("EXTLOAD"))
  {
    line.replace("EXTLOAD ", "");
    PBstart(line.c_str());
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
