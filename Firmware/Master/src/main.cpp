#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <../lib/IBM/src/lmic.h>
#include <../lib/IBM/src/hal/hal.h>
#include <../lib/SlaveController.h>
#include "../lib/CJMCU.h"
#define PROTOCOL_4G

uint8_t arrayData[52]; // array Data
SlaveController slaveController(21, 22);
unsigned long mill = 0;
#include <../lib/PublishersClient.h>
#include <SPI.h>

// 33 SDA 32 SCL
void setup()
{
  publisher->initPublisher();
  slaveController.initMaster();
  // initCJM();
}

void loop()
{
  // getCJMData();
  if (publisher->join())
  {
    if (timerTrue(mill, 10000))
    {
      // get arrayData
      Serial.println("Requesting sensors data..");
      uint8_t bytesToRequest = 8;
      byte *arrayData = slaveController.requestMeasuresToSlave(0x20, bytesToRequest);
      printBytesArray(arrayData, bytesToRequest);

      publisher->sendData(arrayData);
      mill = millis();
    }
  }
  // slaveController.scanSlaves();
}
