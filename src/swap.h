/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#ifndef HEADER_SWAP
  #define HEADER_SWAP
   
  void swapinit();
  void clearFolder(File fldr);
  String swapGetPath(String name);
  void swapcreate(String name, String value);
  String swapread(String name);
  void swapupdate(String name, String value);
  void swapdelete(String name);
  void swapready();
  void swapcrash();

#endif
