/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#ifndef HEADER_OUTPUT
  #define HEADER_OUTPUT
   
  class Output
  {
    public:
      static void Output::init();
      static void Output::write(String msg);
  }
  class ch_Serial
  {
    public:
      static int ch_Serial::init();
      static int ch_Serial::write(String msg);
  }
  #ifdef IO_LOG_SD
    class ch_SD
    {
      public:
        static int ch_SD::init();
        static int ch_SD::write(String msg);
    }
  #endif
  #ifdef IO_LOG_LCD
    class ch_LCD
    {
      public:
        static int ch_LCD::init();
        static int ch_LCD::write(String msg);
      private:
        Liquidcrystal lcd(12, 11, 5, 4, 3, 2);
    }
  #endif
#endif
