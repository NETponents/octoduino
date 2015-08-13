/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
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
