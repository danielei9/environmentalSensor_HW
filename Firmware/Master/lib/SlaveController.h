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

    byte slaveAddresses[128];
    uint8_t numberOfSlaves = 0;

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
    void initMaster()
    {
        Wire.begin(SDA, SCL); // join i2c bus (address optional for master)
    }

    /**
     * Manda una peticion al esclavo seleccionado para que se despierte y coja las mediciones con antelicion antes de pedirlas
     * @param slaveAdress direccion del esclavo
     */
    void wakeUpSlaveAndTakeMeasures(uint8_t slaveAdress)
    {

        byte command = 0x30;

        // Envia una peticion para que cargue los valores de los sensores
        Wire.flush();
        Wire.beginTransmission(slaveAdress);
        Wire.write((byte *)&command, sizeof(command));
        Wire.endTransmission();
        delay(14);
        // delay between sends
    }

    /**
     * Devuelve las mesuras de los sensores del esclavo seleccionado.
     * @param slaveAdress direccion del esclavo
     * @param bytesNumber bytes a pedir al esclavo.
     * @returns array de bytes (Todas las mesuras)
     */
    byte *getMeasuresArrayFromSlave(uint8_t slaveAdress, uint8_t bytesNumber)
    {
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
        Serial.println("Received");
        delay(50);
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
                // hace una busqueda de esclavos
                bool found = 0;
                for (int i = 0; i < 127; i++)
                {
                    if (slaveAddresses[i] == address)
                    {
                        // si se encontro
                        found = 1;
                    }
                }
                // si no se ha encontrado el dispositivo
                if (!found)
                {
                    slaveAddresses[numberOfSlaves] = address;
                    numberOfSlaves++;
                    found = 0;
                }
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
        Serial.println("Devices in arraylist: ");
        for (int i = 0; i < 127; i++)
        {
            if (slaveAddresses[i] != 0)
            {
                Serial.print("0x");
                Serial.println(slaveAddresses[i], HEX);
            }
        }
    }

    // devuelve el array de esclavos disponibles
    byte getSlaves()
    {
        scanSlaves();
        return *slaveAddresses;
    }
};

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
