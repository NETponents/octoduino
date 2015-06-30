#ifndef HEADER_SWAP
  #define HEADER_SWAP
   
  class Swap{
    public:
      void init();
      void screate(String name, String value);
      char* sread(String name);
      void supdate(String name, String value);
      void sdelete(String name);
  };

#endif