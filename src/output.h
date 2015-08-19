/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

#ifdef IO_LOG_LCD
  #include <LiquidCrystal.h>
#endif

#ifndef HEADER_OSTREAM
  #define HEADER_OSTREAM
   
  class Output
  {
    public:
      static void init();
      static void write(String msg);
  };
  class ch_Serial
  {
    public:
      static int init();
	  static int write(String timestamp, String msg);
  };
  #ifdef IO_LOG_SD
    class ch_SD
    {
      public:
        static int init();
        static int write(String timestamp, String msg);
	};
  #endif
  #ifdef IO_LOG_LCD
    class ch_LCD
    {
      public:
        static int init();
	static int write(String timestamp, String msg);
      private:
        LiquidCrystal lcd;
	};
  #endif
#endif
