#include <Arduino.h>
#include "swap.h"

void Swap::init()
{
  //Initialize the swapfile
}
void Swap::screate(String name, String value)
{
  //Create an entry
}
char[] Swap::sread(String name)
{
  //Read an entry
}
void Swap::supdate(String name, String value)
{
  this.sdelete(name);
  this.screate(name, value);
}
void Swap::sdelete(String name)
{
  //Delete an entry
}
