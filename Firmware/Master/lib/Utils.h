#include <Arduino.h>

#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

// (lastMillis:R , TX_interval:R) -> timerTrue -> bool
bool timerTrue(unsigned long lastmillis_, int interval)
{
  if (millis() > (lastmillis_ + interval))
    return true;

  return false;
}
bool timerTrue(unsigned long lastmillis_, int interval, bool estandesp)
{
  if (millis() > (lastmillis_ + interval))
    return true;

  return false;
}

// print array
// @param size tamaño del array
void printBytesArray(byte *arrayData, uint8_t size)
{
  for (int i = 0; i < size; i++)
  {
    Serial.print(arrayData[i]);
    Serial.print(":");
  }
  Serial.println();
}
#endif