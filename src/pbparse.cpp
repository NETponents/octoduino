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
#include "stack.h"

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
    Stack::push(filename);
    char terminator = ";";
    while(source.available())
    {
      String cmd = "";
      while(char(source.peek()) != terminator)
      {
        cmd += char(source.read());
      }
      source.read();
      Parse::run(cmd);
    }
    source.close();
    Stack::pop(filename);
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
      String opcode = Tokenizer::TKgetToken(line, 0);
      if(opcode == "PRINT") Parse::Opcode::IO::PRINT(Tokenizer::TKgetToken(line, 1));
      else if(opcode == "PRINTV") Parse::Opcode::IO::PRINTV(Tokenizer::TKgetToken(line, 1));
      else if(opcode == "ADDS") Parse::Opcode::Var::String::ADDS(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2), Tokenizer::TKgetToken(line, 3));
      else if(opcode == "GETC") Parse::Opcode::Var::String::GETC();
      else if(opcode == "NEWPRINT") Parse::Opcode::IO::NEWPRINT();
      else if(opcode == "WAIT") Parse::Opcode::System::WAIT(Tokenizer::TKgetToken(line, 1));
      else if(opcode == "IFE") Parse::Opcode::Logic::IFE(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2), Tokenizer::TKgetToken(line, 3));
      else if(opcode == "IFNE") Parse::Opcode::Logic::IFNE(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2), Tokenizer::TKgetToken(line, 3));
      else if(opcode == "CREATESWAP") Parse::Opcode::System::SWAP::CREATESWAP();
      else if(opcode == "IO") Parse::Opcode::IO::Ports::IO(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(linem 2));
      else if(opcode == "NEW") Parse::Opcode::System::SWAP::NEW(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2));
      else if(opcode == "DELETE") Parse::Opcode::System::SWAP::DELETE(Tokenizer::TKgetToken(line, 1));
      else if(opcode == "SET") Parse::Opcode::System::SWAP::SET(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2));
      else if(opcode == "EXTLOAD") Parse::Opcode::System::EXTLOAD(Tokenizer::TKgetToken(line, 1));
      else if(opcode == "FILEWRITE") Parse::Opcode::IO::File::FILEWRITE(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2));
      else if(opcode == "FILEREAD") Parse::Opcode::IO::File::FILEREAD(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2));
      else if(opcode == "END") Parse::Opcode::System::END();
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
      static void Parse::Opcode::IO::PRINT(String _msg)
      {
        Output::write(_msg);
      }
      static void Parse::Opcode::IO::PRINTV(String _var)
      {
        Output::write(Swap::read(_var));
      }
      static void Parse::Opcode::IO::NEWPRINT()
      {
        Output::write("\n");
      }
      class Ports
      {
        static void Parse::Opcode::IO::Ports::IO(String _port, String _state)
        {
          int _nPort = int(_port.c_str());
          int _nState = int(_state.c_str());
          pinMode(_nPort, OUTPUT);
          if(_state == 0)
          {
            digitalWrite(_nPort, LOW);
          }
          else
          {
            digitalWrite(_nPort, HIGH);
          }
        }
      }
      class File
      {
        static void Parse::Opcode::IO::File::FILEWRITE(String _filepath, String _var)
        {
          File _file = SD.open(_filepath, FILE_WRITE);
          if(_file)
          {
            _file.println(Swap::read(_var).c_str());
          }
          else
          {
            // TODO: crash system
            while(true)
            {
              
            }
          }
          _file.flush();
          _file.close();
        }
        static void Parse::Opcode::IO::File::FILEREAD(String _filepath, String _var)
        {
          if(!SD.exists(_filepath))
          {
            // TODO: crash system
            while(true)
            {
              
            }
          }
          String _readbuf = "";
          File _file = SD.open(_filepath, FILE_WRITE);
          if(!_file)
          {
            // TODO: crash system
            while(true)
            {
              
            }
          }
          while(_file.available())
          {
            _readbuf = _readbuf + _file.read();
          }
          Swap::update(_var, _readbuf);
          _file.close();
        }
      }
    }
    class Var
    {
      class String
      {
        static void Parse::Opcode::Var::String::ADDS(String _s1, String _s2, String _store)
        {
          Swap::update(_store, _s1 + _s2);
        }
        static void Parse::Opcode::String::ADDS::GETC(String _srg, String _rchar, String _store)
        {
          int _cindex = _rchar.toInt();
          Swap::update(_store, String(_srg.charAt(_cindex)));
        }
      }
    }
    class System
    {
      static void Parse::Opcode::System::WAIT(String _pTime)
      {
        delay(int(_pTime.c_str()));
      }
      static void Parse::Opcode::System::EXTLOAD(String _filepath)
      {
        Parse::start(_filepath);
      }
      static void Parse::Opcode::System::END()
      {
        // TODO: halt system
        while(true)
        {
          
        }
      }
      class SWAP
      {
        static void Parse::Opcode::System::SWAP::CREATESWAP()
        {
          // Do nothing since this is handled by Core::
          //swapinit();
        }
        static void Parse::Opcode::System::SWAP::NEW(String _name, String _value)
        {
          Swap::create(_name, _value);
        }
        static void Parse::Opcode::System::SWAP::DELETE(String _name)
        {
          Swap::sdelete(_name);
        }
        static void Parse::Opcode::System::SWAP::SET(String _name, String _value)
        {
          Swap::update(_name, _value);
        }
      }
    }
    class Logic
    {
      static void Parse::Opcode::Logic::IFE(String _op1, String _op2, String _sFile)
      {
        if(Swap::read(_op1) == Swap::read(_op2))
        {
          Parse::start(_sFile);
        }
      }
      static void Parse::Opcode::Logic::IFNE(String _op1, String _op2, String _sFile)
      {
        if(Swap::read(_op1) != Swap::read(_op2))
        {
          Parse::start(_sFile);
        }
      }
    }
  }
}
