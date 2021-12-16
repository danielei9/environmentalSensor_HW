// -*- mode: c++ -*-

// --------------------------------------------------------------
// Autor: Daniel Burruchaga Sola
// Date: 03 - 12 - 2021
// Name: Example LORA 
// Description: Lora Test 
// Se encarga de Realizar join con gateway lora y envio de datos 
// --------------------------------------------------------------
#define CFG_sx1276_radio 1 // HPD13A LoRa SoC

#include <Arduino.h>
#include <lmic.h>
#include <hal/hal.h>
#include <SPI.h>
#include <loraLib.hpp>
LoraOTAA Lora;
static uint8_t mydata[] = "Hello, world!";

void setup() {
    Serial.begin(9600);
    Serial.println(F("Starting"));

    #ifdef VCC_ENABLE
    // For Pinoccio Scout boards
    pinMode(VCC_ENABLE, OUTPUT);
    digitalWrite(VCC_ENABLE, HIGH);
    delay(1000);
    #endif

    // LMIC init
     Lora.initPublisher();
    // Start job (sending automatically starts OTAA too)
    Lora.sendData(&sendjob,mydata,3,sizeof(mydata));
}
unsigned long mill = 0;

// /**
//      * create a counter with millis
//      * @param lastmillis_ last time
//      * @param interval time interval to return true
//      */
// bool timerTrue(unsigned long lastmillis_, int interval)
// {
//     if (millis() > (lastmillis_ + interval))
//         return true;

//     return false;
// }

void loop() {
    os_runloop_once();
       if (timerTrue(mill, 20000))
        {
    Lora.sendData(&sendjob,mydata,3,sizeof(mydata));
            mill = millis();
        }
}
