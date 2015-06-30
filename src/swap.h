#ifndef HEADER_SWAP
  #define HEADER_SWAP
   
  class Swap{
    public:
      void init();
      void create(String name, String value);
      String read(String name);
      void update(String name, String value);
      void delete(String name);
  };
