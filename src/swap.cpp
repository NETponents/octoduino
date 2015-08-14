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
  void Swap::init()
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
  void Swap::clearFolder(File fldr)
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
  String Swap::GetPath(String name)
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
  void Swap::create(String name, String value)
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
  String Swap::read(String name)
  {
    // Make sure that swap is ready
    Swap::ready();
    // Check for special compile-time variables
    if(name == "$bootver")
    {
      return "v0.2.0a";
    }
    #ifdef SWAP_CONST_BOOL
      else if(name == "$CONST_true")
      {
        return "true";
      }
      else if(name == "$CONST_false")
      {
        return "false";
      }
    #endif
    #ifdef SWAP_CONST_NUM
      else if(name == "$CONST_1")
      {
        return "1";
      }
      else if(name == "$CONST_2")
      {
        return "2";
      }
      else if(name == "$CONST_3")
      {
        return "3";
      }
      else if(name == "$CONST_4")
      {
        return "4";
      }
      else if(name == "$CONST_5")
      {
        return "5";
      }
      else if(name == "$CONST_6")
      {
        return "6";
      }
      else if(name == "$CONST_7")
      {
        return "7";
      }
      else if(name == "$CONST_8")
      {
        return "8";
      }
      else if(name == "$CONST_9")
      {
        return "9";
      }
      else if(name == "$CONST_0")
      {
        return "0";
      }
    #endif
    else if(name == "$FEAT_SWAP_CONST")
    {
      #ifdef SWAP_CONST_BOOL
        #ifdef SWAP_CONST_NUM
          return "true";
        #endif
      #endif
      return false;
    }
    else if(name == "$FEAT_IO_Serial")
    {
      #ifdef IO_LOG_SERIAL
        return "true";
      #endif
      return "false";
    }
    else if(name == "$FEAT_IO_SD")
    {
      #ifdef IO_LOG_SD
        return "true";
      #endif
      return "false";
    }
    else if(name == "$FEAT_IO_LCD")
    {
      #ifdef IO_LOG_LCD
        return "true";
      #endif
      return "false";
    }
    else if(name == "$FEAT_CORE_STACK")
    {
      #ifdef CORE_STACK
        return "true";
      #endif
      return "false";
    }
    else if(name.startsWith("$PIN"))
    {
      int nPin = 0;
      sscanf(name.c_str(), "$PIN%02d", &nPin);
      pinMode(nPin, INPUT);
      String result = String(digitalRead(nPin));
      return result;
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
  void Swap::update(String name, String value)
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
  void Swap::sdelete(String name)
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
  void Swap::ready()
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
