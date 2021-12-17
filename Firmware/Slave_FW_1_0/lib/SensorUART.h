// -*- mode: c++ -*-

// --------------------------------------------------------------
// Autor: Yeray Candel Sampedro
// Date: 16 - 11 - 2021
//
// Description: Clase SensorUART que se encarga de instanciar
// y controlar cada uno de los sensores del esclavo
// --------------------------------------------------------------
#include <Arduino.h>
#ifndef SENSOR_UART_H_INCLUDED
#define SENSOR_UART_H_INCLUDED
#include <SoftwareSerial.h>

// const uint8_t sensorsType[14] = {0x17, 0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F, 0x20, 0x21, 0x22, 0x23, 0x24};

class SensorUART
{
private:
    // pines RX TX de cada sensor
    int8_t RX = 0;
    int8_t TX = 0;
    uint16_t baudios = 9600;
    SoftwareSerial *sensorSerial;

    uint8_t arrayData[9];         // array para guardar las medidas
    uint8_t sensorInformation[9]; // array para guardar la informacion del sensor

    // identificadores del sensor
    uint8_t sensorType = -1;

    uint8_t sensorUnit = -1;

    // contadores y boleanos de lectura
    int counter = 0;
    bool readed = false;
    bool sendCommand = false;

public:
    /**
     * Constructor de la clase SensorUART
     */
    SensorUART(int8_t rx, int8_t tx)
    {
        (*this).RX = rx;
        (*this).TX = tx;
        sensorSerial = new SoftwareSerial(rx, tx);
    }
    /**
     * Inicializa el Sensor
     */
    void initSensor(uint16_t baudios = 9600)
    {
        sensorSerial->begin(baudios);
    }

    /**
     * Obtiene un array de datos con la informacion del modulo
     * Informacion de 8 bytes.
     * 
     *     0    1    2    3    4    5    6    7    8
     * EJ: 0x17 0x00 0XC8 0x02 0x00 0x00 0x00 0x01 0x1E
     */
    bool getSensorInformation()
    {

        if (sensorUnit != sensorInformation[5] || sensorType != sensorInformation[2])
        {
            if (!(*this).sendCommand)
            {

                byte arrayCommand[1] = {0xD7};

                // enviando el comando a la uart del sensor
                for (int i = 0; i < 1; i++)
                {
                    sensorSerial->write(arrayCommand[i]);
                }
                (*this).sendCommand = true;
            }
            if (!(*this).readed)
            {
                sensorSerial->listen();
                while (sensorSerial->available() > 0)
                {
                    uint8_t sensorData = sensorSerial->read();
                    sensorInformation[counter] = (sensorData);
                    Serial.println(sensorData);
                    (*this).counter++;
                    if ((*this).counter == 9)
                    {
                        (*this).readed = true;
                        Serial.println("Sensor Readed");
                        sensorType = (sensorInformation[2]);
                        Serial.println(sensorType);
                        sensorUnit = (sensorInformation[5]);
                        Serial.println(sensorUnit);
                        return (*this).readed;
                    }
                }
            }
            return (*this).readed;
        }
        else
        {
            return true;
        }
    }

    /**
     * Obtiene la medida del sensor
     * @returns devuelve un array
     */
    int getMeasure()
    {
        // intenta obtener la informacion del sensor si ha cambiado. Si no ha cambiado no lee la informacion
        getSensorInformation();
        if (!(*this).sendCommand)
        {

            byte arrayCommand[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

            // enviando el comando a la uart del sensor
            for (int i = 0; i < 9; i++)
            {
                sensorSerial->write(arrayCommand[i]);
            }
            (*this).sendCommand = true;
        }
        if (!(*this).readed)
        {
            sensorSerial->listen();
            while (sensorSerial->available() > 0)
            {
                int sensorData = sensorSerial->read();
                arrayData[counter] = sensorData;
                Serial.println(sensorData);
                (*this).counter++;
                if ((*this).counter == 9)
                {
                    (*this).readed = true;
                    Serial.println("Sensor Readed");
                    reset();
                    return (*this).readed;
                }
                /* code */
            }
        }
        return (*this).readed;
    }

    /**
     * Obtiene la concentracion del gas
     * @returns valor de la concentracion del gas
     */
    int getGasConcentration()
    {
        return arrayData[2] * 255 + arrayData[3];
    }

    /**
     * Obtiene la medida del sensor
     * @returns devuelve un array
     */
    bool sleep()
    {
        if (!(*this).sendCommand)
        {
            //
            byte arrayCommand[6] = {0xAF, 0x53, 0x6C, 0x65, 0x65, 0x70};

            // enviando el comando a la uart del sensor
            for (int i = 0; i < 6; i++)
            {
                sensorSerial->write(arrayCommand[i]);
            }
            (*this).sendCommand = true;
        }
        if (!(*this).readed)
        {
            sensorSerial->listen();
            while (sensorSerial->available() > 0)
            {

                int data = sensorSerial->read();
                arrayData[counter] = data;
                Serial.println(data);
                (*this).counter++;
                if ((*this).counter == 2)
                {
                    (*this).readed = true;
                    Serial.println("Sensor is sleeping...");
                    return (*this).readed;
                }
                /* code */
            }
        }
        return (*this).readed;
    }

    /**
     * Obtiene la medida del sensor
     * @returns devuelve un array
     */
    bool wakeUp()
    {
        if (!(*this).sendCommand)
        {
            //
            byte arrayCommand[5] = {0xAE, 0x45, 0x78, 0x69, 0x74};

            // enviando el comando a la uart del sensor
            for (int i = 0; i < 5; i++)
            {
                sensorSerial->write(arrayCommand[i]);
            }
            (*this).sendCommand = true;
        }
        if (!(*this).readed)
        {
            sensorSerial->listen();
            while (sensorSerial->available() > 0)
            {

                int data = sensorSerial->read();
                arrayData[counter] = data;
                Serial.println(data);
                (*this).counter++;
                if ((*this).counter == 2)
                {
                    (*this).readed = true;
                    Serial.println("Sensor exited from deep Sleep");
                    return (*this).readed;
                }
                /* code */
            }
        }
        return (*this).readed;
    }
    /**
     * Resetea los valores de lectura del sensor
     */
    void reset()
    {
        (*this).counter = 0;
        (*this).readed = false;
        (*this).sendCommand = false;
    }
    /**
     * Devuelve el tipo de sensor
     * @returns  HEXADECIMAl tipo
     */
    int getSensorType()
    {
        if (sensorType != -1 && sensorInformation[2] == sensorType)
            return (sensorInformation[2]);
        else
        {
            getSensorInformation();
        }
    }

    /**
     * Devuelve la unidad en la que se mide el sensor.
     * @returns HEXADECIMAL tipo
     */
    int getUnit()
    {
        if (sensorType != -1 && sensorInformation[5] == sensorUnit)
            return (sensorInformation[5]);
        else
        {
            getSensorInformation();
        }
    }
};

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
