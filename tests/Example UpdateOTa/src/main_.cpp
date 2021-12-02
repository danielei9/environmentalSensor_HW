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