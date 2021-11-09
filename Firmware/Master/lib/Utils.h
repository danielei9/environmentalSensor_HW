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

#endif