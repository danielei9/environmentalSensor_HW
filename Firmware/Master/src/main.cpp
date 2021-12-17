#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#define CFG_sx1276_radio 1 // HPD13A LoRa SoC

#include <../lib/MCCI LoRaWAN LMIC library/src/hal/hal.h>

#include <../lib/MCCI LoRaWAN LMIC library/src/lmic.h>
#include <SPI.h>

#include "../lib/CJMCU.h"
#include "../lib/Modbus/Modbus.hpp"
#include "Adafruit_CCS811.h"
#include "Adafruit_GFX.h"
#include "ESP32httpUpdate.h"

// Set serial for debug console (to Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set serial for AT commands (to SIM800 module)
#define SerialAT Serial1

// Configure TinyGSM library
#define TINY_GSM_MODEM_SIM7070  // Modem is SIM800
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
#include <TinyGsmClient.h>

// #define DUMP_AT_COMMANDS
#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif
// clang-format off
// upload_speed 921600
// board esp32dev

#ifndef _IBOXLORA_H
#define _IBOXLORA_H

#include <stdint.h>

#define CFG_sx1276_radio 1 // HPD13A LoRa SoC

// Pins for LORA chip SPI interface, reset line and interrupt lines
#define LORA_SCK  (18)
#define LORA_CS   (5)
#define LORA_MISO (19)
#define LORA_MOSI (23)
#define LORA_RST  (14) // old 15
#define LORA_IRQ  (2) // old 27
#define LORA_IO1  (32) // old 33
#define LORA_IO2  NOT_A_PIN

#endif
TinyGsmClientSecure client(modem);

#define PROTOCOL_4G
#include <../lib/PublishersClient.h>
#include <../lib/SlaveController.h>
#include <SPI.h>
#include <SD.h>
#include <Ticker.h>
#include "../lib/GPS.hpp"
#include "../lib/OTA/OTAUpdate.hpp"
#include <../lib/Sensor.h>
uint8_t arrayData[52]; // array Data
 Sensor sensorsModbus[4];

SlaveController slaveController(21, 22);
unsigned long mill = 0;

#define TTGO_SOFTWARE_SERIAL 1 // If use ttgo
#define SENSOR_SUELO 1         // If we have sensor floor
#define SENSOR_NOISE 1         // If we have sensor floor

#ifdef SENSOR_SUELO
//#define sensorPowerController 1
//#define adapterModbusPowerController 1
//#define DEBUG 1
#if defined(TTGO_SOFTWARE_SERIAL)
#include <SoftwareSerial.h>
#ifdef TTGO_SOFTWARE_SERIAL
const int SSRxPin = 15; // 2 Recieve pin for software serial (Rx on RS485 adapter)
const int SSTxPin = 13; // 3 Send pin for software serial (Tx on RS485 adapter)
#endif
SoftwareSerial modbusSerial(SSRxPin, SSTxPin);
#else
HardwareSerial modbusSerial = Serial1;
#endif
#endif

void initModbus();
void getModbusData();
uint32_t knownCRC32 = 0xD9971BA9;
// Construct the modbus instance
Modbus modbus;

// OTA
void updateFromFS();
void printPercent(uint32_t readLength, uint32_t contentLength);

void listDir(fs::FS &fs, const char *dirname, uint8_t levels);

const int portServer = 443;
const char resource[] = "/firmware.bin"; //here de bin file

uint32_t knownFileSize = 1024; // In case server does not send it
void performUpdate(Stream &updateSource, size_t updateSize);
void readFile(fs::FS &fs, const char *path);

long contentLength; // How many bytes of data the .bin is
bool isValidContentType = false;
int readLength = 0;

GPS gps;
void initModbus();
void setup()
{
  // gps.init();
  // initModbus();
  // if (!SPIFFS.begin(true))
  // {
  //   Serial.println("SPIFFS Mount Failed");
  //   return;
  // }
  // SPIFFS.format();
  // listDir(SPIFFS, "/", 0);

  publisher->initPublisher();
  //esp_tls_set_global_ca_store(certYcansam, sizeof(certYcansam));

  slaveController.initMaster();
  // initCJM();
  OTAUpd.init();
  // Set console baud rate
  Serial.println("Requesting in 20 seconds");
  Serial.begin(115200);
  initModbus();

}

void initModbus()
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

#ifdef SENSOR_NOISE
  modbus.changeAddrNoise();
#endif
}
bool key = true;
void loop()
{
  // float *coords = gps.getCoords();
  // gps.testLoop();
  // getCJMData();

  // slaveController.scanSlaves();

  if (publisher->join())
  {
    if (timerTrue(mill, 31000))
    {
      if(key){
  protocol4G.sendLinkMessage("deviceSync");
key = false;
      }

      //     // get arrayData
      Serial.println("Requesting sensors data..");
      uint8_t bytesToRequest = 24;
      byte *arrayData = slaveController.requestMeasuresToSlave(0x20, bytesToRequest);

      Serial.println("Received");
      getModbusData();

      printBytesArray(arrayData, bytesToRequest);
#ifdef PROTOCOL_4G
      publisher->sendData(arrayData);
#endif
#ifdef PROTOCOL_LORA
      Lora.sendData(&sendjob, arrayData, DATA_PORT, sizeof(arrayData));
#endif
      mill = millis();
    }
  }
}
void getModbusData()
{
  float temp = modbus.getTemperature();
  Serial.println("Temperatura: ");
  Serial.println(temp);
  arrayData[25] = temp;
  sensorsModbus[0] = Sensor(temp, "TEMP", "Cº");

  float epsi = modbus.getEpsilon();
  Serial.println("Epsilon: ");
  Serial.println(epsi);
  arrayData[26] = epsi;
  sensorsModbus[1] = Sensor(epsi, "EPSI", "espi");

  float soil = modbus.getSoilMoisture();
  Serial.println("Soil: ");
  Serial.println(soil);
  arrayData[27] = soil;
  sensorsModbus[2] = Sensor(soil, "SOIL", "%");

  float noise = modbus.getNoise();
  Serial.println("Noise: ");
  Serial.println(noise);
  arrayData[28] = noise;
  sensorsModbus[3] = Sensor(noise, "NOISE", "dB");
}
