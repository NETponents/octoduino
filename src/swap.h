/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Protected under the GPL   //
// v2.0 license. Copyright 2015 NETponents.    //
/////////////////////////////////////////////////

#ifndef HEADER_SWAP
  #define HEADER_SWAP
  
  class Swap
  {
    public:
		static void init();
		static void clearFolder(File fldr);
		static String GetPath(String name);
		static void create(String name, String value);
		static String read(String name);
		static void update(String name, String value);
		static void sdelete(String name);
		static void ready();
  };

#endif
