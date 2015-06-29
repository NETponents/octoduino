#include <SD.h>
#include <SPI.h> 

bool ShowDebug = true;
bool fatalCrash = false;

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  sPrintLn("Octoduino build: Error");
  sPrintLn("Copyright 2015 - NETponents");
  sPrintLn("Distributed under the GNU GPL v2.0 license");
  sPrintLn("Commercial use with this build of Octoduino is prohibited");
  sPrintLn("Initializing SD interface");
  pinMode(10, OUTPUT);
  if (!SD.begin(4))
  {
    sPrintLn("ERR 0x01");
    fatalCrash = true;
    return;
  }
  File configFile = SD.open("octoduino.ini");
  if (configFile)
  {
    sPrintLn("Configuration file found");
    while (configFile.available())
    {
      Serial.println(configFile.read());
    }
      configFile.close();
  }
  else
  {
    // if the file didn't open, print an error:
    sPrintLn("Error: octoduino.ini was not found.");
    fatalCrash = true;
    return;
  }
}
void loop()
{
  if(fatalCrash)
  {
    digitalWrite(13, LOW);
  }
  else
  {
    // Before script
    // Do stuff
    // After script
  }
}
void sPrintLn(const char message[])
{
  Serial.println(message);
}
void sPrintLn(const char message[], bool isDebug)
{
  if(isDebug)
  {
    if(ShowDebug)
    {
      Serial.println(message);
    }
  }
  else
  {
    Serial.println(message);
  }
}
