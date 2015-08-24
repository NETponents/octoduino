///////////////////////////////////////////////////////////
// This software is provided "as is" with                //
// no warranty of any kind. Use this software            //
// at your own risk. Parts of this file were copied from //
// http://playground.arduino.cc/Code/AvailableMemory     //
// Protected under the GPL v2.0 license.                 //
// Copyright 2015 NETponents.                            //
///////////////////////////////////////////////////////////

#include "task.h"

#ifndef HEADER_MEMCHECK
  #define HEADER_MEMCHECK
  
  class MEMCHECK : public Task
  {
      public:
        MEMCHECK(int _ID);
        void init();
        void step();
      private:
        int freeRam();
  };
#endif