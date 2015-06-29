#include <SD.h>

int CIBUILDNUMBER = 0;
bool ShowDebug = true;
bool fatalCrash = false;

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  sPrintLn("Octoduino build: " + CIBUILDNUMBER);
  sPrintLn("Copyright 2015 - NETponents");
  sPrintLn("Distributed under the GNU GPL v2.0 license");
  sPrintLn("Commercial use with this build of Octoduino is prohibited");
  digitalWrite(13, LOW);
  sPrintLn("");
  digitalWrite(13, HIGH);
  sPrintLn("Starting up...");
  digitalWrite(13, LOW);
  sPrintLn("Initializing SD interface");
  pinMode(10, OUTPUT);
  if (!SD.begin(4))
  {
    sPrintLn("initialization failed!");
    fatalCrash = true;
    return;
  }
  File configFile = SD.open("octoduino.ini");
  if (configFile)
  {
    sPrintLn("Configuration file found");
    while (configFile.available())
    {
      sPrintLn(configFile.read());
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
    
  }
  else
  {
    // Before script
    digitalWrite(13, HIGH);
    // Do stuff
    digitalWrite(13, LOW);
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
