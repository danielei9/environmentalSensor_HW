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

class SensorUART
{
private:
    // pines RX TX de cada sensor
    int8_t RX = 0;
    int8_t TX = 0;
    uint16_t baudios = 9600;
    SoftwareSerial *sensorSerial;

    /**
     * Obtiene la concentracion del gas
     * @param highConcentration concentracion alta del gas
     * @param lowConcentration concentracion baja del gas
     * @returns valor de la concentracion del gas
     */
    int getGasConcentration(byte highConcentration, byte lowConcentration)
    {
        return highConcentration * 256 + lowConcentration;
    }
    
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

    byte testUart(char *c)
    {
        sensorSerial->begin((*this).baudios);
        delay(500);
        sensorSerial->println(c);
        byte b;
        if (sensorSerial->available())
        {
            b = sensorSerial->read();
            Serial.write(b);
        }
        sensorSerial->end();
        Serial.println();
        return b;
    }

    /**
     * Obtiene la medida del sensor
     * @returns devuelve un array
     */
    int getMeasure()
    {
        Serial.println("Enviando comando : 0xFF 0x01 0x86 0x00 0x00 0x00 0x00 0x00 0x79");
        byte arrayCommand[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};

        // enviando el comando a la uart del sensor
        for (int i = 0; i < 9; i++)
        {
            sensorSerial->write(arrayCommand[i]);
        }

        Serial.println("Leyendo Sensor..");
        uint8_t index = 0;
        byte arrayData[8];
        // leyendo la respuesta del sensor
        while (sensorSerial->available() > 0)
        {
            // recibiendo la respuesta del tipo
            Serial.print("Byte: " + index);
            arrayData[index] = sensorSerial->read();
            Serial.println(" : " + arrayData[index]);

            Serial.write(sensorSerial->read());
            index++;
        }

        // devolviendo la lectura de hexadecimal a decimal
        return getGasConcentration(arrayData[6], arrayData[7]);
    }

    /**
     * Obtiene un array de datos con la informacion del modulo
     * Informacion de 8 bytes.
     * 
     *     0    1    2    3    4    5    6    7    8
     * EJ: 0x17 0x00 0XC8 0x02 0x00 0x00 0x00 0x01 0x1E
     */
    byte *getType()
    {
        sensorSerial->begin((*this).baudios);
        delay(500);

        // envia el comando de pedir el tipoS
        Serial.println("Enviando el comando 0xD1");
        sensorSerial->write(0xD1);
        Serial.println("Obteniendo datos...");
        Serial.println();

        // index para el array
        uint8_t index = 0;
        byte arrayData[8];
        while (sensorSerial->available() > 0)
        {
            Serial.print("Byte: " + index);
            // recibiendo la respuesta del tipo
            arrayData[index] = sensorSerial->read();
            Serial.println(" : " + arrayData[index]);
            Serial.write(sensorSerial->read());
            index++;
        }
        sensorSerial->end();
        Serial.println();
        Serial.println("Tipo recibido.");

        return arrayData;
    }
};

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
