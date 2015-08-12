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
    static void Swap::init();
    static void Swap::clearFolder(File fldr);
    static String Swap::GetPath(String name);
    static void Swap::create(String name, String value);
    static String Swap::read(String name);
    static void Swap::update(String name, String value);
    static void Swap::sdelete(String name);
    static void Swap::ready();
  }

#endif
