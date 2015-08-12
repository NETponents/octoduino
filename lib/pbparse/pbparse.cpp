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
#include <swap.h>
#include <output.h>
#include <tokenizer.h>
#include <stack.h>

class Parse
{
  /**
   * Creates a runner to begin execution of a new source file.
   */
  static void Parse::start(String filename)
  {
    File source = SD.open(filename.c_str());
    if(!source)
    {
      // TODO: crash the system
      while(true)
      {
        
      }
    }
    stackpush(filename);
    char terminator = ";";
    while(source.available())
    {
      String cmd = "";
      while(char(source.peek()) != terminator)
      {
        cmd += char(source.read());
      }
      source.read();
      Parse.run(cmd);
    }
    source.close();
    stackpop(filename);
  }
  /**
   * Parses one line of trimmed PB code.
   */
  static void Parse::run(String line)
  {
    line.trim()
    if(line.startsWith("//"))
    {
      // Do nothing, this is a comment
    }
    else
    {
      String opcode = TKgetToken(line, 0);
      if(opcode == "PRINT") Opcode.IO.PRINT(TKgetToken(line, 1));
      else if(opcode == "PRINTV") Opcode.IO.PRINTV(TKgetToken(line, 1));
      else if(opcode == "ADDS") Opcode.Var.String.ADDS(TKgetToken(line, 1), TKgetToken(line, 2), TKgetToken(line, 3));
      else if(opcode == "GETC") Opcode.Var.String.GETC();
      else if(opcode == "NEWPRINT") Opcode.IO.NEWPRINT();
      else if(opcode == "WAIT") Opcode.System.WAIT(TKgetToken(line, 1));
      else if(opcode == "IFE") Opcode.Logic.IFE(TKgetToken(line, 1), TKgetToken(line, 2), TKgetToken(line, 3));
      else if(opcode == "IFNE") Opcode.Logic.IFNE(TKgetToken(line, 1), TKgetToken(line, 2), TKgetToken(line, 3));
      else if(opcode == "CREATESWAP") Opcode.System.SWAP.CREATESWAP();
      else if(opcode == "IO") Opcode.IO.Ports.IO(TKgetToken(line, 1), TKgetToken(linem 2));
      else if(opcode == "NEW") Opcode.System.SWAP.NEW(TKgetToken(line, 1), TKgetToken(line, 2));
      else
      {
        // TODO: crash program
        while(true)
        {
          
        }
      }
    }
  }
  class Opcode
  {
    class IO
    {
      static void PRINT(String msg)
      {
        Output.write(msg);
      }
      static void PRINTV(String var)
      {
        Output.write(swapread(var));
      }
      static void NEWPRINT()
      {
        Output.write("\n");
      }
      class Ports
      {
        static void IO(String port, String state)
        {
          int nPort = int(port.c_str());
          int nState = int(state.c_str());
          pinMode(nPort, OUTPUT);
          if(state == 0)
          {
            digitalWrite(nPort, LOW);
          }
          else
          {
            digitalWrite(nPort, HIGH);
          }
        }
      }
    }
    class Var
    {
      class String
      {
        static void ADDS(String s1, String s2, String store)
        {
          swapupdate(store, s1 + s2);
        }
        static void GETC(String srg, String rchar, String store)
        {
          int cindex = rchar.toInt();
          swapupdate(store, String(srg.charAt(cindex)));
        }
      }
    }
    class System
    {
      static void WAIT(String pTime)
      {
        delay(int(pTime.c_str()));
      }
      class SWAP
      {
        static void CREATESWAP()
        {
          swapinit();
        }
        static void NEW(String name, String value)
        {
          swapcreate(name, value);
        }
      }
    }
    class Logic
    {
      static void IFE(String op1, String op2, String sFile)
      {
        if(swapread(op1) == swapreaad(op2))
        {
          Parse.start(sFile);
        }
      }
       static void IFNE(String op1, String op2, String sFile)
      {
        if(swapread(op1) != swapreaad(op2))
        {
          Parse.start(sFile);
        }
      }
    }
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
/**
 * Halts the system safely by request of the program.
 */
void PBstop()
{
  // Halt the program
  outwrite("Program has finished. Terminating.");
  while(true)
  {
    // Loop until power is reset
  }
}
/**
 * Halts the system forcefully due to a software or hardware error.
 */
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
