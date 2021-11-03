// -*- mode: c++ -*-

// --------------------------------------------------------------
// Yeray Candel Sampedro
// 01 - 11 - 2021
//
// Clase (Abstracta) Publicador que se encarga de manejar los
// protocolos de comunicacion entre la plataforma y el
// arduino.
// --------------------------------------------------------------

#ifndef PUBLISHER_H_INCLUDED
#define PUBLISHER_H_INCLUDED
#include <Arduino.h>

// --------------------------------------------------------------
// si el metodo es puramente virtual = 0 -> no se puede hacer overload
// si se necesita hacer overload ha de ser quitando "= 0" y poner "{}"
// --------------------------------------------------------------
class Publisher
{
public:
    // inicializa el publicador
    //no es puramente virtual por que se necesita hacer overload tanto en la clase lora como 4g
    virtual void initPublisher()
    {
        Serial.println("Failed on Init Publisher: Needs to be 4G or Lora");
    }

    // se conecta a la red
    virtual bool join() = 0;

    // publica los datos
    virtual void sendData(uint8_t *) = 0;

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

    // recibe datos
    virtual void receiveData() = 0;
    virtual ~Publisher() {}
}; // class

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
