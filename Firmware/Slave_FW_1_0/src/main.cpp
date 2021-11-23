#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
#include <../lib/SensorUART.h>

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

const byte I2C_SLAVE_ADDR = 0x20;
uint8_t arrayLength = 8;
byte *arrayData = new byte[arrayLength];

// para TVOC necesito 9 bits 2 BYTEs
// para H2 necesito 10 bits 2 Bytes
// para CO necesito 10 bits 2 bytes
// para H2S necesito 7 bits 1 bytes
// para CL2 necesito 6 buts 1 byte
// para O3 necesito 7 bits 1 byte
// para NO2 necesito 10 bits 2 bytes
// para SO2 necesito 10 bits 2 bytes
// para CH4S necesito 7 bits 1 byte
// para NH3 necesito 10 bits 2 bytes
// para Temp necesito 5 bits 1 byte
// para Hum necesito 7 bits 1 byte
// total 103 bits = 13 bytes // 18 sin juntar todos los bits

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
SensorUART sensor1(10, 11);
SensorUART sensor2(2, 3);
SensorUART sensor3(4, 5);
SensorUART sensor4(6, 7);
SensorUART sensor5(8, 9);

void setup()
{
  Serial.begin(9600);

  // Wire.begin(I2C_SLAVE_ADDR);
  // Wire.onRequest(requestEvent);
  // sensor1.initSensor(115200);
}

void loop()
{
  sensor1.getMeasure("1");
  sensor2.getMeasure("2");
  sensor3.getMeasure("3");
  sensor4.getMeasure("4");
  sensor5.getMeasure("5");
}
