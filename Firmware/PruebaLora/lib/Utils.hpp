
#include <Arduino.h>

// (lastMillis:R , TX_interval:R) -> timerTrue -> bool
bool timerTrue(unsigned long lastmillis_, int interval);
// print array
// @param size tamaño del array
void printBytesArray(byte *arrayData, uint8_t size);