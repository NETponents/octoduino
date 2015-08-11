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

/**
 * Initializes the stack object within the SWAP storage area.
 */
void stackinit()
{
  #ifdef CORE_STACK
    swapcreate("OCTSTACK","");
  #endif
}
/**
 * Pushes a new layer onto the stack.
 */
void stackpush(String filepath)
{
  #ifdef CORE_STACK
    String result = " -> ";
    result = swapread("OCTSTACK") + result + filepath;
    swapupdate("OCTSTACK", result);
  #endif
}
/**
 * Removes the highest instance of thee requested program from the stack object.
 */
void stackpop(String filepath)
{
  #ifdef CORE_STACK
    String stackvar = swapread("OCTSTACK");
    stackvar.remove(stackvar.lastIndexOf(filepath), filepath.length());
    swapupdate("OCTSTACK", stackvar);
  #endif
}
/**
 * Returns a dump of the stack.
 */
String stackdump()
{
  String dump = "";
  #ifdef CORE_STACK
    dump = "";
  #endif
  return dump;
}
