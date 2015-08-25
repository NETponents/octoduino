/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Protected under the GPL   //
// v2.0 license. Copyright 2015 NETponents.    //
/////////////////////////////////////////////////

#include "task.h"

#ifndef HEADER_ETHERNET
  #define HEADER_ETHERNET
  
  class Ethernet : public Task
  {
      public:
        Ethernet(int _ID);
        void init();
        void step();
  };
#endif