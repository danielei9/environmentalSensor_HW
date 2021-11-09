// -*- mode: c++ -*-

// --------------------------------------------------------------
// autor: Yeray Candel Sampedro
// date: 09 - 11 - 2021
// copyright: Copyright (c) 2021 Yeray Candel Sampedro
// description: Publishers Controllers
// --------------------------------------------------------------

#include <Arduino.h>
#include "Publisher.h"

#ifndef PUBLISHERSCLIENT_H
#define PUBLISHERSCLIENT_H

// Publisher *publisher = new Protocol4G(); // forma 1 de definir
// Publisher *publisher = &protocol4G;                    // forma 2 mediante direccion
// Publisher *const publishers[2] = {&protocol4G, &Lora}; // forma 3 array

#if defined(PROTOCOL_4G) // si se define el protocolo 4G

    #include <../lib/Protocol4G.h>
    Protocol4G protocol4G("orangeworld", "orange", "orange"); // constructor normal
    Publisher *publisher = &protocol4G;                       // forma 2 mediante direccion

#elif defined(PROTOCOL_LORA) // si se define el protocolo LORA

    #include <../lib/LoraOTAA.h>
    LoraOTAA Lora;
    Publisher *publisher = &Lora; // forma 2 mediante direccion

    void onEvent(ev_t ev)
    {
        Lora.onEventLora(ev);
    }
    bool timerTrue(unsigned long lastmillis_, int interval);
    #endif

#endif
