// -*- mode: c++ -*-

// --------------------------------------------------------------
// Autor: Yeray Candel Sampedro
// Date: 09 - 11 - 2021
//
// Description: Clase Slave controller que se encarga de controlar
// todos los esclavos por I2C.
// --------------------------------------------------------------

#include <Arduino.h>
#include <Wire.h>
#include <../Utils.h>
#ifndef SLAVE_CONTROLLER_H_INCLUDED
#define SLAVE_CONTROLLER_H_INCLUDED

unsigned long millSensorsRequest = 0;

class SlaveController
{
private:
    // pines SDA, SCL del Slave Controller
    int8_t SDA = 0;
    int8_t SCL = 0;

public:
    /**
     * Constructor de la clase SlaveController
     */
    SlaveController(int8_t sda, int8_t scl)
    {
        (*this).SDA = sda;
        (*this).SCL = scl;
    }
    /**
      * Cambia los pines del Slave Controller
     * @param sda pin sda
     * @param scl pin scl
     */
    void setPines(int8_t sda, int8_t scl)
    {
        (*this).SDA = sda;
        (*this).SCL = scl;
    }

    /**
     * Inicializa el esclavo por I2C
     * @param baudios velocidad del Serial
     */
    void initMaster(int baudios = 115200)
    {
        Wire.begin(SDA, SCL);  // join i2c bus (address optional for master)
        Serial.begin(baudios); // start serial for output
    }

    /**
     * Devuelve las mesuras de los sensores del esclavo seleccionado.
     * @param slaveAdress direccion del esclavo
     * @param bytesNumber bytes a pedir al esclavo.
     * @returns array de bytes (Todas las mesuras)
     */
    byte *requestMeasuresToSlave(uint8_t slaveAdress, uint8_t bytesNumber)
    {

        byte command = 0x30;

        // Envia una peticion para que cargue los valores de los sensores
        Wire.beginTransmission(slaveAdress);
        Wire.write((byte *)&command, sizeof(command));
        Wire.endTransmission();

        Serial.println("Waiting 13 seconds");

        bool waiting = false;
        while (true)
        {
            // puede recibir suscripciones mqtt mientras lee de los archivos
            mqttClient.poll();
            if (timerTrue(millSensorsRequest, 13000))
            {
                if (waiting)
                {
                    millSensorsRequest = millis();
                    waiting = false;
                    break;
                }
                if (!waiting)
                    waiting = true;

                millSensorsRequest = millis();
            }
        }

        // espera 5 segundos para la recepcion de datos y leidas de uarts

        // crea un array vacio
        byte *arrayData = new byte[bytesNumber];
        uint16_t i = 0; // contador

        // first call to get data
        Wire.requestFrom(slaveAdress, bytesNumber);

        // timer to read sensors
        while (Wire.available())
        {
            // se llena el array con los datos
            arrayData[i] = (byte)Wire.read();
            i++;
        }
        return arrayData;
    }

    /* Escanea la comunicacion I2C en busca de esclavos
     */
    void scanSlaves()
    {
        byte error, address;
        int nDevices;
        Serial.println("Scanning...");
        nDevices = 0;
        for (address = 1; address < 127; address++)
        {
            Wire.beginTransmission(address);
            error = Wire.endTransmission();
            if (error == 0)
            {
                Serial.print("I2C device found at address 0x");
                if (address < 16)
                {
                    Serial.print("0");
                }
                Serial.println(address, HEX);
                nDevices++;
            }
            else if (error == 4)
            {
                Serial.print("Unknow error at address 0x");
                if (address < 16)
                {
                    Serial.print("0");
                }
                Serial.println(address, HEX);
            }
        }
        if (nDevices == 0)
        {
            Serial.println("No I2C devices found\n");
        }
        else
        {
            Serial.println("done\n");
        }
        delay(5000);
    }
};

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
