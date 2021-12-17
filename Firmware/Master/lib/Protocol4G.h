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
unsigned long previousMillis = 0;

class Sensor
{
public:
    uint32_t value = 0;
    String type = "";
    String unit = "";

    Sensor()
    {
    }

    Sensor(uint32_t _value, String _type, String _unit)
    {
        (*this).value = _value;
        (*this).type = _type;
        (*this).unit = _unit;
    }
};

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
        if (payload == "ON")
        {
            Serial.println("Encender Dispositivo");
        }
        else if (payload == "OFF")
        {
            Serial.println("Apagar Dispositivo");
        }
        else if ((payload == "UPDATE") and (topic == "update"))
        {
            Serial.println("UPDATE");
            OTAUpd.updateFromServer();
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

    String checkSensorType(byte type)
    {
        switch (type)
        {
        case 0x17:
            return "HCO";
            /* code */
            break;
        case 0x18:
            return "VOC";
            /* code */
            break;
        case 0x19:
            return "CO";
            /* code */
            break;
        case 0x1A:
            return "Cl2";
            /* code */
            break;
        case 0x1B:
            return "H2";
            /* code */
            break;
        case 0x1C:
            return "H2S";
            /* code */
            break;
        case 0x1D:
            return "HCL";
            /* code */
            break;
        case 0x1E:
            return "HCN";
            /* code */
            break;
        case 0x1F:
            return "HF";
            /* code */
            break;
        case 0x20:
            return "NH3";
            /* code */
            break;
        case 0x21:
            return "NO2";
            /* code */
            break;
        case 0x22:
            return "O2";
            /* code */
            break;
        case 0x23:
            return "O3";
            /* code */
            break;
        case 0x24:
            return "SO2";
            /* code */
            break;
        default:
            return "";
            break;
        }
    }
    String checkSensorUnit(byte unit)
    {
        switch (unit)
        {
        case 0x02:
            return "ppm";
            break;
        case 0x04:
            return "ppb";
            break;
        case 0x08:
            return "%";
            break;

        default:
            return "";
            break;
        }
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

                return true;
            }
        }
        else
        {
            mqttClient.poll();
            return true;
        }
    }

    /**
     * sendData() Envia los datos a la plataforma
     * @param arrayData -> Array de bytes con los datos a enviar
     */
    void sendData(byte *arrayData)
    {
        Sensor arraySensors[5];
        for (int i = 0; i < 5; i++)
        {
            Serial.println();
            String type = checkSensorType(arrayData[i + 8]);
            String unit = checkSensorUnit(arrayData[i + 16]);
            arraySensors[i] = Sensor(arrayData[i], type, unit);
            Serial.print(arraySensors[i].type);
            Serial.println(arraySensors[i].unit);
        }
        // // delay(1000);

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
            mqttClient.print("{\"deviceEui\":1,\"value\": ");
            mqttClient.print((String)arrayData[0]);
            mqttClient.println(",\"type\": \"Co2\", \"unit\": \"ppm\"}");
            mqttClient.endMessage();

            mqttClient.beginMessage(topicSend);
            mqttClient.print("{\"deviceEui\":1,\"value\": ");
            mqttClient.print((String)arrayData[1]);
            mqttClient.println(",\"type\": \"HSO\", \"unit\": \"ppm\"}");
            mqttClient.endMessage();

            mqttClient.beginMessage(topicSend);
            mqttClient.print("{\"deviceEui\":1,\"value\": ");
            mqttClient.print((String)arrayData[2]);
            mqttClient.println(",\"type\": \"O3\", \"unit\": \"ppm\"}");
            mqttClient.endMessage();

            mqttClient.beginMessage(topicSend);
            mqttClient.print("{\"deviceEui\":1,\"value\": ");
            mqttClient.print((String)arrayData[3]);
            mqttClient.println(",\"type\": \"CO\", \"unit\": \"pmm\"}");
            mqttClient.endMessage();

            mqttClient.beginMessage(topicSend);
            mqttClient.print("{\"deviceEui\":1,\"value\": ");
            mqttClient.print((String)arrayData[4]);
            mqttClient.println(",\"type\": \"H2\", \"unit\": \"ppm\"}");
            mqttClient.endMessage();

            mqttClient.beginMessage(topicSend);
            mqttClient.print("{\"deviceEui\":1,\"value\": ");
            mqttClient.print((String)arrayData[5]);
            mqttClient.println(",\"type\": \"Temperature\", \"unit\": \"Cº\"}");
            mqttClient.endMessage();

            mqttClient.beginMessage(topicSend);
            mqttClient.print("{\"deviceEui\":1,\"value\": ");
            mqttClient.print((String)arrayData[6]);
            mqttClient.println(",\"type\": \"Epsilon\", \"unit\": \"Epsilon\"}");
            mqttClient.endMessage();

            mqttClient.beginMessage(topicSend);
            mqttClient.print("{\"deviceEui\":1,\"value\": ");
            mqttClient.print((String)arrayData[7]);
            mqttClient.println(",\"type\": \"Soil\", \"unit\": \"Sº\"}");
            mqttClient.endMessage();

            Serial.println(" ");
            Serial.println(" ");
        }
    }

    void vinculateDevice()
    {
        String topicSend = "gesinen/divceSync";

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
            mqttClient.print("{\"gatewayMac\":\"24:232:23:232:23\",\"device\":{\"deviceEui\":\"decive25\",\"latitude\":\"20.0\",\"longitude\":\"30.0\"},");
            mqttClient.print("\"sensors\":[{");
            // mqttClient.print((String)arrayData[0]);
            mqttClient.println(",\"type\": \"Co2\", \"unit\": \"ppm\"}");
            mqttClient.endMessage();
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
