int CIBUILDNUMBER = 0;

void setup()
{
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);
  Serial.begin(9600);
  Serial.println("Octoduino build: " + CIBUILDNUMBER);
  Serial.println("Copyright 2015 - NETponents");
  Serial.println("Distributed under the GNU GPL v2.0 license");
  Serial.println("Commercial use with this build of Octoduino is prohibited");
  digitalWrite(13, LOW);
  Serial.println("");
  digitalWrite(13, HIGH);
  Serial.println("Starting up...");
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
