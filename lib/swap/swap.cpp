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
#include "output.h"

/**
 * Initializes the SWAP area on the SD card.
 */
void swapinit()
{
  // Check to see if swap exists
  if(SD.exists("/swap"))
  {
    // Attempt to remove it
    if(!SD.rmdir("/swap"))
    {
      // SWAP folder is not empty
      File root = SD.open("/swap/");
      clearFolder(root);
      if(SD.exists("/swap"))
      {
        outwrite("Error in SWAP: working directory not cleared.");
        swapcrash();
      }
    }
  }
  // Create the swap folder
  SD.mkdir("/swap");
  // Check to make sure that the swap folder was created
  swapready();
}
/**
 * Recursivly removes all files from within a folder, then deletes it and returns.
 */
void clearFolder(File fldr)
{
  while(true)
  {
    File node = fldr.openNextFile();
    if(!node)
    {
      // No more files found in directory
      break;
    }
    else if(node.isDirectory())
    {
      clearFolder(node);
      SD.rmdir(node.name());
    }
    else
    {
      SD.remove(node.name());
    }
  }
}
/**
 * Gets the full SWAP path of the requested variable.
 */
String swapGetPath(String name)
{
  // Add parts together
  String swp = "/swap/";
  String ext = ".swp";
  String result = swp + name + ext;
  // Return full filename
  return result;
}
/**
 * Creates a new swap object and assigns it the given value.
 */
void swapcreate(String name, String value)
{
  // Make sure that swap is ready
  swapready();
  // Check to see if variable already exists
  if(SD.exists(swapGetPath(name)))
  {
    // It does, so crash system
    outwrite("Error in SWAP: Tried to create a variable that already exists");
    swapcrash();
  }
  // Create new file handle for new swap file
  File newSwap = SD.open(swapGetPath(name), FILE_WRITE);
  // Check to see if we could open the file
  if (newSwap)
  {
    // Write value of item and close the handle
    newSwap.println(value);
    newSwap.close();
  }
  else
  {
    // IO error, crash the system
    outwrite("Error in SWAP: Could not open variable SWAP file. Check the medium for storage corruption");
    swapcrash();
  }
  
}
/**
 * Returns the value of the requested SWAP object.
 */
String swapread(String name)
{
  // Make sure that swap is ready
  swapready();
  // Check for special compile-time variables
  if(name == "$bootver")
  {
    return "v0.1.3";
  }
  // Check to see if variable exists
  if(!SD.exists(swapGetPath(name)))
  {
    // It doesn't, so crash the system
    outwrite("ERR: 0x7");
    swapcrash();
  }
  // Create IO handle
  File readSwap = SD.open(swapGetPath(name));
  // Check to see if IO handle was created
  if(readSwap)
  {
    // Create buffer
    String result = "";
    while (readSwap.available())
    {
        // Read characters from IO stream
        result += readSwap.read();
    }
    // Close handle
    readSwap.close();
    // Return swap variable value
    return result;
  }
  // IO error, crash system
  outwrite("ERR: 0x8");
  swapcrash();
}
/**
 * Replaces the requested SWAP object with the given value.
 */
void swapupdate(String name, String value)
{
  // Make sure swap is ready
  swapready();
  // Delete old value
  swapdelete(name);
  // Create new value
  swapcreate(name, value);
}
/**
 * Removes the requested SWAP object from the SWAP space.
 */
void swapdelete(String name)
{
  // Make sure swap is ready
  swapready();
  // Check to see if file exists
  if(SD.exists(swapGetPath(name)))
  {
    // Remove file
    SD.remove(swapGetPath(name));
    return;
  }
  // IO error, crash the system
  outwrite("ERR: 0x9");
  swapcrash();
}
/**
 * Crashes the system due to a SWAP error.
 */
void swapcrash()
{
  // Notify user of crash
  outwrite("The SWAP module has failed!");
  while(true)
  {
    // Do nothing until system is reset
  }
}
/**
 * Checks to see if the SWAP has been initialized. If not, it forces a system crash with swapcrash().
 */
void swapready()
{
  // Check if swap was initialized
  if(SD.exists("/swap"))
  {
    return;
  }
  // Swap not found, crash system
  outwrite("ERR: 0x6");
  swapcrash();
}
