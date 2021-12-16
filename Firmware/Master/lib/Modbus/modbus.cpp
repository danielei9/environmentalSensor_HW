// -*- mode: c++ -*-

// --------------------------------------------------------------
// Autor: Daniel Burruchaga Sola
// Date: 03 - 12 - 2021
// Name: Modbus.hpp
// Description: Modbus class 
// --------------------------------------------------------------
#include "Arduino.h"
#include "Modbus.hpp"
#define RESPONSE_BUFFER_SIZE 256
#define MODBUS_TIMEOUT 500
#define MODBUS_FRAME_TIMEOUT 4
//#define DEBUG
// initialize the response buffer
byte Modbus::responseBuffer[RESPONSE_BUFFER_SIZE] = {
    0x00,
};
// initialize the crc 
byte Modbus::crcFrame[2] = {
    0x00,
};
//command to send to floor sensore
byte Modbus::command[8] = {0x01, 0x04, 0x00, 0x00, 0x00, 0x03, 0xB0, 0x0B};
// command to sen to get noise levels
byte Modbus::commandNoise[8] = {0x02, 0x03, 0x00, 0x00, 0x00, 0x01, 0x84, 0x0A};
//command to send to chang the addr of the noise sensore
byte Modbus::changAddrNoise[8] = {0xFF, 0x06, 0x07, 0xD0, 0x00, 0x02, 0x1D, 0x58};

/**
     * This sends a command to the sensor bus and listens for a response
     * @param command commmand to send, 
     * @param commandLength commmand to send 
     */
int Modbus::sendCommand(byte command[], int commandLength)
{
    // Empty the response buffer
    for (int i = 0; i < RESPONSE_BUFFER_SIZE; i++)
        responseBuffer[i] = 0x00;

    // Add the CRC to the frame
    insertCRC(command, commandLength);

    // Send out the command
    driverEnable();
    emptySerialBuffer(_stream); // Clear any junk before sending command
    _stream->write(command, commandLength);
    _stream->flush();
    recieverEnable();
    // Print the raw send (for debugging)
#ifdef DEBUG
    Serial.print("Raw Request >>> ");
    printFrameHex(command, commandLength);

#endif

    // Wait for a response
    uint32_t start = millis();
    while (Serial.available() == 0 && millis() - start < modbusTimeout)
    {
        delay(1);
    }

    if (_stream->available() > 0)
    {
        // Read the incoming bytes
        int bytesRead = _stream->readBytes(responseBuffer, 135);
        emptySerialBuffer(_stream);
#ifdef DEBUG
        // Print the raw response (for debugging)
        Serial.print("Raw Response (");
        Serial.print(bytesRead);
        Serial.print(" bytes) <<< ");
        printFrameHex(responseBuffer, bytesRead);
#endif

        // Verify that the values match with the commands
        if (responseBuffer[0] != _slaveID)
        {
#ifdef DEBUG
            Serial.println("Response is not from the correct modbus slave!");
#endif
            return 0;
        }

        // Verify that the CRC is correct
        calculateCRC(responseBuffer, bytesRead);
        if (crcFrame[0] != responseBuffer[bytesRead - 2] || crcFrame[1] != responseBuffer[bytesRead - 1])
        {
#ifdef DEBUG
            Serial.println("CRC of response is not correct!");
#endif
            return 0;
        }

        // Check for exception response
        // An execption response sets the highest bit of the function code in the response.
        if ((responseBuffer[1] & 0b10000000) == 0b10000000)
        {
#ifdef DEBUG
            Serial.print("Exception:  ");
            if (responseBuffer[2] == 0x01)
                Serial.println("Illegal Function!");
            if (responseBuffer[2] == 0x02)
                Serial.println("Illegal Data Address!");
            if (responseBuffer[2] == 0x03)
                Serial.println("Illegal Data Value!");
            if (responseBuffer[2] == 0x04)
                Serial.println("Slave Device Failure!");
            if (responseBuffer[2] == 0x05)
                Serial.println("Acknowledge...");
            if (responseBuffer[2] == 0x06)
                Serial.println("Slave Device Busy!");
            if (responseBuffer[2] == 0x07)
                Serial.println("Negative Acknowledge!");
            if (responseBuffer[2] == 0x08)
                Serial.println("Memory Parity Error!");
            if (responseBuffer[2] == 0x0A)
                Serial.println("Gateway Path Unavailable!");
            if (responseBuffer[2] == 0x0B)
                Serial.println("Gateway Target Device Failed to Respond!");
#endif
            return 0;
        }
        // If everything passes, return the number of bytes
        return bytesRead;
    }
    else
    {
#ifdef DEBUG
        Serial.println("No response received.");
#endif
        return 0;
    }
}

/**
     * Get temperature from floor sensor
     */
float Modbus::getTemperature()
{
    sendCommand(command, sizeof(command));
    return ((responseBuffer[3] * 256 + responseBuffer[4]) / 100);
}

/**
     * Change Address from the noise sensor
     */
void Modbus::changeAddrNoise()
{
    sendCommand(changAddrNoise, sizeof(command));
   // return ((responseBuffer[3] * 256 + responseBuffer[4]) / 100);
}

/**
     * Get noise from noise sensor
     */
float Modbus::getNoise()
{
    sendCommand(commandNoise, sizeof(commandNoise));
    return (((responseBuffer[3]* 256  + responseBuffer[4])/ 10));
}

/**
     * Get soilMoisture from floor sensor
     */
float Modbus::getSoilMoisture()
{
    sendCommand(command, sizeof(command));
    return ((responseBuffer[5] * 256 + responseBuffer[6]) / 100);
}

/**
     * Get epsilon from floor sensor
     */
float Modbus::getEpsilon()
{
    sendCommand(command, sizeof(command));
    return responseBuffer[7] * 256 + responseBuffer[8];
}


/**
     * Initialize the modbus config and begin 
     * @param modbusSlaveID Id of the comm 
     * @param stream Stream to use UART SOFTWARE SERIAL in this case 
     * @param enablePin Pin wich select if is RX or rx
     */
bool Modbus::begin(byte modbusSlaveID, Stream &stream, int enablePin)
{
    return begin(modbusSlaveID, &stream, enablePin);
}

/**
     * Initialize the modbus config and begin 
     * @param modbusSlaveID Id of the comm 
     * @param stream Stream to use UART SOFTWARE SERIAL in this case 
     * @param enablePin Pin wich select if is RX or rx
     */
bool Modbus::begin(byte modbusSlaveID, Stream *stream, int enablePin)
{
    // Give values to variables;
    _slaveID = modbusSlaveID;
    _stream = stream;
    _enablePin = enablePin;

    // Set pin mode for the enable pin
    if (_enablePin >= 0)
        pinMode(_enablePin, OUTPUT);
    recieverEnable();

    _stream->setTimeout(modbusFrameTimeout);

    return true;
}

//----------------------------------------------------------------------------
//                           PRIVATE HELPER FUNCTIONS
//----------------------------------------------------------------------------

/**
     * Put This flips the device/receive enable to DRIVER so the arduino can send text
     */
void Modbus::driverEnable(void)
{
    if (_enablePin >= 0)
    {
        digitalWrite(_enablePin, HIGH);
#ifdef DEBUG
        Serial.println("RS485 Driver/Master Tx Enabled");
#endif
        delay(8);
    }
}

/**
     * This flips the device/receive enable to RECIEVER so the sensor can send text
     */
void Modbus::recieverEnable(void)
{
    if (_enablePin >= 0)
    {
        digitalWrite(_enablePin, LOW);
#ifdef DEBUG
        Serial.println("RS485 Receiver/Slave Tx Enabled");
#endif
        // delay(8);
    }
}
/**
     *  This empties the serial buffer
     * @param stream Stream to use UART SOFTWARE SERIAL in this case 
     */

void Modbus::emptySerialBuffer(Stream *stream)
{
    while (stream->available() > 0)
    {
        stream->read();
        delay(1);
    }
}

/**
     *  pretty-print the modbus hex frames for DEBUG
     * @param modbusFrame  Frame to show 
     * @param frameLength Frame length
     */
void Modbus::printFrameHex(byte modbusFrame[], int frameLength)
{
    Serial.print("{");
    for (int i = 0; i < frameLength; i++)
    {
        Serial.print("0x");
        if (modbusFrame[i] < 16)
            Serial.print("0");
        Serial.print(modbusFrame[i], HEX);
        if (i < frameLength - 1)
            Serial.print(", ");
    }
    Serial.println("}");
}

/**
     * Calculates a Modbus RTC cyclical redudancy code (CRC) and adds it to the last two bytes of a frame
     * @param modbusFrame  Frame to show 
     * @param frameLength Frame length
     */
void Modbus::calculateCRC(byte modbusFrame[], int frameLength)
{
    // Reset the CRC frame
    crcFrame[0] = {0x00};
    crcFrame[1] = {0x00};

    uint16_t crc = 0xFFFF;
    for (int pos = 0; pos < frameLength - 2; pos++)
    {
        crc ^= (unsigned int)modbusFrame[pos]; // XOR byte into least sig. byte of crc

        for (int i = 8; i != 0; i--)
        { // Loop over each bit
            if ((crc & 0x0001) != 0)
            {              // If the least significant bit (LSB) is set
                crc >>= 1; // Shift right and XOR 0xA001
                crc ^= 0xA001;
            }
            else           // Else least significant bit (LSB) is not set
                crc >>= 1; // Just shift right
        }
    }

    // Break into low and high bytes
    byte crcLow = crc & 0xFF;
    byte crcHigh = crc >> 8;

    // Append the bytes to the end of the frame
    crcFrame[0] = crcLow;
    crcFrame[1] = crcHigh;
}

/**
     * Insert the crc 
     * @param modbusFrame  Frame to show 
     * @param frameLength Frame length
     */
void Modbus::insertCRC(byte modbusFrame[], int frameLength)
{
    // Calculate the CRC
    calculateCRC(modbusFrame, frameLength);

    // Append the bytes to the end of the frame
    modbusFrame[frameLength - 2] = crcFrame[0];
    modbusFrame[frameLength - 1] = crcFrame[1];
}

/**
     * This slices one array out of another helper debug
     * @param inputArray  Input to slice
     * @param outputArray  Output from slice
     */

void Modbus::sliceArray(byte inputArray[], byte outputArray[],
                        int start_index, int numBytes, bool reverseOrder)
{

    if (reverseOrder)
    {
        // Reverse the order of bytes to get from big-endian to little-endian
        int j = numBytes - 1;
        for (int i = 0; i < numBytes; i++)
        {
            outputArray[i] = inputArray[start_index + j];
            j--;
        }
    }
    else
    {
        for (int i = 0; i < numBytes; i++)
            outputArray[i] = inputArray[start_index + i];
    }
}
