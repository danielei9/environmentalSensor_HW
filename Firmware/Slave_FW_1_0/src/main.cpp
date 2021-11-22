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
// SensorUART sensor1(10, 11);
SoftwareSerial serial25(10, 11);
SoftwareSerial serial2(2, 3);

void setup()
{
  Serial.begin(9600);
  serial25.begin(9600);

  //serial25.print("25");

  // Wire.begin(I2C_SLAVE_ADDR);
  // Wire.onRequest(requestEvent);
  // sensor1.initSensor(115200);
}

void loop()
{
  serial25.begin(9600);
  delay(500);
  serial25.print("1");
  if (serial25.available())
  {
    Serial.write(serial25.read());
  }
  serial25.end();

  serial2.begin(9600);
  delay(500);
  serial2.println("2");
  if (serial2.available())
  {
    Serial.write(serial2.read());
  }
  serial2.end();
}
