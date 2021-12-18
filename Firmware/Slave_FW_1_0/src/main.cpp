// -*- mode: c++ -*-
// --------------------------------------------------------------
// Autor: Yeray Candel Sampedro
// Date: 16 - 10 - 2021
//
// Description: El archivo main se encarga de gestionar mediante
// el arduino nano todos los sensores actualmente conectados
// a este mediante UART.
// --------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <SoftwareSerial.h>
unsigned long mill = 0;

bool timerTrue(unsigned long lastmillis_, int interval)
{
  if (millis() > (lastmillis_ + interval))
    return true;

  return false;
}

#include <../lib/SensorUART.h>

// function that executes whenever data is received from master
// this function is registered as an event, see setup()

const byte I2C_SLAVE_ADDR = 0x20;

// comandos
const byte REQUEST_COMMAND = 0x30;

uint8_t arrayLength = 8;
byte *arrayData1 = new byte[arrayLength];
byte *arrayData2 = new byte[arrayLength];
byte *arrayData3 = new byte[arrayLength];
void wakeUpSensors();
void sleepSensors();
void requestDataSensors();
void resetArrayData();
bool wakedUP = false;
void requestSensorsInformation();

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

SensorUART sensor1(11, 10);
SensorUART sensor2(9, 8);
SensorUART sensor3(5, 4);
SensorUART sensor4(7, 6);
SensorUART sensor5(3, 2);

SoftwareSerial serialtest(11, 10);
SoftwareSerial serialtest2(9, 8);
SoftwareSerial serialtest3(5, 4);
SoftwareSerial serialtest4(7, 6);
SoftwareSerial serialtest5(3, 2);

byte data = 0;

void resetSensors()
{

  sensor1.reset();
  sensor2.reset();
  sensor3.reset();
  sensor4.reset();
  sensor5.reset();

  data = 0;
}

// Request event para enviar los datos
void requestEvent()
{
  Wire.flush();
  resetSensors();
  wakedUP = false;

  Serial.println("Requested data from Master...");
  Serial.println("Sending Data: ");

  Serial.println();
  Serial.println();

  Wire.write(arrayData1, arrayLength);
  Wire.flush();
  delay(10);
  Wire.write(arrayData2, arrayLength);
  Wire.flush();
  delay(10);
  Wire.write(arrayData3, arrayLength);
  delay(10);
  Wire.flush();
}

void resetArrayData()
{
  // for (int i = 0; i < arrayLength; i++)
  // {
  //   arrayData1[i] = -1;
  //   arrayData2[i] = -1;
  //   arrayData3[i] = -1;
  // }
  sensor1.resetArrays();
  sensor2.resetArrays();
  sensor3.resetArrays();
  sensor4.resetArrays();
  sensor5.resetArrays();
}

// Funcion para recibir comandos desde el master
void receiveEvent(int bytes)
{
  resetArrayData();

  Wire.flush();
  data = 0;
  uint8_t index = 0;
  Serial.println("Received instruction from Master");
  // lee el comando
  while (Wire.available())
  {
    byte *pointer = (byte *)&data;
    *(pointer + index) = (byte)Wire.read();
    index++;
  }
}

void setup()
{
  Serial.begin(9600);
  Serial.println("Initialized Slave");

  serialtest.begin(9600);
  serialtest2.begin(9600);
  serialtest3.begin(9600);
  serialtest4.begin(9600);
  serialtest5.begin(9600);

  sensor1.initSensor(9600);
  sensor2.initSensor(9600);
  sensor3.initSensor(9600);
  sensor4.initSensor(9600);
  sensor5.initSensor(9600);
  wakeUpSensors();

  Wire.begin(I2C_SLAVE_ADDR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}
void loop()
{

  if (data != 0)
  {
    Serial.print("Command received: 0x");
    Serial.println(data, HEX);

    if (data == REQUEST_COMMAND)
    {
      wakeUpSensors();

      if (wakedUP)
      {
        delay(5200);
        requestSensorsInformation();
        delay(1000);
        requestDataSensors();
        // Serial.print("rabo");
      }

      // rellenando el array
      arrayData1[0] = sensor1.getGasConcentration();
      arrayData1[1] = sensor2.getGasConcentration();
      arrayData1[2] = sensor3.getGasConcentration();
      arrayData1[3] = sensor4.getGasConcentration();
      arrayData1[4] = sensor5.getGasConcentration();
      arrayData1[5] = 1;
      arrayData1[6] = 1;
      arrayData1[7] = 1;
      delay(10);
      arrayData2[0] = sensor1.getType();
      arrayData2[1] = sensor2.getType();
      arrayData2[2] = sensor3.getType();
      arrayData2[3] = sensor4.getType();
      arrayData2[4] = sensor5.getType();
      arrayData2[5] = 2;
      arrayData2[6] = 2;
      arrayData2[7] = 2;
      delay(10);

      arrayData3[0] = sensor1.getUnit();
      arrayData3[1] = sensor2.getUnit();
      arrayData3[2] = sensor3.getUnit();
      arrayData3[3] = sensor4.getUnit();
      arrayData3[4] = sensor5.getUnit();
      arrayData3[5] = 3;
      arrayData3[6] = 3;
      arrayData3[7] = 3;
      delay(10);

      for (int i = 0; i < arrayLength; i++)
      {
        Serial.print(arrayData1[i]);
        Serial.print(".");
        Serial.print(arrayData2[i]);
        Serial.print(".");
        Serial.print(arrayData3[i]);
        Serial.println();
      }
      // ejecutar el comando
    }
  }
}
void requestDataSensors()
{
  sensor1.getMeasure();
  sensor2.getMeasure();
  sensor3.getMeasure();
  sensor4.getMeasure();
  sensor5.getMeasure();
  data = 0;
  resetSensors();
}

void requestSensorsInformation()
{

  sensor1.getInformation();
  sensor2.getInformation();
  sensor3.getInformation();
  sensor4.getInformation();
  sensor5.getInformation();
  data = 0;
  resetSensors();
}

// despierta a todos los sensores
void wakeUpSensors()
{

  sensor1.wakeUp();
  sensor2.wakeUp();
  sensor3.wakeUp();
  sensor4.wakeUp();
  sensor5.wakeUp();
  resetSensors();
  wakedUP = true;
  
}

// funcion que duerme a todos los sensores
void sleepSensors()
{
  sensor1.sleep();
  sensor2.sleep();
  sensor3.sleep();
  sensor4.sleep();
  sensor5.sleep();
  resetSensors();
  wakedUP = false;
}