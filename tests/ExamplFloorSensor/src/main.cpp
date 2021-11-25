#include <Arduino.h>
#define TTGO_SOFTWARE_SERIAL 1 // If use ttgo
#define SENSOR_SUELO 1 // If we have sensor floor
#include <modbus.hpp>

#ifdef SENSOR_SUELO
//#define sensorPowerController 1
//#define adapterModbusPowerController 1
//#define DEBUG 1
#if defined(TTGO_SOFTWARE_SERIAL)
#include <SoftwareSerial.h>
#ifdef TTGO_SOFTWARE_SERIAL
const int SSRxPin = 32; // 2 Recieve pin for software serial (Rx on RS485 adapter)
const int SSTxPin = 33; // 3 Send pin for software serial (Tx on RS485 adapter)
#endif
SoftwareSerial modbusSerial(SSRxPin, SSTxPin);
#else
HardwareSerial modbusSerial = Serial1;
#endif
#endif

// Construct the modbus instance
Modbus modbus;

// ---------------------------------------------------------------------------
// Main setup function
// ---------------------------------------------------------------------------
void setup()
{
#ifdef SENSOR_SUELO
// Controller Modbus interface
#ifdef TTGO_SOFTWARE_SERIAL
  if (DEREPin >= 0)
  {
    pinMode(DEREPin, OUTPUT);
  }
#endif
  // Controller PowerPin Sensor
#ifdef sensorPowerController
  if (sensorPwrPin >= 0)
  {
    pinMode(sensorPwrPin, OUTPUT);
    digitalWrite(sensorPwrPin, HIGH);
  }
#endif
  // Controller power modbus interface
#ifdef adapterModbusPowerController
  if (adapterPwrPin >= 0)
  {
    pinMode(adapterPwrPin, OUTPUT);
    digitalWrite(adapterPwrPin, HIGH);
  }
#endif

  // Turn on modbus serial port
#if defined(TTGO_SOFTWARE_SERIAL)
  modbusSerial.begin(9600);
#else
  Serial1.begin(modbusBaudRate, SERIAL_8O1);
#endif
  modbus.begin(0x01, modbusSerial, DEREPin);
#endif

  Serial.begin(9600);
}

// ---------------------------------------------------------------------------
// Main setup function
// ---------------------------------------------------------------------------
void loop()
{

  delay(2000);
  Serial.println("Temperatura: ");
  Serial.println(modbus.getTemperature());
  
  Serial.println("Epsilon: ");
  Serial.println(modbus.getEpsilon());
  
  Serial.println("Soil: ");
  Serial.println(modbus.getSoilMoisture());
}