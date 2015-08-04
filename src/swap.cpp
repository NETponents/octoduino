#include <Arduino.h>
#include <SD.h>
#include <SPI.h> // Required for PlatformIO
#include "swap.h"
#include "output.h"

void swapinit()
{
  // Check to see if swap exists
  if(SD.exists("/swap"))
  {
    // Attempt to remove it
    if(!SD.rmdir("/swap"))
    {
      // Error, SWAP folder is not empty
      outwrite("ERR: 0x5");
    }
  }
  // Create the swap folder
  SD.mkdir("/swap");
  // Check to make sure that the swap folder was created
  swapready();
}
String swapGetPath(String name)
{
  // Add parts together
  String swp = "/swap/";
  String ext = ".swp";
  String result = swp + name + ext;
  // Return full filename
  return result;
}
void swapcreate(String name, String value)
{
  // Make sure that swap is ready
  swapready();
  // Check to see if variable already exists
  if(SD.exists(swapGetPath(name)))
  {
    // It does, so crash system
    outwrite("ERR: 0x6");
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
    swapcrash();
  }
  
}
String swapread(String name)
{
  // Make sure that swap is ready
  swapready();
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
void swapupdate(String name, String value)
{
  // Make sure swap is ready
  swapready();
  // Delete old value
  swapdelete(name);
  // Create new value
  swapcreate(name, value);
}
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
void swapcrash()
{
  // Notify user of crash
  outwrite("The SWAP module has failed!");
  while(true)
  {
    // Do nothing until system is reset
  }
}
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
