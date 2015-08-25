/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Protected under the GPL   //
// v2.0 license. Copyright 2015 NETponents.    //
/////////////////////////////////////////////////

#include "task.h"
#include <SD.h>

#ifndef HEADER_PBPARSE 
  #define HEADER_PBPARSE
  
  class Parser : public Task
  {
    public:
      Parser(int _ID);
      void init();
      void step();
    private:
      File source;
  };
  
  class Parse
  {
  public:
	static void start(String filename);
    static void run(String line);
    class Opcode
    {
	public:
	  class IO
      {
	  public:
		static void PRINT(String _msg);
        static void PRINTV(String _var);
        static void NEWPRINT();
        class Ports
        {
		public:
          static void IO(String _port, String _state);
		};
        class Files
        {
		public:
          static void FILEWRITE(String _filepath, String _var);
          static void FILEREAD(String _filepath, String _var);
		};
	  };
      class Var
      {
	  public:
        class Strings
        {
		public:
          static void ADDS(String _s1, String _s2, String _store);
          static void GETC(String _srg, String _rchar, String _store);
		};
	  };
	  class System
      {
	  public:
        static void WAIT(String _pTime);
        static void EXTLOAD(String _filepath);
        static void END();
		class SWAP
		{
		public:
			static void CREATESWAP();
			static void NEW(String _name, String _value);
			static void DELETE(String _name);
			static void SET(String name, String _value);
		};
	  };
      class Logic
      {
	  public:
        static void IFE(String _op1, String _op2, String _sFile);
        static void IFNE(String _op1, String _op2, String _sFile);
	  };
	};
  };
  
#endif 
