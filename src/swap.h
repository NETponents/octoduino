#ifndef HEADER_SWAP
  #define HEADER_SWAP
   
  void swapinit();
  void swapcreate(String name, String value);
  char* swapread(String name);
  void swapupdate(String name, String value);
  void swapdelete(String name);
  void swapready();
  void swapcrash();

#endif