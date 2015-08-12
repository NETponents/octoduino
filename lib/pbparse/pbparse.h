/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#ifndef HEADER_PBPARSE 
  #define HEADER_PBPARSE
  
  class Parse
  {
    static void start(String filename);
    static void run(String line);
    class Opcode
    {
      class IO
      {
        static void PRINT(String _msg);
        static void PRINTV(String _var);
        static void NEWPRINT();
        class Ports
        {
          static void IO(String _port, String _state);
        }
        class File
        {
          static void FILEWRITE(String _filepath, String _var);
          static void FILEREAD(String _filepath, String _var);
        }
      }
      class Var
      {
        class String
        {
          static void ADDS(String _s1, String _s2, String _store);
          static void GETC(String _srg, String _rchar, String _store);
        }
      }
      class System
      {
        static void WAIT(String _pTime);
        static void EXTLOAD(String _filepath);
        static void END();
        class SWAP
        {
          static void CREATESWAP();
          static void NEW(String _name, String _value);
          static void DELETE(_name);
          static void SET(_name, _value)
        }
      }
      class Logic
      {
        static void IFE(String _op1, String _op2, String _sFile);
        static void IFNE(String _op1, String _op2, String _sFile);
      }
    }
  }
  
#endif 
