#include <Arduino.h>
#include <SD.h>
#include <SPI.h>

void initBootstrap()
{
  pinMode(10, OUTPUT);
  SD.begin(4);
  //Begin parsing the PARSEBASIC main script
  Serial.println("Launching bootloader");
  File bootloader = SD.open("bootloader.pba");
  if(bootloader)
  {
    sPrintLn("Booting...");
    char terminator = ';';
    while (bootloader.available())
    {
      String cmd = "";
      while (char(bootloader.peek()) != terminator)
      {
        cmd += bootloader.read();
      }
      bootloader.read();
      parseBasic(cmd);
    }
    bootloader.close();
  }
  else
  {
    Serial.println("ERR: 0x4");
    return;
  }
}
