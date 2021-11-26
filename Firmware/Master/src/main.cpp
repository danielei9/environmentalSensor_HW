#include <Arduino.h>
#include <Wire.h>
#include <EEPROM.h>
#include <Adafruit_I2CDevice.h>
#include <Adafruit_GFX.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>
#include <FS.h>
#include <ESP32httpUpdate.h>
#include <../lib/IBM/src/lmic.h>
#include <../lib/IBM/src/hal/hal.h>
#include <../lib/SlaveController.h>
#include "../lib/CJMCU.h"
#define PROTOCOL_4G

uint8_t arrayData[52]; // array Data
SlaveController slaveController(21, 22);
unsigned long mill = 0;
<<<<<<< Updated upstream
#include <../lib/PublishersClient.h>
#include <SPI.h>
=======

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

void updateFromFS();
void printPercent(uint32_t readLength, uint32_t contentLength);
#include <CRC32.h>
#include "FS.h"
#include "SPIFFS.h"

void listDir(fs::FS &fs, const char *dirname, uint8_t levels);

//TinyGsmClientSecure client(modem);
const char server[] = "gesinen.es";
const int portServer = 80;
const char resource[] = "/firmware.bin"; //here de bin file

uint32_t knownFileSize = 1024; // In case server does not send it
void performUpdate(Stream &updateSource, size_t updateSize);
void readFile(fs::FS &fs, const char *path);

// Construct the modbus instance
Modbus modbus;
uint32_t knownCRC32 = 0x6f50d767;
>>>>>>> Stashed changes

// 33 SDA 32 SCL
void setup()
{
  publisher->initPublisher();
  slaveController.initMaster();
  // initCJM();

  if (!SPIFFS.begin(true))
  {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  SPIFFS.format();
  listDir(SPIFFS, "/", 0);
}

void loop()
{
  // getCJMData();
  if (publisher->join())
  {

    // if you get a connection, report back via serial:

    if (!client.connect(server, 80))
    {
      Serial.println(" fail");
      delay(5000);
      return;
    }

    client.println("GET https://www.gesinen.es/firmware.bin HTTP/1.0");
    client.println("Host: www.gesinen.es");
    client.println("Connection: close");
    client.println();

    long timeout = millis();
    while (!client.available())
    {
      if (millis() - timeout > 7000L)
      {
        Serial.println(">>> Client Timeout !");
        client.stop();
        delay(10000L);
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
      else if (line.length() == 0)
      {
        break;
      }
    }

    timeout = millis();
    uint32_t readLength = 0;
    CRC32 crc;

    unsigned long timeElapsed = millis();
    printPercent(readLength, contentLength);

    while (readLength < contentLength )
    {
<<<<<<< Updated upstream
      // get arrayData
      Serial.println("Requesting sensors data..");
      uint8_t bytesToRequest = 8;
      byte *arrayData = slaveController.requestMeasuresToSlave(0x20, bytesToRequest);
      printBytesArray(arrayData, bytesToRequest);
=======
      int i = 0;
      while (readLength < contentLength)
      {
        // Serial.println(" while (client.available())");
        // read file data to spiffs
        if (!file.print(char(client.read())))
        {
          Serial.println("Appending file");
        }
        int c = client.read();
        Serial.print((char)c); // COMMENT THis shit pls
        crc.update((char)c);   //
        readLength++;

        if (readLength % (contentLength / 13) == 0)
        {
          printPercent(readLength, contentLength);
        }
        timeout = millis();
      }
     
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
    for (int i = 0; i < 10; i++)
    {
      Serial.print(String(i) + "...");
      delay(1000);
    }

    readFile(SPIFFS, "/firmware.bin");

    updateFromFS();
>>>>>>> Stashed changes

    // Do nothing forevermoreContent-Type
    while (true)
    {
      delay(1000);
    }

    // if (timerTrue(mill, 10000))
    // {
    //   // get arrayData
    //   Serial.println("Requesting sensors data..");
    //   uint8_t bytesToRequest = 8;
    //   byte *arrayData = slaveController.requestMeasuresToSlave(0x20, bytesToRequest);

    //   float temp = modbus.getTemperature();
    //   Serial.println("Temperatura: ");
    //   Serial.println(temp);
    //   arrayData[5] = temp;

    //   float epsi = modbus.getEpsilon();
    //   Serial.println("Epsilon: ");
    //   Serial.println(epsi);
    //   arrayData[6] = epsi;

    //   float soil = modbus.getSoilMoisture();
    //   Serial.println("Soil: ");
    //   Serial.println(soil);
    //   arrayData[7] = soil;

    //   printBytesArray(arrayData, bytesToRequest);

    //   publisher->sendData(arrayData);
    //   mill = millis();
    // }
  }
  // slaveController.scanSlaves();
}

void appendFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Appending to file: %s\n", path);

  File file = fs.open(path, FILE_APPEND);
  if (!file)
  {
    Serial.println("Failed to open file for appending");
    return;
  }
  if (file.print(message))
  {
    Serial.println("APOK");
  }
  else
  {
    Serial.println("APX");
  }
}

void readFile(fs::FS &fs, const char *path)
{
  Serial.printf("Reading file: %s\n", path);

  File file = fs.open(path);
  if (!file || file.isDirectory())
  {
    Serial.println("Failed to open file for reading");
    return;
  }

  Serial.print("Read from file: ");
  while (file.available())
  {
    Serial.write(file.read());
    delayMicroseconds(100);
  }
}

void writeFile(fs::FS &fs, const char *path, const char *message)
{
  Serial.printf("Writing file: %s\n", path);

  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("Failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    Serial.println("File written");
  }
  else
  {
    Serial.println("Write failed");
  }
}

void listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
  Serial.printf("Listing directory: %s\n", dirname);

  File root = fs.open(dirname);
  if (!root)
  {
    Serial.println("Failed to open directory");
    return;
  }
  if (!root.isDirectory())
  {
    Serial.println("Not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file)
  {
    if (file.isDirectory())
    {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels)
      {
        listDir(fs, file.name(), levels - 1);
      }
    }
    else
    {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("  SIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}

void deleteFile(fs::FS &fs, const char *path)
{
  Serial.printf("Deleting file: %s\n", path);
  if (fs.remove(path))
  {
    Serial.println("File deleted");
  }
  else
  {
    Serial.println("Delete failed");
  }
}

void updateFromFS()
{
  File updateBin = SPIFFS.open("/firmware.bin");
  if (updateBin)
  {
    if (updateBin.isDirectory())
    {
      Serial.println("Directory error");
      updateBin.close();
      return;
    }

    size_t updateSize = updateBin.size();

    if (updateSize > 0)
    {
      Serial.println("Starting update");
      performUpdate(updateBin, updateSize);
    }
    else
    {
      Serial.println("Error, archivo vacío");
    }

    updateBin.close();

    // remove from dir
    //fs.remove("/update.bin");
  }
  else
  {
    Serial.println("no such binary");
  }
}

void performUpdate(Stream &updateSource, size_t updateSize)
{
  if (Update.begin(updateSize))
  {
    size_t written = Update.writeStream(updateSource);
    if (written == updateSize)
    {
      Serial.println("Writes : " + String(written) + " successfully");
    }
    else
    {
      Serial.println("Written only : " + String(written) + "/" + String(updateSize) + ". Retry?");
    }
    if (Update.end())
    {
      Serial.println("OTA finished!");
      if (Update.isFinished())
      {
        Serial.println("Restart ESP device!");
        ESP.restart();
      }
      else
      {
        Serial.println("OTA not fiished");
      }
    }
    else
    {
      Serial.println("Error occured #: " + String(Update.getError()));
    }
  }
  else
  {
    Serial.println("Cannot beggin update");
  }
}

void printPercent(uint32_t readLength, uint32_t contentLength)
{
  Serial.println("printPercent");
  // If we know the total length
  if (contentLength != -1)
  {
    Serial.print("\r ");
    Serial.print((100.0 * readLength) / contentLength);
    Serial.print('%');
  }
  else
  {
    Serial.println(readLength);
  }
}
