#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include "crash.h"
#include "oethernet.h"

EthernetServer esvr(80);
oEthernet::oEthernet(int _ID) : Task(_ID)
{
    // Don't do anything since this is the universal initializer
}
/**
 * Initializes EthernetServer object. Obtains IP address.
 */
void oEthernet::init()
{
    // Initialize ethernet object
    byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
    IPAddress ip(192, 168, 1, 200);
    Ethernet.begin(mac, ip);
    this->esvr.begin();
    Serial.print("HTTP server open: ");
    Serial.println(Ethernet.localIP());
}
void oEthernet::step()
{
  EthernetClient client = this->esvr.available();
  if (client)
  {
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<h1>Not supported yet...</h1>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
    // close the connection:
    client.stop();
  }
}