#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "swap.h"

void swapinit()
{
  if(SD.exists("/swap"))
  {
    if(!SD.rmdir("/swap"))
    {
      outwrite("ERR: 0x5");
    }
  }
  SD.mkdir("/swap");
  swapready();
}
String swapGetPath(String name)
{
  String swp = "/swap/";
  String ext = ".swp";
  String result = swp + name + ext;
  return result;
}
void swapcreate(String name, String value)
{
  swapready();
  if(SD.exists(swapGetPath(name)))
  {
    outwrite("ERR: 0x6");
    swapcrash();
  }
  File newSwap = SD.open(swapGetPath(name), FILE_WRITE);
  if (newSwap)
  {
    newSwap.println(value);
    newSwap.close();
  }
  else
  {
    swapcrash();
  }
  
}
String swapread(String name)
{
  swapready();
  if(!SD.exists(swapGetPath(name)))
  {
    outwrite("ERR: 0x7");
    swapcrash();
  }
  File readSwap = SD.open(swapGetPath(name));
  if(readSwap)
  {
    String result = "";
    while (readSwap.available())
    {
        result += readSwap.read();
    }
    readSwap.close();
    return result;
  }
  outwrite("ERR: 0x8");
  swapcrash();
}
void swapupdate(String name, String value)
{
  swapready();
  swapdelete(name);
  swapcreate(name, value);
}
void swapdelete(String name)
{
  swapready();
  if(SD.exists(swapGetPath(name)))
  {
    SD.remove(swapGetPath(name));
    return;
  }
  outwrite("ERR: 0x9");
  swapcrash();
}
void swapcrash()
{
  outwrite("The SWAP module has failed!");
  while(true)
  {
    
  }
}
void swapready()
{
  if(SD.exists("/swap"))
  {
    return;
  }
  outwrite("ERR: 0x6");
  swapcrash();
}
