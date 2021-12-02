// /* ----------------------------------------------------------------
//  *   AUTHOR:        Daniel Burruchaga Sola
//  *   FILE:           OTA_Update.cpp
//  *   DATE:           22/11/2021
//  *   STATE:          DONE
//  *  ---------------------------------------------------------------- */
#pragma once

#include <Arduino.h>
#include "SPIFFS.h"
#include "ESP32httpUpdate.h"
#include <esp_tls.h>
#include "FS.h"

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
// //----------------------------------------------------------------------------
// //                           PRIVATE FUNCTIONS
// //----------------------------------------------------------------------------