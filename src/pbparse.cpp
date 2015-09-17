/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Protected under the GPL   //
// v2.0 license. Copyright 2015 NETponents.    //
/////////////////////////////////////////////////

#include <Arduino.h>
#include <SD.h>
#include <SPI.h> // Required for PlatformIO
#include "pbparse.h"
#include "swap.h"
#include "output.h"
#include "tokenizer.h"
#include "stack.h"
#include "crash.h"
  
  File source;
  Parser::Parser(int _ID) : Task(_ID)
  {
    // Nothing to instance here
  }
  void Parser::init()
  {
    this->source = SD.open(F("/boot.pba"));
    if(!source)
    {
      #ifdef CRASH_MSG_DETAIL
        Crash::forceHalt("PB runner could not open file.");
      #else
        Crash::forceHalt("Ex006");
      #endif
    }
    Stack::push(F("/boot.pba"));
  }
  void Parser::step()
  {
    if(!this->source.available())
    {
      #ifdef CRASH_MSG_DETAIL
        Crash::forceHalt("End of script file.");
      #else
        Crash::forceHalt("Ex000");
      #endif
    }
    String cmd = "";
    const char terminator = ';';
    while(char(this->source.peek()) != terminator)
    {
      cmd += char(source.read());
    }
    this->source.read();
    Parse::run(cmd);
  }
  
  /**
   * Creates a runner to begin execution of a new source file.
   */
  void Parse::start(String filename)
  {
    File source = SD.open(filename.c_str());
    if(!source)
    {
      #ifdef CRASH_MSG_DETAIL
        Crash::forceHalt("PB runner could not open file.");
      #else
        Crash::forceHalt("Ex006");
      #endif
    }
    Stack::push(filename);
    const char terminator = ';';
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
  void Parse::run(String line)
  {
	line.trim();
    if(line.startsWith("//"))
    {
      // Do nothing, this is a comment
    }
    else
    {
      String opcode = Tokenizer::TKgetToken(line, 0);
      if(opcode == "PRINT") Parse::Opcode::IO::PRINT(Tokenizer::TKgetToken(line, 1));
      else if(opcode == "PRINTV") Parse::Opcode::IO::PRINTV(Tokenizer::TKgetToken(line, 1));
      else if(opcode == "ADDS") Parse::Opcode::Var::Strings::ADDS(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2), Tokenizer::TKgetToken(line, 3));
	  else if (opcode == "GETC") Parse::Opcode::Var::Strings::GETC(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2), Tokenizer::TKgetToken(line, 3));
      else if(opcode == "NEWPRINT") Parse::Opcode::IO::NEWPRINT();
      else if(opcode == "WAIT") Parse::Opcode::System::WAIT(Tokenizer::TKgetToken(line, 1));
      else if(opcode == "IFE") Parse::Opcode::Logic::IFE(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2), Tokenizer::TKgetToken(line, 3));
      else if(opcode == "IFNE") Parse::Opcode::Logic::IFNE(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2), Tokenizer::TKgetToken(line, 3));
      else if(opcode == "CREATESWAP") Parse::Opcode::System::SWAP::CREATESWAP();
      else if(opcode == "INCREMENT") Parse::Opcode::Math::Increment(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2));
      else if(opcode == "IO") Parse::Opcode::IO::Ports::IO(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2));
      else if(opcode == "NEW") Parse::Opcode::System::SWAP::NEW(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2));
      else if(opcode == "DELETE") Parse::Opcode::System::SWAP::DELETE(Tokenizer::TKgetToken(line, 1));
      else if(opcode == "SET") Parse::Opcode::System::SWAP::SET(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2));
      else if(opcode == "EXTLOAD") Parse::Opcode::System::EXTLOAD(Tokenizer::TKgetToken(line, 1));
      else if(opcode == "FILEWRITE") Parse::Opcode::IO::Files::FILEWRITE(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2));
      else if(opcode == "FILEREAD") Parse::Opcode::IO::Files::FILEREAD(Tokenizer::TKgetToken(line, 1), Tokenizer::TKgetToken(line, 2));
      else if(opcode == "END") Parse::Opcode::System::END();
      else
      {
        #ifdef CRASH_MSG_DETAIL
          Crash::forceHalt("Error, unrecognized command.");
        #else
          Crash::forceHalt("Ex007");
        #endif
      }
    }
  };

      /**
       * Prints a string to all configured output buffers.
       */
      void Parse::Opcode::IO::PRINT(String _msg)
      {
        Output::write(_msg);
      }
      /**
       * Prints a SWAP variable to all configured output buffers.
       */
      void Parse::Opcode::IO::PRINTV(String _var)
      {
        Output::write(Swap::read(_var));
      }
      /**
       * Prints a new line to the output stream.
       */
      void Parse::Opcode::IO::NEWPRINT()
      {
        Output::write("\n");
      }

        /**
         * Sets the requested pin to the specified state.
         */
        void Parse::Opcode::IO::Ports::IO(String _port, String _state)
        {
          int _nPort = int(_port.c_str());
          int _nState = int(_state.c_str());
          pinMode(_nPort, OUTPUT);
          if(_nState == 0)
          {
            digitalWrite(_nPort, LOW);
          }
          else
          {
            digitalWrite(_nPort, HIGH);
          }
        }
        
		/**
		 * Writes the requested string to an open file on SD card.
		 */
		void Parse::Opcode::IO::Files::FILEWRITE(String _filepath, String _var)
        {
          File _file = SD.open(_filepath, FILE_WRITE);
          if(_file)
          {
            _file.println(Swap::read(_var).c_str());
          }
          else
          {
            #ifdef CRASH_MSG_DETAIL
              Crash::forceHalt("Error writing to file on SD card.");
            #else
          		Crash::forceHalt("Ex008");
        		#endif
          }
          _file.flush();
          _file.close();
        }
        /**
         * Reads the requested file into SWAP buffer.
         */
        void Parse::Opcode::IO::Files::FILEREAD(String _filepath, String _var)
        {
          if(!SD.exists(_filepath))
          {
            #ifdef CRASH_MSG_DETAIL
          		Crash::forceHalt("File does not exist on SD card.");
        		#else
          		Crash::forceHalt("Ex009");
        		#endif
          }
          String _readbuf = "";
          File _file = SD.open(_filepath, FILE_WRITE);
          if(!_file)
          {
            #ifdef CRASH_MSG_DETAIL
          		Crash::forceHalt("Error reading from file on SD card.");
        		#else
          		Crash::forceHalt("Ex010");
        		#endif
          }
          while(_file.available())
          {
            _readbuf = _readbuf + _file.read();
          }
          Swap::update(_var, _readbuf);
          _file.close();
        }

        /**
         * Adds two strings together and stores them in a new variable.
         */
        void Parse::Opcode::Var::Strings::ADDS(String _s1, String _s2, String _store)
        {
          Swap::update(_store, _s1 + _s2);
        }
        /**
         * Gets the character from a string at specified index and stores it in SWAP.
         */
        void Parse::Opcode::Var::Strings::GETC(String _srg, String _rchar, String _store)
        {
          int _cindex = _rchar.toInt();
          Swap::update(_store, String(_srg.charAt(_cindex)));
        }

      /**
       * Pauses the system for a specified amount of time.
       */
      void Parse::Opcode::System::WAIT(String _pTime)
      {
        delay(int(_pTime.c_str()));
      }
      /**
       * Spawns a new runner task from the specified PB script file.
       */
      void Parse::Opcode::System::EXTLOAD(String _filepath)
      {
        //Parse::start(_filepath);
        Crash::forceHalt(F("EXTLOAD has been temporarily disabled."));
      }
      /**
       * Halts the system in a clean manner.
       */
      void Parse::Opcode::System::END()
      {
        #ifdef CRASH_MSG_DETAIL
          Crash::forceHalt("Program has been terminated by the script file.");
        #else
          Crash::forceHalt("Ex000");
        #endif
      }
		/**
		 * Increments a given variable by 1.
		 */
		void Parse::Opcode::Math(String _var)
		{
			int operand = 0;
			String _svar = "";
			_svar = Swap::read(_var);
			operand = int(_svar.c_str());
			operand++;
			Swap::update(_var, String(operand));
		}
        /**
         * DEPRECIATED: creates the swap directory.
         */
        void Parse::Opcode::System::SWAP::CREATESWAP()
        {
          // Do nothing since this is handled by Core::
          //swapinit();
        }
        /**
         * Creates a new SWAP variable.
         */
        void Parse::Opcode::System::SWAP::NEW(String _name, String _value)
        {
          Swap::create(_name, _value);
        }
        /**
         * Deletes a SWAP variable.
         */
        void Parse::Opcode::System::SWAP::DELETE(String _name)
        {
          Swap::sdelete(_name);
        }
        /**
         * Assigns a SWAP variable a new value.
         */
        void Parse::Opcode::System::SWAP::SET(String _name, String _value)
        {
          Swap::update(_name, _value);
        }

      /**
       * Checks if the given arguments are equal.
       * If they are, run `EXTLOAD` on the given script file.
       * If not, ignore and continue.
       */
      void Parse::Opcode::Logic::IFE(String _op1, String _op2, String _sFile)
      {
        if(Swap::read(_op1) == Swap::read(_op2))
        {
          //Parse::start(_sFile);
          Crash::forceHalt(F("EXTLOAD has been temporarily disabled."));
        }
      }
      /**
       * Checks if the given arguments are not equal.
       * If they are not equal, run `EXTLOAD` on the given script file.
       * If they are equal, ignore and continue.
       */
	    void Parse::Opcode::Logic::IFNE(String _op1, String _op2, String _sFile)
	    {
		    if (Swap::read(_op1) != Swap::read(_op2))
		    {
			    //Parse::start(_sFile);
			    Crash::forceHalt(F("EXTLOAD has been temporarily disabled."));
		    }
	    }
