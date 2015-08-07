/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#include <Arduino.h>
#include <SD.h>
#include <SPI.h> // Required for PlatformIO
#include "pbparse.h"
#include "swap.h"
#include "output.h"
#include "tokenizer.h"

void PBstart(String filename)
{
  // Open file handle to source file
  File bootloader = SD.open(filename.c_str());
  // Check to see if file handle opened
  if(bootloader)
  {
    // Instruction terminator
    char terminator = ';';
    while (bootloader.available())
    {
      // Clear instruction buffer
      String cmd = "";
      // Read until you hit instruction terminator
      while (char(bootloader.peek()) != terminator)
      {
        cmd += bootloader.read();
      }
      // Read one more time to include instruction terminator
      cmd += bootloader.read();
      // Send the instruction for parsing
      PBparse(cmd);
    }
    // Close file handle
    bootloader.close();
  }
  else
  {
    // File handle could not be opened, crash the system
    outwrite("ERR: 0x4");
    PBcrash();
  }
}
void PBparse(String line)
{
  // Check if this line is a comment
  if(line.startsWith("//"))
  {
    //Do nothing, this is a comment
  }
  else
  {
    // Get opcode from instruction
    String opcode = TKgetToken(line, 0);
    // Check opcode against dictionary
    if(opcode == "PRINT")
    {
      outwrite(TKgetToken(line, 1));
    }
    else if(opcode == "PRINTV")
    {
      outwrite(swapread(TKgetToken(line, 1)));
    }
    else if(opcode == "ADDS")
    {
      swapupdate(TKgetToken(line, 3), TKgetToken(line, 1) + TKgetToken(line, 2));
    }
    else if(opcode == "GETC")
    {
      swapupdate(TKgetToken(line, 2), TKgetToken(line, 1).charAt(int(TKgetToken(line, 3).c_str())));
    }
    else if(opcode == "NEWPRINT")
    {
      outwrite("\n");
    }
    else if(opcode == "WAIT")
    {
      delay(int(TKgetToken(line, 1).c_str()));
    }
    else if(opcode == "IFE")
    {
      if(swapread(TKgetToken(line, 1)) == swapread(TKgetToken(line, 2)))
      {
        PBstart(TKgetToken(line, 3).c_str());
      }
    }
    else if(opcode == "IFNE")
    {
      if(swapread(TKgetToken(line, 1)) != swapread(TKgetToken(line, 2)))
      {
        PBstart(TKgetToken(line, 3).c_str());
      }
    }
    else if(opcode == "CREATESWAP")
    {
      swapinit();
    }
    else if(opcode == "IO")
    {
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
    }
    else if(opcode == "NEW")
    {
      String value = TKgetToken(line, 2);
      if(value == "TKERROR")
      {
        value = "";
      }
      swapcreate(TKgetToken(line, 1), value);
    }
    else if(opcode == "DELETE")
    {
      swapdelete(TKgetToken(line, 1));
    }
    else if(opcode == "SET")
    {
      swapupdate(TKgetToken(line, 1), TKgetToken(line, 2));
    }
    else if(opcode == "EXTLOAD")
    {
      PBstart(TKgetToken(line, 1).c_str());
    }
    else if(opcode == "FILEWRITE")
    {
      File extfile = SD.open(TKgetToken(line, 1), FILE_WRITE);
      if(extfile)
      {
        extfile.println(swapread(TKgetToken(line, 2)).c_str());
      }
      else
      {
        PBcrash();
      }
      extfile.close();
    }
    else if(opcode == "FILEREAD")
    {
      if (SD.exists(TKgetToken(line, 1)))
      {
        File extfile = SD.open(TKgetToken(line, 1), FILE_WRITE);
        if(extfile)
        {
          String readvar = "";
          while (extfile.available())
          {
            readvar = readvar + extfile.read();
          }
          swapupdate(TKgetToken(line, 2), readvar);
        }
        else
        {
          PBcrash();
        }
        extfile.close();
      }
      else
      {
        PBcrash();
      }
    }
    else if(opcode == "END")
    {
      // Program has requested that execution end
      PBstop();
    }
    else
    {
      PBcrash();
    }
  }
}
void PBstop()
{
  // Halt the program
  outwrite("Program has finished. Terminating.");
  while(true)
  {
    // Loop until power is reset
  }
}
void PBcrash()
{
  // System has crashed
  // Notify user
  outwrite("ParseBasic parser has encountered an error. Terminating.");
  while(true)
  {
    // Loop until power is reset
  }
}
