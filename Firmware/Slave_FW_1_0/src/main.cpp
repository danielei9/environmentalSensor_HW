#include <Arduino.h>
#include <Wire.h>

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

const byte I2C_SLAVE_ADDR = 0x20;
long data = 0;
long response = 10;
uint8_t arrayLength = 8;
byte *arrayData = new byte[arrayLength];

// para TVOC necesito 9 bits 2 BYTEs
// para H2 necesito 10 bits 2 Bytes


void requestEvent()
{
  arrayData[0] = 10;
  arrayData[1] = 255;
  arrayData[2] = B00000001;
  arrayData[3] = 255;
  arrayData[4] = 255;
  arrayData[5] = 255;
  arrayData[6] = 255;
  arrayData[7] = 255;

  Wire.write(arrayData, arrayLength);
}

void setup()
{
  Serial.begin(115200);
  Wire.begin(I2C_SLAVE_ADDR);
  Wire.onRequest(requestEvent);
}

void loop()
{
  if (data != 0)
  {
    Serial.println(data);
    data = 0;
  }
  delay(100);
}
