#include <Arduino.h>
#include "swap.h"

void Swap::init()
{
  //Initialize the swapfile
}
void Swap::create(String name, String value)
{
  //Create an entry
}
String Swap::read(String name)
{
  //Read an entry
}
void Swap::update(String name, String value)
{
  this.delete(name);
  this.create(name, value);
}
void Swap::delete(String name)
{
  //Delete an entry
}
