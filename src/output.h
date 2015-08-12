/////////////////////////////////////////////////
// This software is provided "as is" with      //
// no warranty of any kind. Use this software  //
// at your own risk. Distributed under the     //
// MIT license. Copyright 2015 Joshua Zenn.    //
/////////////////////////////////////////////////

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
      static int write(String msg);
  };
  #ifdef IO_LOG_SD
    class ch_SD
    {
      public:
        static int init();
        static int write(String msg);
	};
  #endif
  #ifdef IO_LOG_LCD
    class ch_LCD
    {
      public:
        static int init();
        static int write(String msg);
      private:
        Liquidcrystal lcd(12, 11, 5, 4, 3, 2);
	};
  #endif
#endif
