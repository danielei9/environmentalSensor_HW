#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <../lib/IBM/src/lmic.h>
#include <../lib/IBM/src/hal/hal.h>
#include <../lib/SlaveController.h>
#include "../lib/CJMCU.h"
#include "../lib/Modbus/Modbus.hpp"

#define PROTOCOL_4G
#include <../lib/PublishersClient.h>
#include <SPI.h>
uint8_t arrayData[52]; // array Data
SlaveController slaveController(21, 22);
unsigned long mill = 0;

#define TTGO_SOFTWARE_SERIAL 1 // If use ttgo
#define SENSOR_SUELO 1         // If we have sensor floor
#include <modbus.hpp>

#ifdef SENSOR_SUELO
//#define sensorPowerController 1
//#define adapterModbusPowerController 1
//#define DEBUG 1
#if defined(TTGO_SOFTWARE_SERIAL)
#include <SoftwareSerial.h>
#ifdef TTGO_SOFTWARE_SERIAL
const int SSRxPin = 32; // 2 Recieve pin for software serial (Rx on RS485 adapter)
const int SSTxPin = 33; // 3 Send pin for software serial (Tx on RS485 adapter)
#endif
SoftwareSerial modbusSerial(SSRxPin, SSTxPin);
#else
HardwareSerial modbusSerial = Serial1;
#endif
#endif

// Construct the modbus instance
Modbus modbus;

// 33 SDA 32 SCL
void setup()
{

#ifdef SENSOR_SUELO
// Controller Modbus interface
#ifdef TTGO_SOFTWARE_SERIAL
  if (DEREPin >= 0)
  {
    pinMode(DEREPin, OUTPUT);
  }
#endif
  // Controller PowerPin Sensor
#ifdef sensorPowerController
  if (sensorPwrPin >= 0)
  {
    pinMode(sensorPwrPin, OUTPUT);
    digitalWrite(sensorPwrPin, HIGH);
  }
#endif
  // Controller power modbus interface
#ifdef adapterModbusPowerController
  if (adapterPwrPin >= 0)
  {
    pinMode(adapterPwrPin, OUTPUT);
    digitalWrite(adapterPwrPin, HIGH);
  }
#endif

  // Turn on modbus serial port
#if defined(TTGO_SOFTWARE_SERIAL)
  modbusSerial.begin(9600);
#else
  Serial1.begin(modbusBaudRate, SERIAL_8O1);
#endif
  modbus.begin(0x01, modbusSerial, DEREPin);
#endif

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

      float temp = modbus.getTemperature();
      Serial.println("Temperatura: ");
      Serial.println(temp);
      arrayData[5] = temp;

      float epsi = modbus.getEpsilon();
      Serial.println("Epsilon: ");
      Serial.println(epsi);
      arrayData[6] = epsi;

      float soil = modbus.getSoilMoisture();
      Serial.println("Soil: ");
      Serial.println(soil);
      arrayData[7] = soil;


      printBytesArray(arrayData, bytesToRequest);

      publisher->sendData(arrayData);
      mill = millis();
    }
  }
  // slaveController.scanSlaves();
}
