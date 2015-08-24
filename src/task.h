/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Protected under the GPL   //
// v2.0 license. Copyright 2015 NETponents.    //
/////////////////////////////////////////////////

#ifndef HEADER_TASK
  #define HEADER_TASK
  
  class Task
  {
    public:
      void Task(int);
      virtual void init();
      virtual void step();
      int getID();
    protected:
      extern int taskID;
  }
#endif