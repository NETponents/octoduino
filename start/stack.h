/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#ifndef HEADER_STACK
  #define HEADER_STACK
   
  void stackinit();
  void stackpush(String filepath);
  void stackpop(String filepath);
  String stackdump();

#endif
