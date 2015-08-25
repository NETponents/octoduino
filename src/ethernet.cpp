#include <Arduino.h>
#include "crash.h"
#include "ethernet.h"

Ethernet::Ethernet(int _ID) : Task(_ID)
{
    // Don't do anything since this is the universal initializer
}
void Ethernet::init()
{
    // Initialize ethernet objects
}
void Ethernet::step()
{
    // Check for clients
    // If there is one, send data
    // Close connection
}