int CIBUILDNUMBER = 0;
bool ShowDebug = true;

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
}
void loop()
{
  // Before script
  digitalWrite(13, HIGH);
  // Do stuff
  digitalWrite(13, LOW);
  // After script
}
void sPrintLn(char message[])
{
  Serial.println(message);
}
void sPrintLn(char message[], bool isDebug)
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
