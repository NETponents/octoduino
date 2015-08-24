///////////////////////////////////////////////////////////
// This software is provided "as is" with                //
// no warranty of any kind. Use this software            //
// at your own risk. Parts of this file were copied from //
// http://playground.arduino.cc/Code/AvailableMemory     //
// Protected under the GPL v2.0 license.                 //
// Copyright 2015 NETponents.                            //
///////////////////////////////////////////////////////////

#ifndef HEADER_MEMCHECK
  #define HEADER_MEMCHECK
  
  class MEMCHECK : public Task
  {
      public:
        void MEMCHECK(int _ID) : Task(_ID);
        void virtual step();
      private:
        int freeRam();
  };
#endif