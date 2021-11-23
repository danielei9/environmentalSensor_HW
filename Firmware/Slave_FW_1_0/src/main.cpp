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

SensorUART sensor1(10, 11);
SensorUART sensor2(2, 3);
SensorUART sensor3(4, 5);
SensorUART sensor4(6, 7);
SensorUART sensor5(8, 9);

void requestEvent()
{
  // rellenando el array
  arrayData[0] = sensor1.getMeasure();
  arrayData[1] = sensor2.getMeasure();
  arrayData[2] = sensor3.getMeasure();
  arrayData[3] = sensor4.getMeasure();
  arrayData[4] = sensor5.getMeasure();
  // arrayData[5] = 255;
  // arrayData[6] = 255;
  // arrayData[7] = 255;

  Wire.write(arrayData, arrayLength);
}

void setup()
{
  Serial.begin(9600);

  Wire.begin(I2C_SLAVE_ADDR);
  Wire.onRequest(requestEvent);
}

void loop()
{
  sensor1.testUart("1");
  sensor2.testUart("2");
  sensor3.testUart("3");
  sensor4.testUart("4");
  sensor5.testUart("5");
  delay(100);
}
