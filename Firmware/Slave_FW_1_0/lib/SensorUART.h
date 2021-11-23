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
     * Inicializa el esclavo por I2C
     * @param baudios velocidad del Serial
     */
    void initSensor(int baudios = 9600)
    {
        (*this).baudios = baudios;
        sensorSerial->begin(baudios);
        sensorSerial->print("Inicializando");
        if (sensorSerial->available())
        {
            char inByte = sensorSerial->read();
    
            Serial.write(inByte);
        }
    }

    /**
     * Obtiene la medida del sensor
     */
    void getMeasure(char* c)
    {
        sensorSerial->begin((*this).baudios);
        delay(500);
        sensorSerial->println(c);
        if (sensorSerial->available())
        {
            Serial.write(sensorSerial->read());
        }
        sensorSerial->end();
        Serial.println();
    }
    

    /**
     * Obtiene el tipo de sensor
     */
    byte getType()
    {
        sensorSerial->begin((*this).baudios);
        delay(500);
        sensorSerial->println("5");
        if (sensorSerial->available())
        {
            Serial.write(sensorSerial->read());
        }
        sensorSerial->end();
        Serial.println();
        return 0x25;
    }
};

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
