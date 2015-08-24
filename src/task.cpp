/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Protected under the GPL   //
// v2.0 license. Copyright 2015 NETponents.    //
/////////////////////////////////////////////////

#include <Arduino.h>
#include <Task.h>
  
int Task::taskID;
Task::Task(int _ID)
{
  taskID = _ID;
}
void Task::init()
{
    
}
void Task::step()
{
    
}
int Task::getID()
{
  return taskID;
}