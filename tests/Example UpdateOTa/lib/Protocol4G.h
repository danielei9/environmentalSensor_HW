// -*- mode: c++ -*-

// --------------------------------------------------------------
// Autor: Yeray Candel Sampedro
// Date: 01 - 11 - 2021
//
// Description: Clase 4G encargada de manejar el protocolo de comunicacion con
// la plataforma via MQTT con 4G
// --------------------------------------------------------------

#ifndef PROTOCOL_4G_H_INCLUDED
#define PROTOCOL_4G_H_INCLUDED

#include "Publisher.h"
#include <Arduino.h>
#include <ArduinoMqttClient.h>
#include <../lib/Utils.h>
#include <esp_tls.h>
#include <../lib/TLS/clientcert.h>
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
#include <TinyGsmClient.h>

#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h>
StreamDebugger debugger(SerialAT, SerialMon);
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT);
#endif

TinyGsmClientSecure client(modem);
#include <Wire.h>

// I2C
TwoWire I2CPower = TwoWire(0);

// MQTT CLIENT
MqttClient mqttClient(client);

const char broker[] = "gesinen.es";
int port = 8882;
const char *username = "gesinen";
const char *password = "gesinen2110";
// /codigoPostal/ambiental/idDispositivo/
char topic[] = "46701/ambiental/1/";
const char codigoPostal[] = "";
const char idDispositivo[] = "";

const char topicSubscribed[] = "gesinen/#";

const long interval = 1000;
unsigned long previousMillis = 0;
// --------------------------------------------------------------
// --------------------------------------------------------------
class Protocol4G : public Publisher
{
private:
    const char *apn = "";

    const char *gprsUser = "";

    const char *gprsPass = "";

    const char *simPin = "";

    /**
     * Se contecta al broker MQTT
     */
    void initMqtt()
    {

        // inicializa la conexion MQTT
        while (1)
        {
            if (mqttClient.connect(broker, port))
            {
                break;
                
            }
        }
        if (!mqttClient.connect(broker, port))
        {
            Serial.print("MQTT connection failed! Error code = ");
            Serial.println(mqttClient.connectError());

            while (1)
                ;
        }

        Serial.println("You're connected to the MQTT broker!");
        Serial.println();
    }

    /**
     * Se subscribe a un topico
     * @param topic direccion del topico a subscribirse
     */
    void subscribeToTopic(const char *topic)
    {
        mqttClient.onMessage(onMqttMessage);

        Serial.print("Subscribing to topic: ");
        Serial.println(topic);
        Serial.println();

        // Suscripcion a un 'topic'
        mqttClient.subscribe(topic);
    }

    /**
     * Recibe mensajes de los topicos
     * @param messageSize tamaño del mensaje
     */
    static void onMqttMessage(int messageSize)
    {

        // we received a message, print out the topic and contents
        String topic = mqttClient.messageTopic();
        String payload = mqttClient.readString();
        Serial.println("incoming: " + topic + ", length: " + messageSize + " ");
        Serial.println(payload);
        if (payload == "ON")
        {
            Serial.println("Encender Dispositivo");
        }
        else if (payload == "OFF")
        {
            Serial.println("Apagar Dispositivo");
        }

        Serial.println();
    }

    /*
    * Instancia los credenciales
    */
    void setMqttCredentials()
    {
        esp_tls_set_global_ca_store(certYcansam, sizeof(certYcansam));
        ESP_LOGI("TEST", "CA store set. Error = %d %s", err, esp_err_to_name(err));
        mqttClient.setUsernamePassword(username, password);
    }

public:
    /**
     * Crea el protocolo.
     */
    Protocol4G(const char *apn, const char *gprsUser, const char *gprsPass, const char *simPin = "")
    {
        (*this).apn = apn;
        (*this).gprsUser = gprsUser;
        (*this).gprsPass = gprsPass;
        (*this).simPin = simPin;
        // void
    }
    /**
     * (Virtual)
     * Inicializa el publicador
     * @param apn
     * @param gprsUser
     * @param gprsPass
     * @param simPin
     */
    virtual void initPublisher();

    /**
     * join() Se une a la red.
     *  @returns bool -> devuelve TRUE si se ha conectado a la red y al MQTT y FALSE si no.
     */
    bool join()
    {
        if (!modem.isGprsConnected())
        {
            SerialMon.print("Connecting to APN: ");
            SerialMon.print(apn);

            if (!modem.gprsConnect(apn, gprsUser, gprsPass))
            {
                SerialMon.println(" fail");
                return false;
            }
            else
            {
                SerialMon.println(" Connected");

                // Setting Up Credentials
                // setMqttCredentials();

                // Inicializa el MQTT despues de conectarse
                // initMqtt();

                // se suscribe a un topico
                // subscribeToTopic(topicSubscribed);

                return true;
            }
        }
        else
        {
            return true;
        }
    }

    /**
     * sendData() Envia los datos a la plataforma
     * @param arrayData -> Array de bytes con los datos a enviar
     */
    void sendData(uint8_t *arrayData)
    {
        String topicSend = topic;

        mqttClient.poll();

        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval)
        {
            // save the last time a message was sent
            previousMillis = currentMillis;

            Serial.println("Sending message to topic: ");
            Serial.println(topicSend);

            // send message, the Print interface can be used to set the message contents
            mqttClient.beginMessage(topicSend);

            String message = "{\"deviceEui\":1,\"value\": 25.222,\"type\": \"co2\", \"unit\": \"ppm\"}";
            mqttClient.println(message);
            mqttClient.endMessage();

            Serial.println(" ");
            Serial.println(" ");
        }
    }

    void receiveData(byte *arrayData)
    {
    }

}; // class

/**
 * Inicializa la clase 4G
 * @param apn
 * @param gprsUser
 * @param gprsPass
 * @param simPin pin de la tarjeta sim
 */
void Protocol4G::initPublisher()
{
    Serial.begin(115200);

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
}

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif
