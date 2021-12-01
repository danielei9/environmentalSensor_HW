// -*- mode: c++ -*-

/** --------------------------------------------------------------
 * Autor: Yeray Candel Sampedro
 * Date: 09 - 11 - 2021
 *
 * Description: ejemplo de uso de la clase SLAVE CONTROLLER
 * --------------------------------------------------------------
 */

#include <Arduino.h>
#include <../lib/SlaveController.h>
#include "../lib/Utils.h"
unsigned long mill = 0;

// constructor
SlaveController slaveController(21, 22);

void setup()
{
    // Inicializa la clase slavecontroller con direcicon de I2C SDA = 21 y SCL = 22
    // El maestro se inicializa sin direccion
    slaveController.initMaster();
}
void loop()
{
    // !IMPORTANT 
    // HACER UN SCANEO DE LOS PUERTOS I2C PARA DETECTAR DIRECCIONES DE ESCLAVOS.

    slaveController.scanSlaves();  // COMENTAR LINEA SI SE HAN ESCANEADO CORRECTAMENTE

    if (timerTrue(mill, 10000))
    {
        // Hace una peticion de 8 bytes a el eslavo con la direccion 0x20. Este deberia devolver el array de datos.
        Serial.println("Requesting sensors data..");
        uint8_t bytesToRequest = 8;
        byte *arrayData = slaveController.requestMeasuresToSlave(0x20, bytesToRequest);

        printBytesArray(arrayData, bytesToRequest);

        mill = millis();
    }
}
