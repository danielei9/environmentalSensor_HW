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

#define uS_TO_S_FACTOR 1000000ULL // Conversion factor for micro seconds to seconds
#define TIME_TO_SLEEP 60          // Time ESP32 will go to sleep (in seconds)

#define UART_BAUD 9600
#define PIN_TX 27
#define PIN_RX 26
#define PWR_PIN 4
#define LED_PIN 12

#define I2C_SDA 21
#define I2C_SCL 22

// Set serial for debug console (to Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set serial for AT commands (to SIM7000 module)
#define SerialAT Serial1
#ifndef MODEM
#define MODEM
// Configure TinyGSM library
#define TINY_GSM_MODEM_SIM7000SSL // Modem is SIM7000
#define TINY_GSM_RX_BUFFER 1024   // Set RX buffer to 1Kb
#include <TinyGsmClient.h>

// #define DUMP_AT_COMMANDS
#define DUMP_AT_COMMANDS
#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif
#endif

// --------------------------------------------------------------
// --------------------------------------------------------------
class GPS
{
private:

    /**
     * Enciende el GPS
     */
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

    /**
     * Apaga el gps
     */
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
    /**
     * Enciende el led azul
     */
    void modemPowerOn()
    {
        pinMode(PWR_PIN, OUTPUT);
        digitalWrite(PWR_PIN, LOW);
        delay(1000); //Datasheet Ton mintues = 1S
        digitalWrite(PWR_PIN, HIGH);
    }

    /**
     * Apaga el led azul
     */
    void modemPowerOff()
    {
        pinMode(PWR_PIN, OUTPUT);
        digitalWrite(PWR_PIN, LOW);
        delay(1500); //Datasheet Ton mintues = 1.2S
        digitalWrite(PWR_PIN, HIGH);
    }

    /**
     * Resetea el modem para el GNSS
     */
    void modemRestart()
    {
        modemPowerOff();
        delay(1000);
        modemPowerOn();
    }

public:
    /**
     * Inicializa el GPS
     */
    void init()
    {
        SerialMon.begin(115200);
        delay(10);

        // Set LED OFF
        pinMode(LED_PIN, OUTPUT);
        digitalWrite(LED_PIN, HIGH);

        modemPowerOn();

        SerialAT.begin(UART_BAUD, SERIAL_8N1, PIN_RX, PIN_TX);

        Serial.println("/**********************************************************/ ");
        Serial.println("To initialize the network test, please make sure your GPS");
        Serial.println("antenna has been connected to the GPS port on the board.");
        Serial.println("/**********************************************************/\n\n");

        // se hace la configuracion para que se conecte a la constelacion de satelites de GALILEO (En el caso de EUROPA)
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

    /**
     * Obtiene la latitud y longitud en un array cuando se detecta. Tiene un timeout de 10 segundos si no encuentra la posicion
     * @returns *coords [0] = lat;  [1] = long
     */
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

        unsigned int times = 0;
        const unsigned int timeOut = 10000;
        bool foundCoords = false;

        float lat, lon;
        //timeout de 10 segundos
        while (1)
        {
            if (times > 5)
            {
                break;
            }
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
            delay(2000);
            times++;
            digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        }

        disableGPS();

        if (foundCoords)
        {
            return *coords;
        }
        else
        {
            // mostrara este mensaje si han pasado 10 segundos desde el pedido de datos
            Serial.println("GPS TIMEOUT!");
            return *coords;
        }
    }
    /**
     * Test del gps. Obtiene las coordenadas indefinidamente
     */
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

        // se queda en bucle cuando se han encontrado las coordenadas
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
