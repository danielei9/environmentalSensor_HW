// -*- mode: c++ -*-

// --------------------------------------------------------------
// Yeray Candel Sampedro
// 01 - 11 - 2021
//
// Clase 4G encargada de manejar el protocolo de comunicacion con
// la plataforma via 4G
// --------------------------------------------------------------

#ifndef PROTOCOL_4G_H_INCLUDED
#define PROTOCOL_4G_H_INCLUDED

#include "Publisher.h"
#include <Arduino.h>
#include <Wire.h>
// #include <TinyGsmClient.h>

// TTGO T-Call pins
#define MODEM_RST 5
#define MODEM_PWKEY 4
#define MODEM_POWER_ON 23
#define MODEM_TX 27
#define MODEM_RX 26
#define I2C_SDA 21
#define I2C_SCL 22

// Set serial for debug console (to Serial Monitor, default speed 115200)
#define SerialMon Serial
// Set serial for AT commands (to SIM800 module)
#define SerialAT Serial1

// Configure TinyGSM library
#define TINY_GSM_MODEM_SIM7070  // Modem is SIM800
#define TINY_GSM_RX_BUFFER 1024 // Set RX buffer to 1Kb
#include "TinyGsmClientSIM7080.h"
typedef TinyGsmSim7080 TinyGsm;
typedef TinyGsmSim7080::GsmClientSim7080 TinyGsmClient;
typedef TinyGsmSim7080::GsmClientSecureSIM7080 TinyGsmClientSecure;

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

TinyGsmClient client(modem);

// I2C
TwoWire I2CPower = TwoWire(0);

// variable para indicar si se ha conectado a la red o no
bool joined = false;
// --------------------------------------------------------------
// --------------------------------------------------------------
class Protocol4G : public Publisher
{
private:
    const char *apn = "";

    const char *gprsUser = "";

    const char *gprsPass = "";

    const char *simPin = "";

public:
    /**
     * Crea el protocolo.
     */
    Protocol4G()
    {
        // void
    }
    /**
     *Inicializa el publicador
     */
    virtual void initPublisher(const char *apn, const char *gprsUser, const char *gprsPass, const char *simPin);

    /**
     * join() Se une a la red.
     *  @returns bool -> devuelve TRUE si se ha conectado a la red y FALSE si no.
     */
    bool join()
    {
        if (!joined)
        {
            SerialMon.print("Connecting to APN: ");
            SerialMon.print(apn);

            if (!modem.gprsConnect(apn, gprsUser, gprsPass))
            {
                SerialMon.println(" fail");
                joined = false;
                return joined;
            }
            else
            {
                SerialMon.println(" Connected");
                joined = true;
                return joined;
            }
            return false;
        }
        else
        {
            return true;
        }
    }

    /**
     * sendData() Envia los datos a la plataforma
     * 
     * @param arrayData -> Array de bytes con los datos a enviar
     */
    void sendData(uint8_t *arrayData)
    {

    }

    void receiveData()
    {
    }

}; // class
void Protocol4G::initPublisher(const char *apn, const char *gprsUser, const char *gprsPass, const char *simPin)
{
    (*this).apn = apn;
    (*this).gprsUser = gprsUser;
    (*this).gprsPass = gprsPass;
    (*this).simPin = simPin;

    Serial.print((*this).simPin);

    // Start I2C communication
    I2CPower.begin(I2C_SDA, I2C_SCL, 400000);

    // Set modem reset, enable, power pins
    pinMode(MODEM_PWKEY, OUTPUT);
    pinMode(MODEM_RST, OUTPUT);
    pinMode(MODEM_POWER_ON, OUTPUT);
    digitalWrite(MODEM_PWKEY, LOW);
    digitalWrite(MODEM_RST, HIGH);
    digitalWrite(MODEM_POWER_ON, HIGH);

    // Set GSM module baud rate and UART pins
    SerialAT.begin(115200, SERIAL_8N1, MODEM_RX, MODEM_TX);
    delay(3000);

    // Restart SIM800 module, it takes quite some time
    // To skip it, call init() instead of restart()
    SerialMon.println("Initializing modem...");
    modem.restart();
    // use modem.init() if you don't need the complete restart

    // Unlock your SIM card with a PIN if needed
    if (strlen(simPin) && modem.getSimStatus() != 3)
    {
        modem.simUnlock(simPin);
    }
    else
    {
        Serial.print("Pin Incorrect");
    }
}

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
