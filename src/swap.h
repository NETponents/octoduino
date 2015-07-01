#ifndef HEADER_SWAP
  #define HEADER_SWAP
   
  void swapinit();
  String swapGetPath(String name);
  void swapcreate(String name, String value);
  String swapread(String name);
  void swapupdate(String name, String value);
  void swapdelete(String name);
  void swapready();
  void swapcrash();

#endif
