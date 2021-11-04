// -*- mode: c++ -*-
// --------------------------------------------------------------
// Yeray Candel Sampedro
// 01 - 11 - 2021
//
// Clase (Abstracta) Publicador que se encarga de manejar los
// protocolos de comunicacion entre la plataforma y el
// arduino.
// --------------------------------------------------------------
#include <Arduino.h>
#ifndef PUBLISHER_H_INCLUDED
#define PUBLISHER_H_INCLUDED

// --------------------------------------------------------------
// --------------------------------------------------------------
class Publisher
{
public:
    // publica los datos
    virtual void sendData(uint8_t *){}
    virtual void initPublisher(){}
    /**
     * cleanData() Borra los datos del array
     * 
     * @param arrayData -> Array de bytes que se va a vaciar
     */
    void cleanData(uint8_t *arrayData)
    {
        for (int i = 0; i < sizeof(arrayData); i++)
        {
            arrayData[i] = 0;
        }
    };
}; // class

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
