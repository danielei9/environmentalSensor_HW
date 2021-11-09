#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <../lib/IBM/src/lmic.h>
#include <../lib/IBM/src/hal/hal.h>
#include <../lib/SlaveController.h>

#define PROTOCOL_4G
uint8_t arrayData[52]; // array Data
unsigned long mill = 0;
#include <../lib/PublishersClient.h>

void setup()
{
  publisher->initPublisher();
}

void loop()
{
  if (publisher->join())
  {
    if (timerTrue(mill, 20000))
    {
      publisher->sendData(arrayData);
      mill = millis();
    }
  }
}
