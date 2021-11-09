#include <Arduino.h>
#include <../lib/Publisher.h>
#include <../lib/Protocol4G.h>
#include <../lib/LoraOTAA.h>
#include <Wire.h>
#include <EEPROM.h>
#include <../lib/IBM/src/lmic.h>
#include <../lib/IBM/src/hal/hal.h>
#include <../lib/SlaveController.h>

Protocol4G protocol4G; // constructor normal
LoraOTAA Lora;
// Publisher *publisher = new Protocol4G(); // forma 1 de definir

Publisher *publisher = &protocol4G;                    // forma 2 mediante direccion
Publisher *const publishers[2] = {&protocol4G, &Lora}; // forma 3 array
#define PROTOCOL 0  // 0 = 4G, 1 = LORA, etc.

uint8_t arrayData[52]; // array Data

unsigned long mill = 0;
void onEvent(ev_t ev)
{
  Lora.onEventLora(ev);
}
bool timerTrue(unsigned long lastmillis_, int interval);

void setup()
{
  // constructor 4G
  protocol4G.initPublisher("orangeworld", "orange", "orange");
  publishers[PROTOCOL]->initPublisher();

  // se conecta a la red
  publishers[PROTOCOL]->join();

  arrayData[0] = 2;
}

void loop()
{
  mqttClient.poll();
  delay(5000);
  publishers[PROTOCOL]->sendData(arrayData);
}
