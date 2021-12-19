// -*- mode: c++ -*-

// --------------------------------------------------------------
// Autor: Yeray Candel Sampedro
// Date: 01 - 11 - 2021
//
// Description: Clase 4G encargada de manejar el protocolo de comunicacion con
// la plataforma via MQTT con 4G
// --------------------------------------------------------------
#ifndef DEVEUI_DEF

#define DEVEUI_DEF                                     \
    {                                                  \
        0x64, 0x47, 0x1d, 0xa3, 0xe1, 0x71, 0x99, 0x13 \
    }
#endif
#ifndef PROTOCOL_4G_H_INCLUDED
#define PROTOCOL_4G_H_INCLUDED

#include "Publisher.h"
#include <Arduino.h>
#include "../lib/Sensor.h"
#include <ArduinoMqttClient.h>
#include <../lib/Utils.h>
#include <esp_tls.h>
#include <../lib/TLS/clientcert.h>
#include <../lib/OTA/OTAUpdate.hpp>
OTAUpdate OTAUpd;

// TTGO T-Call pins
#define MODEM_RST 5
#define MODEM_PWKEY 4
#define MODEM_POWER_ON 23
#define MODEM_TX 27
#define MODEM_RX 26
#define I2C_SDA 21
#define I2C_SCL 22

#include <Wire.h>

// I2C
TwoWire I2CPower = TwoWire(0);

// MQTT CLIENT
MqttClient mqttClient(client);

const char broker[] = "gesinen.es";
// const char broker[] = "broker.hivemq.com";
int port = 8882;
// int port = 1883;
const char *username = "gesinen";
const char *password = "gesinen2110";
// /codigoPostal/ambiental/idDispositivo/
char topic[] = "46701/ambiental/1/";
const char codigoPostal[] = "";
const char idDispositivo[] = "";

const char topicSubscribed[] = "46701/ambiental/2/#";

const long interval = 1000;
unsigned long previousMillis = 0, lmill = 0;
bool sync = false;
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
        Serial.println("Connecting to MQTT..");
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

    static void scheduleRxMqtt(String payload, String topic)
    {

        Serial.println("recived payload");
        Serial.println(payload);
        if (payload == "ON")
        {
            Serial.println("Encender Dispositivo");
        }
        else if (payload == "OFF")
        {
            Serial.println("Apagar Dispositivo");
        }
        else if (payload == "UPDATE")
        {
            Serial.println("UPDATE");
            OTAUpd.updateFromServer();
        }
        if ((payload == "{\n\"SYNCHRONIZED\":\"64:47:1d:a3:e1:71:99:13\"\n}") and (topic == "deviceSync"))
        {
            Serial.println("SYNCHRONIZED");
            sync = true;
        }
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
        Serial.println();
        scheduleRxMqtt(payload, topic);
    }
    /*
    * Instancia los credenciales
    */
    void setMqttCredentials()
    {
        esp_tls_set_global_ca_store(DSTroot_CA, sizeof(DSTroot_CA));
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
                setMqttCredentials();

                // Inicializa el MQTT despues de conectarse
                initMqtt();

                // se suscribe a un topico
                subscribeToTopic(topicSubscribed);
                subscribeToTopic("deviceSync");     
                return true;
            }
        }
        else
        {
            mqttClient.poll();
            return true;
        }
    }
    bool sendLinkMessage(String topic_)
    {
        if (!sync)
        {
            
            if (millis() > (lmill + 10000))
            {
        String msg = "{\n   \"gatewayMac\":\"SXV16431C\",\n   \"device\":{\n      \"deviceEui\":\"64:47:1d:a3:e1:71:99:13\",\n      \"name\":\"mqttDev\",\n      \"latitude\":12,\n      \"longitude\":76\n   },\n   \"sensors\":[]\n}";

#ifdef DEBUG
                Serial.println("sendLinkMessage");
                Serial.print(msg);
                Serial.println("SYNC");
#endif
                lmill = millis();
                sendMqttMessage(msg, topic_);
            }
            return false;
        }
        mqttClient.unsubscribe("deviceSync");
        return true;
    }


    void sendMqttMessage(String str, String topic_)
    {
#ifdef DEBUG
    Serial.println("sendMqttMessage");
       
#endif
        mqttClient.poll();
        mqttClient.beginMessage(topic_);
        mqttClient.print(str);
        mqttClient.endMessage();
    }
    /**
     * sendData() Envia los datos a la plataforma
     * @param arrayData -> Array de bytes con los datos a enviar
     */
    void sendData(byte *arrayData, uint8_t size)
    {
        Sensor arraySensors[size];
        for (int i = 0; i < size; i++)
        {

            Serial.println();
            String type = arraySensors[i].checkSensorType(arrayData[i + 8]);
            String unit = arraySensors[i].checkSensorUnit(arrayData[i + 16]);
            arraySensors[i] = Sensor(arrayData[i], type, unit, "ambientalDevice" + (String(i + 1)));
            Serial.print("Sensor " + String(i + 1) + ":");
            Serial.print(String(arraySensors[i].value) + " ");
            Serial.print(arraySensors[i].type + " ");
            Serial.println(arraySensors[i].unit);
        }

        Serial.println(" ");
        Serial.println(" ------------------------------------ ");
        String topicSend = "measure/send";

        mqttClient.poll();

        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis >= interval)
        {
            // save the last time a message was sent
            previousMillis = currentMillis;

            Serial.print("Sending message to topic: ");
            Serial.println(topicSend);
            for (int i = 0; i < size; i++)
            {

                // send message, the Print interface can be used to set the message contents
                mqttClient.beginMessage(topicSend);
                mqttClient.print("{\"deviceEui\":152,\"value\":");
                mqttClient.print((String)arraySensors[i].value);
                mqttClient.print(",\"name\":\"ambientalDevice" + String(i) + "\"");
                mqttClient.print(", \"unit\":\"");
                mqttClient.print((String)arraySensors[i].unit);
                mqttClient.print("\", \"type\":\"");
                mqttClient.print((String)arraySensors[i].type);
                mqttClient.println("\"}");
                mqttClient.endMessage();
            }
            Serial.println("... Message sended");
            Serial.println(" ");
        }
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
