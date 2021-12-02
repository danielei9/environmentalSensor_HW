
#ifndef CJMCU_H_INCLUDED
#define CJMCU_H_INCLUDED
#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_CCS811.h"
#include "Adafruit_GFX.h"

Adafruit_CCS811 ccs;

void initCJM()
{
    Wire.begin(21, 22);
    Wire.setClock(400000);
    Serial.begin(115200);
    if (!ccs.begin(0x5A, &Wire))
    {
        Serial.println("Failed to start sensor! Please check your wiring.");
        while (1)
            ;
    }

    delay(500);

    //calibrate temperature sensor
    while (!ccs.available())
        ;
    float temp = ccs.calculateTemperature();
    ccs.setTempOffset(temp - 25.0);

    Serial.println("IO test");
}

void getCJMData()
{
    if (ccs.available())
    {
        float temp = ccs.calculateTemperature();
        delay(200);
        if (!ccs.readData())
        {
            Serial.print("eCO2: ");
            float eCO2 = ccs.geteCO2();
            Serial.print(eCO2);

            Serial.print(" ppm, TVOC: ");
            float TVOC = ccs.getTVOC();
            Serial.print(TVOC);

            Serial.print(" ppb   Temp:");
            Serial.println(temp);
        }
        else
        {
            Serial.println("ERROR!");
        }
    }
    delay(500);
}

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
