#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <../lib/IBM/src/lmic.h>
#include <../lib/IBM/src/hal/hal.h>
#include <../lib/SlaveController.h>
#include "../lib/CJMCU.h"
#include "../lib/Modbus/Modbus.hpp"
#include "Adafruit_CCS811.h"
#include "Adafruit_GFX.h"
#include "ESP32httpUpdate.h"
#include "../lib/OTA/OTAU.hpp"

#define PROTOCOL_4G
#include <../lib/PublishersClient.h>
#include <SPI.h>
#include <SD.h>
#include <Ticker.h>
#include "../lib/GPS.hpp"

uint8_t arrayData[52]; // array Data
SlaveController slaveController(21, 22);
unsigned long mill = 0;

void initModbus();
void getModbusData();

#define TTGO_SOFTWARE_SERIAL 1 // If use ttgo
#define SENSOR_SUELO 1         // If we have sensor floor

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
uint32_t knownCRC32 = 0xD9971BA9;
// Construct the modbus instance
Modbus modbus;

// OTA
void updateFromFS();
void printPercent(uint32_t readLength, uint32_t contentLength);

void listDir(fs::FS &fs, const char *dirname, uint8_t levels);

const char server[] = "ycansam.upv.edu.es";
const int portServer = 443;
const char resource[] = "/firmware.bin"; //here de bin file

uint32_t knownFileSize = 1024; // In case server does not send it
void performUpdate(Stream &updateSource, size_t updateSize);
void readFile(fs::FS &fs, const char *path);
void OTAUpdate();

long contentLength; // How many bytes of data the .bin is
bool isValidContentType = false;
int readLength = 0;

GPS gps;

void setup()
{
  gps.init();
  // initModbus();
  // if (!SPIFFS.begin(true))
  // {
  //   Serial.println("SPIFFS Mount Failed");
  //   return;
  // }
  // SPIFFS.format();
  // listDir(SPIFFS, "/", 0);

  // publisher->initPublisher();
  //esp_tls_set_global_ca_store(certYcansam, sizeof(certYcansam));

  // slaveController.initMaster();
  // initCJM();

  // Set console baud rate
}
void loop()
{

  float *coords = gps.getCoords();
  delay(2000);
  // gps.getCoords();
  // getCJMData();
  // if (publisher->join())
  // {
  //   if (timerTrue(mill, 10000))
  //   {
  //     // get arrayData
  //     Serial.println("Requesting sensors data..");
  //     uint8_t bytesToRequest = 8;
  //     byte *arrayData = slaveController.requestMeasuresToSlave(0x20, bytesToRequest);
  //     getModbusData();

  //     printBytesArray(arrayData, bytesToRequest);

  //     publisher->sendData(arrayData);
  //     mill = millis();
  //   }
  // }
}
// slaveController.scanSlaves();
void getModbusData()
{
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
}

void OTAUpdate()
{
  Serial.print("Connecting to ");
  Serial.print(server);
  // if you get a connection, report back via serial:

  Serial.println(" OK");

  if (client.connect(server, portServer))
  {
    Serial.println("Fetching bin file at: " + String("https://ycansam.upv.edu.es/js/firmware.bin")); // tells where its going to get the .bin and the name its looking for

    // Get the contents of the bin file
    client.print(String("GET ") + "https://ycansam.upv.edu.es/js/firmware.bin" + " HTTP/1.1\r\n" +
                 "Host: " + String(server) + "\r\n" +
                 "Cache-Control: no-cache\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0)
    {
      if (millis() - timeout > 5000)
      {
        Serial.println("Client Timeout !");
        client.stop();
        return;
      }
    }
    Serial.println("Reading header");

    uint32_t contentLength = knownFileSize;

    File file = SPIFFS.open("/firmware.bin", FILE_APPEND);

    while (client.available())
    {
      String line = client.readStringUntil('\n');
      line.trim();
      Serial.println(line); // Uncomment this to show response header
      line.toLowerCase();
      if (line.startsWith("content-length:"))
      {
        contentLength = line.substring(line.lastIndexOf(':') + 1).toInt();
      }
      else if (line.length() <= 0)
      {
        break;
      }
    }

    timeout = millis();
    CRC32 crc;

    unsigned long timeElapsed = millis();
    // printPercent(readLength, contentLength);

    while (readLength < contentLength && client.connected() && millis() - timeout < 10000L)
    {
      while (client.available() && readLength < contentLength)
      {
        // read file data to spiffs
        int c = client.read();
        // client.write(file);
        file.print((char)c);
        crc.update((char)c);
        readLength++;

        printPercent(readLength, contentLength);
        timeout = millis();
      }
      if (client.available() <= 0)
        Serial.println("Client not Available");
      if (millis() - timeout < 9500L)
        Serial.println("TimeOut");
    }

    file.close();
    Serial.println("  file.close();");
    printPercent(readLength, contentLength);
    timeElapsed = millis() - timeElapsed;
    Serial.println();

    client.stop();
    Serial.println("stop client");

    modem.gprsDisconnect();
    Serial.println("gprs disconnect");
    Serial.println();

    float duration = float(timeElapsed) / 1000;

    Serial.print("Tamaño de Archivo: ");
    Serial.println(contentLength);
    Serial.print("Leido:  ");
    Serial.println(readLength);
    Serial.print("Calculado. CRC32:    0x");
    Serial.println(crc.finalize(), HEX);
    Serial.print("Conocido CRC32:    0x");
    Serial.println(knownCRC32, HEX);
    Serial.print("Bajado en:       ");
    Serial.print(duration);
    Serial.println("s");

    Serial.println("Se genera una espera de 3 segundos");
    for (int i = 0; i < 3; i++)
    {
      Serial.print(String(i + 1) + "...");
      delay(1000);
    }

    // Check if there is enough to OTA Update

    readFile(SPIFFS, "/firmware.bin");

    updateFromFS();

    // Do nothing forevermoreContent-Type
    while (true)
    {
      delay(1000);
    }
  }
}