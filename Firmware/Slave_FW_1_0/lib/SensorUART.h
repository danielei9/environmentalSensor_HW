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
        delay(1000);
        sensorSerial->listen();
        sensorSerial->begin(baudios);
        sensorSerial->print("Inicializando");
        while (sensorSerial->available() > 0)
        {

            char inByte = sensorSerial->read();

            Serial.write(inByte);
        }
        Serial.print("iniciando" + (*this).RX);
    }

    void print(String word)
    {
        sensorSerial->listen();
        sensorSerial->print(word);
        if (sensorSerial->available())
        {
            Serial.write(sensorSerial->read());
        }
    }
};

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
