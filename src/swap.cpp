#include <Arduino.h>
#include "swap.h"

void swapinit()
{
  if(SD.exists("/swap"))
  {
    if(!SD.rmdir("/swap"))
    {
      Serial.println("ERR: 0x5");
    }
  }
  SD.mkdir("/swap");
  swapready();
}
void swapcreate(String name, String value)
{
  swapready();
  if(SD.exists("/swap/" + name.c_str + ".swp"))
  {
    Serial.println("ERR: 0x6");
    swapcrash();
  }
  File newSwap = SD.open("/swap/" + name.c_str + ".swp", FILE_WRITE);
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
char* swapread(String name)
{
  swapready();
  if(!SD.exists("/swap/" + name.c_str + ".swp"))
  {
    Serial.println("ERR: 0x7");
    swapcrash();
  }
  File readSwap = SD.open("/swap/" + name.c_str + ".swp");
  if(readSwap)
  {
    char result[];
    while (readSwap.available())
    {
        result += readSwap.read();
    }
    readSwap.close();
    return result;
  }
  Serial.println("ERR: 0x8");
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
  if(SD.exists("/swap/" + name.c_str + ".swp"))
  {
    SD.remove("/swap/" + name.c_str + ".swp");
    return;
  }
  Serial.println("ERR: 0x9");
  swapcrash();
}
void swapcrash()
{
  Serial.println("The SWAP module has failed!");
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
  Serial.println("ERR: 0x6");
  swapcrash();
}
