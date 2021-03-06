// -*- mode: c++ -*-

// --------------------------------------------------------------
// Autor: Yeray Candel Sampedro
// Date: 01 - 12 - 2021
//
// Description: Clase GPS
// --------------------------------------------------------------

#ifndef GPS_H_INCLUDED
#define GPS_H_INCLUDED

#include <Arduino.h>
#include <../lib/Utils.h>
#include <../lib/Protocol4G.h>

#define uS_TO_S_FACTOR 1000000ULL // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP 60          // Time ESP32 will go to sleep (in seconds)

#define UART_BAUD 9600
#define PIN_DTR 25
#define PIN_TX 27
#define PIN_RX 26
#define PWR_PIN 4

#define SD_MISO 2
#define SD_MOSI 15
#define SD_SCLK 14
#define SD_CS 13
#define LED_PIN 12

// --------------------------------------------------------------
// --------------------------------------------------------------
class GPS
{
private:
    void enableGPS(void)
    {
        // Set SIM7000G GPIO4 LOW ,turn on GPS power
        // CMD:AT+SGPIO=0,4,1,1
        // Only in version 20200415 is there a function to control GPS power

        modem.sendAT(GF("+SGPIO=0,4,1,1"));
        delay(2000);
        modem.sendAT(GF("+CGNSPWR=1"));
        delay(2000);
        modem.enableGPS();
    }

    void disableGPS(void)
    {
        // Set SIM7000G GPIO4 LOW ,turn off GPS power
        // CMD:AT+SGPIO=0,4,1,0
        // Only in version 20200415 is there a function to control GPS power
        modem.sendAT(GF("+SGPIO=0,4,1,0"));
        delay(2000);
        modem.sendAT(GF("+CGNSPWR=0"));
        delay(2000);
        modem.disableGPS();
    }

    void modemPowerOn()
    {
        pinMode(PWR_PIN, OUTPUT);
        digitalWrite(PWR_PIN, LOW);
        delay(1000); //Datasheet Ton mintues = 1S
        digitalWrite(PWR_PIN, HIGH);
    }

    void modemPowerOff()
    {
        pinMode(PWR_PIN, OUTPUT);
        digitalWrite(PWR_PIN, LOW);
        delay(1500); //Datasheet Ton mintues = 1.2S
        digitalWrite(PWR_PIN, HIGH);
    }

    void modemRestart()
    {
        modemPowerOff();
        delay(1000);
        modemPowerOn();
    }

public:
    void init()
    {
        SerialMon.begin(115200);
        delay(10);

        // Set LED OFF
        pinMode(LED_PIN, OUTPUT);
        digitalWrite(LED_PIN, HIGH);

        modemPowerOn();

        SerialAT.begin(UART_BAUD, SERIAL_8N1, PIN_RX, PIN_TX);

        Serial.println("/**********************************************************/");
        Serial.println("To initialize the network test, please make sure your GPS");
        Serial.println("antenna has been connected to the GPS port on the board.");
        Serial.println("/**********************************************************/\n\n");

        modem.sendAT(GF("+SGNSCFG: \"NMEATYPE\",2"));
        delay(2000);
        modem.sendAT(GF("+CGNSPWR=1"));
        delay(2000);
        modem.sendAT(GF("+SGNSCFG: \"MODE\",1"));
        delay(2000);
        modem.sendAT(GF("+CGNSMOD=?"));
        delay(2000);
        modem.sendAT(GF("+CGNSMOD=1"));
        delay(2000);
    }

    float *getCoords()
    {
        if (!modem.testAT())
        {
            Serial.println("Failed to restart modem, attempting to continue without restarting");
            modemRestart();
        }

        float *coords[2];

        Serial.println("Start positioning . Make sure to locate outdoors.");
        Serial.println("The blue indicator light flashes to indicate positioning.");

        enableGPS();

        unsigned int timeGettingCoords = 0;
        const unsigned int timeOut = 10000;
        bool foundCoords = false;

        float lat, lon;
        //timeout de 10 segundos
        while ((millis() - timeGettingCoords) >= timeOut)
        {
            if (modem.getGPS(&lat, &lon))
            {
                Serial.println("The location has been locked, the latitude and longitude are:");
                Serial.print("latitude:");
                Serial.println(lat);
                Serial.print("longitude:");
                Serial.println(lon);
                foundCoords = true;
                break;
            }
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));
            delay(2000);

            timeGettingCoords = millis();
        }

        disableGPS();

        if (foundCoords)
        {
            return *coords;
        }
        else
        {
            Serial.println("GPS TIMEOUT!");
            return *coords;
        }
    }

    void testLoop()
    {

        if (!modem.testAT())
        {
            Serial.println("Failed to restart modem, attempting to continue without restarting");
            modemRestart();
            return;
        }

        Serial.println("Start positioning . Make sure to locate outdoors.");
        Serial.println("The blue indicator light flashes to indicate positioning.");

        enableGPS();

        float lat, lon;
        while (1)
        {
            if (modem.getGPS(&lat, &lon))
            {
                Serial.println("The location has been locked, the latitude and longitude are:");
                Serial.print("latitude:");
                Serial.println(lat);
                Serial.print("longitude:");
                Serial.println(lon);
                break;
            }
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));
            delay(2000);
        }

        disableGPS();

        Serial.println("/**********************************************************/");
        Serial.println("After the network test is complete, please enter the  ");
        Serial.println("AT command in the serial terminal.");
        Serial.println("/**********************************************************/\n\n");

        while (1)
        {
            while (SerialAT.available())
            {
                SerialMon.write(SerialAT.read());
            }
            while (SerialMon.available())
            {
                SerialAT.write(SerialMon.read());
            }
        }
    }
};

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
