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

class Swap
{
  /**
   * Initializes the SWAP area on the SD card.
   */
  static void Swap::init()
  {
    // Check to see if swap exists
    if(SD.exists("/swap"))
    {
      // Attempt to remove it
      if(!SD.rmdir("/swap"))
      {
        // SWAP folder is not empty
        File root = SD.open("/swap/");
        Swap::clearFolder(root);
        if(SD.exists("/swap"))
        {
          Output::write("Error in SWAP: working directory not cleared.");
          // TODO: crash system
          while(true)
          {
            
          }
        }
      }
    }
    // Create the swap folder
    SD.mkdir("/swap");
    // Check to make sure that the swap folder was created
    Swap::ready();
  }
  /**
   * Recursivly removes all files from within a folder, then deletes it and returns.
   */
  static void Swap::clearFolder(File fldr)
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
        Swap::clearFolder(node);
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
  static String Swap::GetPath(String name)
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
  static void Swap::create(String name, String value)
  {
    // Make sure that swap is ready
    Swap::ready();
    // Check to see if variable already exists
    if(SD.exists(Swap::GetPath(name)))
    {
      // It does, so crash system
      Output::write("Error in SWAP: Tried to create a variable that already exists");
      // TODO: crash system
      while(true)
      {
        
      }
    }
    // Create new file handle for new swap file
    File newSwap = SD.open(Swap::GetPath(name), FILE_WRITE);
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
      Output::write("Error in SWAP: Could not open variable SWAP file. Check the medium for storage corruption");
      // TODO: crash system
      while(true)
      {
        
      }
    }
    
  }
  /**
   * Returns the value of the requested SWAP object.
   */
  static String Swap::read(String name)
  {
    // Make sure that swap is ready
    Swap::ready();
    // Check for special compile-time variables
    if(name == "$bootver")
    {
      return "v0.1.3";
    }
    // Check to see if variable exists
    if(!SD.exists(Swap::GetPath(name)))
    {
      // It doesn't, so crash the system
      Output::write("ERR: 0x7");
      // TODO: crash system
      while(true)
      {
        
      }
    }
    // Create IO handle
    File readSwap = SD.open(Swap::GetPath(name));
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
    Output::write("ERR: 0x8");
    // TODO: crash system
    while(true)
    {
      
    }
  }
  /**
   * Replaces the requested SWAP object with the given value.
   */
  static void Swap::update(String name, String value)
  {
    // Make sure swap is ready
    Swap::ready();
    // Delete old value
    Swap::sdelete(name);
    // Create new value
    Swap::create(name, value);
  }
  /**
   * Removes the requested SWAP object from the SWAP space.
   */
  static void Swap::sdelete(String name)
  {
    // Make sure swap is ready
    Swap::ready();
    // Check to see if file exists
    if(SD.exists(Swap::GetPath(name)))
    {
      // Remove file
      SD.remove(Swap::GetPath(name));
      return;
    }
    // IO error, crash the system
    Output::write("ERR: 0x9");
    // TODO: crash system
    while(true)
    {
      
    }
  }
  /**
   * Checks to see if the SWAP has been initialized. If not, it forces a system crash with swapcrash().
   */
  static void Swap::ready()
  {
    // Check if swap was initialized
    if(SD.exists("/swap"))
    {
      return;
    }
    // Swap not found, crash system
    Output::write("ERR: 0x6");
    // TODO: crash system
  }
}