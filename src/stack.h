/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Protected under the GPL   //
// v2.0 license. Copyright 2015 NETponents.    //
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
