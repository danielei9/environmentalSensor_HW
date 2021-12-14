// -*- mode: c++ -*-

// --------------------------------------------------------------
// Autor: Daniel Burruchaga Sola
// Date: 01 - 12 - 2021
// Name: Example OTA UPDATE
// Description: Clase Update OTA TEST 
// Se encarga de actualizar el firmware mediante 4G
// --------------------------------------------------------------

#include "Arduino.h"
#define DEBUG
#define PROTOCOL_4G
#include <../lib/PublishersClient.h>
#include <Wire.h>
#include <EEPROM.h>

#include "OTAUpdate.hpp"
OTAUpdate OTAUpd;
void setup()
{
    publisher->initPublisher();
    OTAUpd.init();
}
void loop()
{
    if (publisher->join())
        OTAUpd.updateFromServer();
}