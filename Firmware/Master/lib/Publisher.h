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
// si el metodo es puramente virtual = 0 -> no se puede hacer overload
// si se necesita hacer overload ha de ser quitando "= 0" y poner "{}"
// --------------------------------------------------------------

class Publisher
{
public:
    // inicializa el publicador
    //no es puramente virtual por que se necesita hacer overload tanto en la clase lora como 4g
    virtual void initPublisher() = 0;
    /**
     *  Se une a la red.
     *  @returns bool -> devuelve TRUE si se ha conectado a la red  y FALSE si no.
     */
    virtual bool join() = 0;

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
