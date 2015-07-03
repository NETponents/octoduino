#include <Arduino.h>
#include <SD.h>
#include <SPI.h>
#include "output.h"

void outinit()
{
  File logger = SD.open("/log.txt");
  logger.println("Logging started");
}
void outwrite(String msg)
{
  Serial.println(msg);
  File logger = SD.open("/log.txt");
  logger.println(msg);
  logger.close();
}
