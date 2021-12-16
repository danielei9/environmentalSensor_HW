// -*- mode: c++ -*-

// --------------------------------------------------------------
// Autor: Daniel Burruchaga Sola
// Date: 03 - 12 - 2021
// Name: Modbus.hpp
// Description: Modbus class 
// --------------------------------------------------------------
#include "Arduino.h"
#define MODBUS_TIMEOUT 500
#define MODBUS_FRAME_TIMEOUT 4
#define RESPONSE_BUFFER_SIZE 256
#ifndef TTGO_SOFTWARE_SERIAL 
#define TTGO_SOFTWARE_SERIAL 4
#endif
//----------------------------------------------------------------
// Define the sensor's modbus address
//----------------------------------------------------------------

//----------------------------------------------------------------
// Define pin number variables
//----------------------------------------------------------------

const int sensorPwrPin = 34;  // The pin sending power to the sensor
const int adapterPwrPin = 35; // The pin sending power to the RS485 adapter
const int DEREPin = 0;       // The pin controlling Recieve Enable and Driver Enable
                              // on the RS485 adapter, if applicable (else, -1)
                              // Setting HIGH enables the driver (arduino) to send text
                              // Setting LOW enables the receiver (sensor) to send text
//----------------------------------------------------------------
class Modbus
{

public:
float getNoise();
    int sendCommand(byte command[], int commandLength);
    void driverEnable(void);
    float getTemperature();
    void changeAddrNoise();
    float getSoilMoisture();
    float getEpsilon();
    void recieverEnable(void);
    void emptySerialBuffer(Stream *stream);
    void printFrameHex(byte modbusFrame[], int frameLength);
    void calculateCRC(byte modbusFrame[], int frameLength);
    void insertCRC(byte modbusFrame[], int frameLength);
    void sliceArray(byte inputArray[], byte outputArray[],
                    int start_index, int numBytes, bool reverseOrder);
    bool begin(byte modbusSlaveID, Stream *stream, int enablePin);
    bool begin(byte modbusSlaveID, Stream &stream, int enablePin);
    static byte responseBuffer[RESPONSE_BUFFER_SIZE];

    byte _slaveID;   // The sensor slave id
    Stream *_stream; // The stream instance (serial port) for communication with the RS485
    int _enablePin;  // The pin controlling the driver/receiver enable on the RS485-to-TLL chip

    Stream *_debugStream1; // The stream instance (serial port) for debugging

    static byte crcFrame[2];
    static byte command[8];
    static byte commandNoise[8];
    static byte changAddrNoise[8];

    const uint32_t modbusTimeout = MODBUS_TIMEOUT;       // The time to wait for response after a command (in ms)
    const int modbusFrameTimeout = MODBUS_FRAME_TIMEOUT; // the time to wait between characters within a frame (in ms)
};