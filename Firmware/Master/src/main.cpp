#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <../lib/IBM/src/lmic.h>
#include <../lib/IBM/src/hal/hal.h>
#include <../lib/SlaveController.h>

#define PROTOCOL_4G

uint8_t arrayData[52]; // array Data
SlaveController slaveController(21, 22);

unsigned long mill = 0;
#include <../lib/PublishersClient.h>
#include <Wire.h>

void setup()
{
  // publisher->initPublisher();
  slaveController.initMaster();
}

void loop()
{

  // if (publisher->join())
  // {
  //   if (timerTrue(mill, 2000))
  //   {
  //     // publisher->sendData(arrayData);
  //     mill = millis();
  //   }
  // }
  // slaveController.scanSlaves();

  uint8_t bytesToRequest = 8;
  byte *arrayData = slaveController.requestMeasuresToSlave(0x20, bytesToRequest);
  printBytesArray(arrayData, bytesToRequest);
  delay(2000);
}
