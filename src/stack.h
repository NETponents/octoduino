/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#ifndef HEADER_STACK
  #define HEADER_STACK
   
  class Stack
  {
  public:
	static void init();
    static void push(String filepath);
    static void pop(String filepath);
    static String dump();
  };

#endif
