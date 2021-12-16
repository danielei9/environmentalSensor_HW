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
byte *arrayData = new byte[arrayLength];
void wakeUpSensors();
void sleepSensors();
void requestDataSensors();

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

// semaforos de los sensores
bool readedSensor1 = false;
bool readedSensor2 = false;
bool readedSensor3 = false;
bool readedSensor4 = false;
bool readedSensor5 = false;

void resetSensors()
{
  //reseteando semaforos
  readedSensor1 = false;
  readedSensor2 = false;
  readedSensor3 = false;
  readedSensor4 = false;
  readedSensor5 = false;

  sensor1.reset();
  sensor2.reset();
  sensor3.reset();
  sensor4.reset();
  sensor5.reset();
}

// Request event para enviar los datos
void requestEvent()
{
  resetSensors();

  Serial.println("Requested data from Master...");
  Serial.println("Sending Data: ");
  for (int i = 0; i < 8; i++)
  {
    Serial.print(arrayData[i]);
    if (i < 7)
      Serial.print(":");
  }
  Serial.println();
  Serial.println();
  Wire.write(arrayData, arrayLength);
}

// Funcion para recibir comandos desde el master
byte data = 0;
void receiveEvent(int bytes)
{
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
  Serial.println("delay");
  sleepSensors();

  Wire.begin(I2C_SLAVE_ADDR);
  Wire.onRequest(requestEvent);
  Wire.onReceive(receiveEvent);
}
bool wakedUP = false;

void loop()
{
  // wakeUpSensors();
  // if (wakedUP)
  // {
  //   delay(6000);
  //   requestDataSensors();
  //   Serial.println("Delay0");
  //   delay(5000);
  //   Serial.println("Delay1");
  // }

  // if (sensor1.getMeasure() == 1)
  // {
  //   sensor1.reset();
  // }

  // byte arrayCommand[9] = {0xFF, 0x00, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

  // // enviando el comando a la uart del sensor
  // for (int i = 0; i < 9; i++)
  // {
  //   serialtest.write(arrayCommand[i]);
  // }

  // serialtest.listen();
  // while (serialtest.available() > 0)
  // {
  //   int sensorData = serialtest.read();
  //   arrayData[counter] = sensorData;
  //   Serial.println(sensorData);

  //   Serial.println(sensorData);
  //   if (counter == 9)
  //   {
  //     readed = true;
  //     Serial.println("Sensor Readed");
  //     counter = 0;
  //   }
  //   /* code */
  // }
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
        requestDataSensors();
      }

      // rellenando el array
      arrayData[0] = sensor1.getGasConcentration();
      arrayData[1] = sensor2.getGasConcentration();
      arrayData[2] = sensor3.getGasConcentration();
      arrayData[3] = sensor4.getGasConcentration();
      arrayData[4] = sensor5.getGasConcentration();
      arrayData[5] = 25;
      arrayData[6] = 30;
      arrayData[7] = 90;
      // ejecutar el comando
    }
  }
}
int counter = 0;
void requestDataSensors()
{
  while (!readedSensor1)
  {
    counter++;
    if (sensor1.getMeasure() == 1)
    {
      readedSensor1 = true;
      Serial.print("Sensor1 Leido ");
      Serial.println(sensor1.getGasConcentration());
      break;
    }
    if (timerTrue(mill, 500))
    {
      readedSensor1 = true;
      Serial.println("Timeout sensor 1");
      mill = millis();
      break;
    }
  }

  while (readedSensor1 && !readedSensor2)
  {
    counter++;
    if (sensor2.getMeasure() == 1)
    {
      readedSensor2 = true;
      Serial.print("Sensor2 Leido :");
      Serial.println(sensor2.getGasConcentration());
      break;
    }
    if (timerTrue(mill, 1000))
    {
      readedSensor2 = true;
      Serial.println("Timeout sensor 2");
      mill = millis();
      break;
    }
  }

  while (readedSensor2 && !readedSensor3)
  {
    counter++;
    if (sensor3.getMeasure() == 1)
    {
      readedSensor3 = true;
      Serial.print("Sensor3 Leido :");
      Serial.println(sensor3.getGasConcentration());
      break;
    }
    if (timerTrue(mill, 1000))
    {
      readedSensor3 = true;
      Serial.println("Timeout sensor 3");
      mill = millis();
      break;
    }
  }

  while (readedSensor3 && !readedSensor4)
  {
    counter++;
    if (sensor4.getMeasure() == 1)
    {
      readedSensor4 = true;
      Serial.print("Sensor4 Leido :");
      Serial.println(sensor4.getGasConcentration());
      break;
    }
    if (timerTrue(mill, 1000))
    {
      readedSensor4 = true;
      Serial.println("Timeout sensor 4");
      mill = millis();
      break;
    }
  }
  while (readedSensor4 && !readedSensor5)
  {
    counter++;
    if (sensor5.getMeasure() == 1)
    {
      Serial.print("Sensor5 Leido :");
      Serial.println(sensor5.getGasConcentration());
      readedSensor5 = true;
      data = 0;
      resetSensors();
      sleepSensors();
      break;
    }
    if (timerTrue(mill, 1000))
    {
      Serial.println("Timeout sensor 5");
      mill = millis();
      readedSensor5 = true;
      data = 0;
      resetSensors();
      sleepSensors();
      break;
    }
  }
}
// despierta a todos los sensores
void wakeUpSensors()
{
  while (!wakedUP)
  {
    if (!readedSensor1)
    {
      if (sensor1.wakeUp() == 1)
      {
        readedSensor1 = true;
      }
      if (timerTrue(mill, 200))
      {
        readedSensor1 = true;
        Serial.println("Timeout wakingUp sensor 1");
        mill = millis();
      }
    }

    if (readedSensor1 && !readedSensor2)
    {
      if (sensor2.wakeUp() == 1)
      {
        readedSensor2 = true;
      }
      if (timerTrue(mill, 200))
      {
        readedSensor2 = true;
        Serial.println("Timeout wakingUp sensor 2");
        mill = millis();
      }
    }

    if (readedSensor2 && !readedSensor3)
    {
      if (sensor3.wakeUp() == 1)
      {
        readedSensor3 = true;
      }
      if (timerTrue(mill, 200))
      {
        readedSensor3 = true;
        Serial.println("Timeout wakingUp sensor 3");
        mill = millis();
      }
    }

    if (readedSensor3 && !readedSensor4)
    {
      if (sensor4.wakeUp() == 1)
      {
        readedSensor4 = true;
      }
      if (timerTrue(mill, 200))
      {
        readedSensor4 = true;
        Serial.println("Timeout wakingUp sensor 4");
        mill = millis();
      }
    }

    if (readedSensor4 && !readedSensor5)
    {
      if (sensor4.wakeUp() == 1)
      {
        readedSensor5 = true;
        resetSensors();
        wakedUP = true;
      }
      if (timerTrue(mill, 200))
      {
        readedSensor5 = true;
        Serial.println("Timeout wakingUp sensor 5");
        mill = millis();
        resetSensors();
        wakedUP = true;
      }
    }
  }
}

// funcion que duerme a todos los sensores
void sleepSensors()
{
  while (true)
  {

    //durmiendo sensor 1
    if (!readedSensor1)
    {
      // cuand
      if (sensor1.sleep() == 1)
      {
        readedSensor1 = true;
      }
      if (timerTrue(mill, 50))
      {
        readedSensor1 = true;
        Serial.println("Timeout sleep sensor 1");
        mill = millis();
      }
    }

    // durmiendo sensor 2 si se ha dormido el sensor 1
    if (readedSensor1 && !readedSensor2)
    {
      if (sensor2.sleep() == 1)
      {
        readedSensor2 = true;
      }
      if (timerTrue(mill, 50))
      {
        readedSensor2 = true;
        Serial.println("Timeout sleep sensor 2");
        mill = millis();
      }
    }
    if (readedSensor2 && !readedSensor3)
    {
      if (sensor3.sleep() == 1)
      {
        readedSensor3 = true;
      }
      if (timerTrue(mill, 50))
      {
        readedSensor3 = true;
        Serial.println("Timeout sleep sensor 3");
        mill = millis();
      }
    }
    if (readedSensor3 && !readedSensor4)
    {
      if (sensor4.sleep() == 1)
      {
        readedSensor4 = true;
      }
      if (timerTrue(mill, 50))
      {
        readedSensor4 = true;
        Serial.println("Timeout sleep sensor 4");
        mill = millis();
      }
    }
    if (readedSensor4 && !readedSensor5)
    {
      if (sensor5.sleep() == 1)
      {
        readedSensor5 = true;
        wakedUP = false;
        resetSensors();
        break;
      }
      if (timerTrue(mill, 50))
      {
        readedSensor5 = true;
        Serial.println("Timeout sleep sensor 5");
        mill = millis();
        wakedUP = false;
        resetSensors();
        break;
      }
    }
  }
}