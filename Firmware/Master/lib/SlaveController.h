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
    {
        (*this).SDA = sda;
        (*this).SCL = scl;
    }

    /**
     * Inicializa el esclavo por I2C
     */
    void initSlave(int baudios = 115200)
    {
        Wire.begin();          // join i2c bus (address optional for master)
        Serial.begin(baudios); // start serial for output
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
     * Devuelve las mesuras de los sensores del esclavo seleccionado.
     * @param slaveAdress direccion del esclavo.
     * @returns array de bytes (Todas las mesuras)
     */
    byte* getSlaveMeasures(int8_t slaveAdress, unsigned int bytesNumber = 50)
    {
        Wire.requestFrom(slaveAdress, bytesNumber); // request 6 bytes from slave device #8

        // crea un array vacio
        byte *arrayData = new byte[bytesNumber];
        int i = 0; // contador

        while (Wire.available())
        {                         // slave may send less than requested
            byte c = Wire.read(); // receive a byte as character
            // poniendo los bytes transmitidos por el eslavo en el array de bytes
            arrayData[i] = c;
            i++;
        }
        return arrayData;
    }
};