/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#include <Arduino.h> 
#include <SD.h> 
#include <SPI.h> // Required for PlatformIO
#include "swap.h"
#include "stack.h"

  /**
   * Initializes the stack object within the SWAP storage area.
   */
  void Stack::init()
  {
    #ifdef CORE_STACK
      Swap::create("OCTSTACK","");
    #endif
  }
  /**
   * Pushes a new layer onto the stack.
   */
  void Stack::push(String filepath)
  {
    #ifdef CORE_STACK
      String result = " -> ";
      result = Swap::read("OCTSTACK") + result + filepath;
      Swap::update("OCTSTACK", result);
    #endif
  }
  /**
   * Removes the highest instance of the requested program from the stack object.
   */
  void Stack::pop(String filepath)
  {
    #ifdef CORE_STACK
      String stackvar = Swap::read("OCTSTACK");
      stackvar.remove(stackvar.lastIndexOf(filepath), filepath.length());
      Swap::update("OCTSTACK", stackvar);
    #endif
  }
  /**
   * Returns a dump of the stack.
   */
  String Stack::dump()
  {
    String dump = "";
    #ifdef CORE_STACK
      dump = Swap::read("OCTOSTACK");
    #endif
    return dump;
  }
