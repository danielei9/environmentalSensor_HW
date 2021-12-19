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

    /**
     * Obtiene un array de datos con la informacion del modulo
     * Informacion de 8 bytes.
     * 
     *     0    1    2    3    4    5    6    7    8
     * EJ: 0x17 0x00 0XC8 0x02 0x00 0x00 0x00 0x01 0x1E
     */
    bool getSensorInformation()
    {
        // si es distinto del tipo obtenido anteriormente vuelve a escanear el sensor
        if (sensorUnit != sensorInformation[5] || sensorType != sensorInformation[2])
        {
            // envia el comando para escuchar a los sensores
            byte arrayCommand[1] = {0xD7};
            writeCommand(arrayCommand, 1);

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
     * Se encarga de leer las medidas
     * @returns devuelve true si se ha leido y false si no
     */
    int read()
    {
        // intenta obtener la informacion del sensor si ha cambiado. Si no ha cambiado no lee la informacion
        getSensorInformation();

        // escribe en la uart el comando para obtener medidas del sensor
        byte arrayCommand[9] = {0xFF, 0x01, 0x86, 0x00, 0x00, 0x00, 0x00, 0x00, 0x79};
        writeCommand(arrayCommand, 9);

        // escucha al sensor con una respuesta de 9 bytes.
        bool response = listenToResponse(9);
        if (response)
        {
            Serial.println("Sensor Readed");
            return response;
        }
        return response;
    }
    /**
     * Duerme al sensor
     * @returns devuelve true si se ha dormido y false si no
     */
    bool sleepSensor()
    {
        // envia el comando para escuchar al sensor
        byte arrayCommand[6] = {0xAF, 0x53, 0x6C, 0x65, 0x65, 0x70};
        writeCommand(arrayCommand, 6);

        // espera a la escucha de la respuesta del sensor si se ha dormido o no.
        bool response = listenToResponse(2);
        if (response)
        {
            Serial.println("Sensor is sleeping...");
            return response;
        }
        return response;
    }

    /**
     * Despierta al sensor
     * @returns devuelve true si se ha despertado y false si no
     */
    bool wakeUpSensor()
    {
        // envia el comando para despertar al sensor
        byte arrayCommand[5] = {0xAE, 0x45, 0x78, 0x69, 0x74};
        writeCommand(arrayCommand, 5);

        // espera una respuesta del sensor
        bool response = listenToResponse(2);
        if (response)
        {
            Serial.println("Sensor exited from deep Sleep");
            return response;
        }
        return response;
    }

    /**
     * Envia comandos por uart al sensor
     * @param array array con el comando a enviar
     * @param size es el tamaño del comando
     */
    void writeCommand(byte *array, uint8_t size)
    {
        if (!(*this).sendCommand)
        {
            // enviando el comando a la uart del sensor
            for (int i = 0; i < size; i++)
            {
                sensorSerial->write(array[i]);
            }
            (*this).sendCommand = true;
        }
    }
    /**
     * Escucha a la respuesta del sensor despues de enviar un comando
     * @param size es el tamaño de la respuesta
     * @return devuelve true si se ha leido y false si no
     */
    bool listenToResponse(uint8_t size)
    {
        if (!(*this).readed)
        {
            sensorSerial->listen();
            while (sensorSerial->available() > 0)
            {

                int data = sensorSerial->read();
                arrayData[counter] = data;
                Serial.println(data);
                (*this).counter++;
                if ((*this).counter == size)
                {
                    (*this).readed = true;
                    return (*this).readed;
                }
                /* code */
            }
        }
        return (*this).readed;
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
    /**
     * Inicializa el Sensor
     */
    void initSensor(uint16_t baudios = 9600)
    {
        sensorSerial->begin(baudios);
        getSensorInformation();
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
    uint8_t getType()
    {
        // si el tipo es diferente o no existe llama a la funcion para encontrar el tipo
        if (sensorType != -1 && sensorInformation[2] == sensorType)
            return (sensorType);
        else
        {
            getSensorInformation();
        }
    }

    /**
     * Devuelve la unidad en la que se mide el sensor.
     * @returns HEXADECIMAL tipo
     */
    uint8_t getUnit()
    {
        // si el tipo es diferente o no existe llama a la funcion para encontrar el tipo de unidad
        if (sensorUnit != -1 && sensorInformation[5] == sensorUnit)
            return (sensorUnit);
        else
        {
            sensorInformation[5] = 0;
            getSensorInformation();
        }
    }
    /**
     * Se encarga de llamar al sensor para realizar las mediciones
     */
    void getMeasure()
    {
        bool sensorReaded = false;
        while (!sensorReaded)
        {
            if (read() == 1)
            {
                sensorReaded = true;
                Serial.print("Sensor Leido ");
                Serial.println(getGasConcentration());
                break;
            }
            if (timerTrue(mill, 500))
            {
                sensorReaded = true;
                Serial.println("Timeout ");
                mill = millis();
                break;
            }
        }
    }

    /**
     * Obtiene toda la informacion del sensor Unidad / tipo / etc
     */
    void getInformation()
    {
        bool sensorReaded = false;
        while (!sensorReaded)
        {
            if (getSensorInformation() == 1)
            {
                sensorReaded = true;
                Serial.print("Sensor Type Obtained: ");
                Serial.println(getType());
                break;
            }
            if (timerTrue(mill, 200))
            {
                sensorReaded = true;
                Serial.println("Timeout on get sensor information ");
                mill = millis();
                break;
            }
        }
    }

    /**
     * Se encarga de llamar a la funcion para dormir al sensor
     */
    void sleep()
    {
        bool sensorReaded = false;
        while (!sensorReaded)
        {
            if (sleepSensor() == 1)
            {
                sensorReaded = true;
                break;
            }
            if (timerTrue(mill, 200))
            {
                sensorReaded = true;
                Serial.println("Timeout on sleep sensor");
                mill = millis();
                break;
            }
        }
    }
    /**
     * Se encarga de ejecutar la llamada del sensor para despertarlo
     */
    void wakeUp()
    {
        bool sensorReaded = false;
        while (!sensorReaded)
        {
            if (wakeUpSensor() == 1)
            {
                sensorReaded = true;
                break;
            }
            if (timerTrue(mill, 200))
            {
                sensorReaded = true;
                Serial.println("Timeout on Wake Up Sensor ");
                mill = millis();
                break;
            }
        }
    }

    /**
     * Resetea el array que contiene la informacion del sensor
     */
    void resetArrays()
    {
        for (int i = 0; i < 9; i++)
        {
            (*this).sensorInformation[i] = 0;
            (*this).arrayData[i] = 0;
        }
    }
};

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
