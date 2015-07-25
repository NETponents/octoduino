#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "pbparse.h"
#include "swap.h"
#include "output.h"
#include "tokenizer.h"

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
    outwrite("ERR: 0x4");
    PBcrash();
  }
}
void PBparse(String line)
{
  if(line.startsWith("//"))
  {
    //Do nothing, this is a comment
  }
  else
  {
    String opcode = TKgetToken(line, 0);
    switch(opcode)
    {
      case "PRINT":
        outwrite(TKgetToken(line, 1));
        break;
      case "NEWPRINT":
        outwrite("\n");
        break;
      case "CREATESWAP":
        swapinit();
        break;
      case "IO":
        int portn = int(TKgetToken(line, 1).c_str());
        int state = int(TKgetToken(line, 2).c_str());
        if(state == '0')
        {
          digitalWrite(portn, LOW);
        }
        else
        {
          digitalWrite(portn, HIGH);
        }
        break;
      case "NEW":
        String value = TKgetToken(line, 2);
        if(value == "TKERROR")
        {
          value = "";
        }
        swapcreate(TKgetToken(line, 1), value);
        break;
      case "DELETE":
        swapdelete(TKgetToken(line, 1));
        break;
      case "SET":
        swapupdate(TKgetToken(line, 1), TKgetToken(line, 2));
        break;
      case "EXTLOAD":
        PBstart(TKgetToken(line, 1).c_str());
        break;
      case "END":
        PBstop();
        break;
      case "TKERROR":
        PBcrash();
        break;
      case default:
        PBcrash();
        break;
    }
  }
}
void PBstop()
{
  outwrite("Program has finished. Terminating.");
  while(true)
  {
    
  }
}
void PBcrash()
{
  outwrite("ParseBasic parser has encountered an error. Terminating.");
  while(true)
  {
    
  }
}
