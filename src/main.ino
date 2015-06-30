#include <SD.h>
#include <SPI.h> 

bool ShowDebug = true;
bool fatalCrash = false;

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  sPrintLn("Octoduino build: ERR 0x1");
  sPrintLn("Copyright 2015 - NETponents");
  sPrintLn("Distributed under the GNU GPL v2.0 license");
  sPrintLn("Commercial use with this build of Octoduino is prohibited");
  sPrintLn("Initializing SD interface");
  pinMode(10, OUTPUT);
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
    sPrintLn("ERR: 0x4");
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
void parseBasic(String line)
{
  if(line.startsWith("//"))
  {
    //Do nothing, this is a comment
  }
  else if(line.startsWith("PRINT"))
  {
    while(true)
    {
      if(line.charAt(0) == '"')
      {
        line.remove(0);
        break;
      }
      else
      {
        line.remove(0);
      }
    }
    while(true)
    {
      if(line.charAt(0) == '"')
      {
        line.remove(0);
        break;
      }
      else
      {
        //Do nothing
      }
    }
    Serial.print(line);
  }
  else if(line.startsWith("NEWPRINT"))
  {
    Serial.print("\n");
  }
  else if(line.startsWith("CREATESWAP"))
  {
    //Create swap file and pass Stream<> handle
  }
  else if(line.startsWith("EXTLOAD"))
  {
    line.replace("EXTLOAD ", "");
    File newFile = SD.open(line.c_str());
    if(newFile)
    {
      char terminator = ';';
      while (newFile.available())
      {
        String cmd = "";
        while (char(newFile.peek()) != terminator)
        {
          cmd += newFile.read();
        }
        newFile.read();
        parseBasic(cmd);
      }
      newFile.close();
    }
    else
    {
      Serial.println("ERR: 0x4");
      PBcrash();
    }
  }
  else if(line.startsWith("END"))
  {
    PBstop();
  }
  else
  {
    PBcrash();
  }
}
void PBstop()
{
  Serial.println("Program has finished. Terminating.");
  digitalWrite(13, LOW);
  while(true)
  {
    
  }
}
void PBcrash()
{
  Serial.println("ParseBasic parser has encountered an error. Terminating.");
  digitalWrite(13, LOW);
  while(true)
  {
    
  }
}
void parseConfigLine(char line[])
{
  switch (line[0])
  {
    case '0':
      //Language
      //Language = (int)line[1];
      break;
    case '1':
      //Debug
      if(line[1] == '0')
      {
        ShowDebug = false;
      }
      else
      {
        ShowDebug = true;
      }
      break;
    case '2':
      //Do something
      break;
    case '3':
      //Do something
      break;
    default:
      Serial.println("ERR: 0x2");
  }
}
void sPrintLn(const char message[])
{
  Serial.println(message);
}
