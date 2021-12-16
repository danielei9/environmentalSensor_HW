// /* ----------------------------------------------------------------
//  *   AUTHOR:        Daniel Burruchaga Sola
//  *   FILE:           OTAUpdate.cpp
//  *   DATE:           22/11/2021
//  *   STATE:          DONE
//  *  ---------------------------------------------------------------- */
#pragma once
#define DEBUG
#include <Arduino.h>
#include "SPIFFS.h"
#include "ESP32httpUpdate.h"
#include <esp_tls.h>
#include "FS.h"
#include <CRC32.h>
const char server[] = "ycansam.upv.edu.es";

class OTAUpdate
{
private:
  const int portServer = 443;
  //uint32_t knownCRC32 = 0x6f50d767;
  uint32_t knownFileSize = 1024; // In case server does not send it
  long contentLength;            // How many bytes of data the .bin is
  bool isValidContentType = false;
  int readLength = 0;
  void updateFromFS();
  void printPercent(uint32_t readLength, uint32_t contentLength);
  void listDir(fs::FS &fs, const char *dirname, uint8_t levels);
  void performUpdate(Stream &updateSource, size_t updateSize);
  void readFile(fs::FS &fs, const char *path);
  void appendFile(fs::FS &fs, const char *path, const char *message);
  void writeFile(fs::FS &fs, const char *path, const char *message);
  void deleteFile(fs::FS &fs, const char *path);
  String getHeaderValue(String header, String headerName);
  

public:
  OTAUpdate();
  void init();
  void updateFromServer();
};

// DEBUG DEIFNE TO SHOW DATA DEBUG
#define DEBUG

  String updateUrl = "https://ycansam.upv.edu.es/js/firmware.bin";
// //----------------------------------------------------------------------------
// //                           PRIVATE FUNCTIONS
// //----------------------------------------------------------------------------
// Constructor
 OTAUpdate::OTAUpdate(){
 }
/**
     * appendFile to update
     * @param fs File bin with firmware
     * @param path path to find the file in the server 
     * @param message the content of the File 
     */
void OTAUpdate::appendFile(fs::FS &fs, const char *path, const char *message)
{
#ifdef DEBUG
      Serial.printf("Appending to file: %s\n", path);
#endif
      File file = fs.open(path, FILE_APPEND);
      if (!file)
      {
#ifdef DEBUG
            Serial.println("Failed to open file for appending");
#endif
            return;
      }
      if (file.print(message))
      {
#ifdef DEBUG
            Serial.println("APOK");
#endif
      }
      else
      {
#ifdef DEBUG
            Serial.println("APX");
#endif
      }
}
/**
     * Read the file
     * @param fs File bin with firmware
     * @param path path to find the file in the server 
     */
void OTAUpdate::readFile(fs::FS &fs, const char *path)
{
#ifdef DEBUG
      Serial.printf("Reading file: %s\n", path);
#endif

      File file = fs.open(path);

      if (!file || file.isDirectory())
      {
#ifdef DEBUG
            Serial.println("Failed to open file for reading");
#endif
            return;
      }
#ifdef DEBUG
      Serial.print("Read from file: ");
#endif
      while (file.available())
      {
#ifdef DEBUG
            Serial.write(file.read());
#endif
            delayMicroseconds(100);
      }
}

/**
     * Write bin File to update to mem
     * @param fs File bin with firmware
     * @param path path to find the file in the server 
     * @param message the content of the File 
     */
void OTAUpdate::writeFile(fs::FS &fs, const char *path, const char *message)
{
#ifdef DEBUG
      Serial.printf("Writing file: %s\n", path);
#endif
      File file = fs.open(path, FILE_WRITE);
      if (!file)
      {
#ifdef DEBUG
            Serial.println("Failed to open file for writing");
#endif
            return;
      }
      if (file.print(message))
      {
#ifdef DEBUG
            Serial.println("File written");
#endif
      }
      else
      {
#ifdef DEBUG
            Serial.println("Write failed");
#endif
      }
}

/**
     * Show directories
     * @param fs File bin with firmware
     * @param dirname name or the directory
     * @param levels levels to downgrade to search directory
     */
void OTAUpdate::listDir(fs::FS &fs, const char *dirname, uint8_t levels)
{
#ifdef DEBUG
      Serial.printf("Listing directory: %s\n", dirname);
#endif
      File root = fs.open(dirname);
      if (!root)
      {
#ifdef DEBUG
            Serial.println("Failed to open directory");
#endif

            return;
      }
      if (!root.isDirectory())
      {
#ifdef DEBUG
            Serial.println("Not a directory");
#endif

            return;
      }

      File file = root.openNextFile();
      while (file)
      {
            if (file.isDirectory())
            {
#ifdef DEBUG
                  Serial.print("  DIR : ");
                  Serial.println(file.name());
#endif

                  if (levels)
                  {
                        listDir(fs, file.name(), levels - 1);
                  }
            }
            else
            {
#ifdef DEBUG
                  Serial.print("  FILE: ");
                  Serial.print(file.name());
                  Serial.print("  SIZE: ");
                  Serial.println(file.size());
#endif
            }
            file = root.openNextFile();
      }
}
/**
     * delete file when updated
     * @param fs File bin with firmware
     * @param path path to find the file in the server 
     */
void OTAUpdate::deleteFile(fs::FS &fs, const char *path)
{
#ifdef DEBUG
      Serial.printf("Deleting file: %s\n", path);
#endif

      if (fs.remove(path))
      {
#ifdef DEBUG
            Serial.println("File deleted");
#endif
      }
      else
      {
#ifdef DEBUG
            Serial.println("Delete failed");
#endif
      }
}

/**
     *  start Update From File
     */
void OTAUpdate::updateFromFS()
{
      File updateBin = SPIFFS.open("/firmware.bin");
      Serial.print(updateBin);
      if (updateBin)
      {
            if (updateBin.isDirectory())
            {
#ifdef DEBUG
                  Serial.println("Directory error");
#endif

                  updateBin.close();
                  return;
            }

            size_t updateSize = updateBin.size();

            if (updateSize > 0)
            {
#ifdef DEBUG
                  Serial.println("Starting update");
#endif
                  performUpdate(updateBin, updateSize);
            }
            else
            {
#ifdef DEBUG
                  Serial.println("Error, archivo vacío");
#endif
            }

            updateBin.close();

            // remove from dir
            SPIFFS.remove("/firmware.bin");
      }
      else
      {
#ifdef DEBUG
            Serial.println("no such binary");
#endif
      }
}

/**
     * performUpdate on streaming
     * @param updateSource update Source where is the file
     * @param updateSize size of the bin file to update
     */
void OTAUpdate::performUpdate(Stream &updateSource, size_t updateSize)
{
      if (Update.begin(updateSize))
      {
            size_t written = Update.writeStream(updateSource);
            if (written == updateSize)
            {
#ifdef DEBUG
                  Serial.println("Writes : " + String(written) + " successfully");
#endif
            }
            else
            {
#ifdef DEBUG
                  Serial.println("Written only : " + String(written) + "/" + String(updateSize) + ". Retry?");
#endif
            }
            if (Update.end())
            {
#ifdef DEBUG
                  Serial.println("OTA finished!");
#endif
                  if (Update.isFinished())
                  {
#ifdef DEBUG
                        Serial.println("Restart ESP device!");
#endif
                        ESP.restart();
                  }
                  else
                  {
#ifdef DEBUG
                        Serial.println("OTA not fiished");
#endif
                  }
            }
            else
            {
#ifdef DEBUG
                  Serial.println("Error occured #: " + String(Update.getError()));
#endif
            }
      }
      else
      {
#ifdef DEBUG
            Serial.println("Cannot beggin update");
#endif
      }
}

/**
     * print percentage of the update
     * @param readLength readed length of file
     * @param contentLength size of the bin file to update
     */
void OTAUpdate::printPercent(uint32_t readLength, uint32_t contentLength)
{
#ifdef DEBUG
     // Serial.println("printPercent");
#endif
      // If we know the total length
      if (contentLength != -1)
      {
#ifdef DEBUG
            Serial.print("\r ");
            Serial.print((100.0 * readLength) / contentLength);
            Serial.print('%');
#endif
      }
      else
      {
            Serial.println(readLength);
      }
}

// 

/**
     * used to extract header value from headers for ota update
     * @param header header of the get
     * @param headerName Name of the get header
     */
String OTAUpdate::getHeaderValue(String header, String headerName)
{
      return header.substring(strlen(headerName.c_str()));
}

// //----------------------------------------------------------------------------
// //                           PUBLIC FUNCTIONS
// //----------------------------------------------------------------------------

/**
     * Init the update 
     */
void OTAUpdate::init()
{
      if (!SPIFFS.begin(true))
      {
#ifdef DEBUG
            Serial.println("SPIFFS Mount Failed");
#endif
            return;
      }
      SPIFFS.format();
      listDir(SPIFFS, "/", 0);

      // publisher->initPublisher();
#include <../lib/TLS/clientcert.h>

      esp_tls_set_global_ca_store( certYcansam, sizeof(certYcansam)); //  TODO: VER NAME
}

/**
     * Start the update from server
     */
void OTAUpdate::updateFromServer()
{
      /*if (publisher->join())
    {
#ifdef DEBUG
      Serial.print("Connecting to ");
      Serial.print(server);
      Serial.println(" OK");
#endif
    }*/
      if (client.connect(server, portServer))
      {
#ifdef DEBUG
            Serial.println("Fetching bin file at: " + String(updateUrl)); // tells where its going to get the .bin and the name its looking for
#endif
            // Get the contents of the bin file
            client.print(String("GET ") + updateUrl + " HTTP/1.1\r\n" +
                         "Host: " + String(server) + "\r\n" +
                         "Cache-Control: no-cache\r\n" +
                         "Connection: close\r\n\r\n");
            unsigned long timeout = millis();
            while (client.available() == 0)
            {
                  if (millis() - timeout > 5000)
                  {
#ifdef DEBUG
                        Serial.println("Client Timeout !");
#endif
                        client.stop();
                        return;
                  }
            }
#ifdef DEBUG
            Serial.println("Reading header");
#endif
            uint32_t contentLength = knownFileSize;
            File file = SPIFFS.open("/firmware.bin", FILE_APPEND);
            while (client.available())
            {
                  String line = client.readStringUntil('\n');
                  line.trim();
#ifdef DEBUG
                  Serial.println(line); // Uncomment this to show response header
#endif
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
            // CRC32 crc;
            unsigned long timeElapsed = millis();
            // printPercent(readLength, contentLength);

            while (readLength < contentLength && client.connected() && millis() - timeout < 10000L)
            {
                  while (client.available() && readLength < contentLength)
                  {
                        int c = client.read();
                        // client.write(file);
                        file.print((char)c);
                        // crc.update((char)c);
                        readLength++;
                        printPercent(readLength, contentLength);
                        timeout = millis();
                  }
#ifdef DEBUG
                  if (client.available() <= 0)
                        Serial.println("Client not Available");
                  if (millis() - timeout < 9500L)
                        Serial.println("TimeOut");
#endif
            }

            file.close();
#ifdef DEBUG
            Serial.println("  file.close();");
            Serial.println();
#endif
            printPercent(readLength, contentLength);
            timeElapsed = millis() - timeElapsed;

            client.stop();
#ifdef DEBUG
            Serial.println("stop client");
#endif
            modem.gprsDisconnect();
            float duration = float(timeElapsed) / 1000;
#ifdef DEBUG
            Serial.println("gprs disconnect");
            Serial.println();
            Serial.print("Tamaño de Archivo: ");
            Serial.println(contentLength);
            Serial.print("Leido:  ");
            Serial.println(readLength);
            //Serial.print("Calculado. CRC32:    0x");
            //Serial.println(crc.finalize(), HEX);
            //Serial.print("Conocido CRC32:    0x");
            //Serial.println(knownCRC32, HEX);
            Serial.print("Bajado en:       ");
            Serial.print(duration);
            Serial.println("s");
            Serial.println("Se genera una espera de 3 segundos");
#endif
            for (int i = 0; i < 3; i++)
            {
                  Serial.print(String(i + 1) + "...");
                  delay(1000);
            }
            readFile(SPIFFS, "/firmware.bin");
            updateFromFS();
            while (true)
            {
                  delay(1000);
            }
      }
}
