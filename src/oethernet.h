/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Protected under the GPL   //
// v2.0 license. Copyright 2015 NETponents.    //
/////////////////////////////////////////////////

#include "task.h"
#include <Ethernet.h>
#include <Arduino.h>

#ifndef HEADER_OETHERNET
  #define HEADER_OETHERNET
  
  class oEthernet : public Task
  {
      public:
        oEthernet(int _ID);
        void init();
        void step();
      //private:
        //EthernetServer esvr = new EthernetServer(80);
  };
#endif