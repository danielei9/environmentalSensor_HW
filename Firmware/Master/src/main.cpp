#include <Arduino.h>
#include <Publisher.h>
#include <Protocol4G.h>

Protocol4G protocol4G; // constructor normal
// Publisher *publisher = new Protocol4G(); // forma 1 de definir

Publisher *publisher = &protocol4G; // forma 2 mediante direccion

// Publisher *const publishers[2] = {&protocol4G, &LoraOTA}; // forma 3 array

uint8_t arrayData[52]; // array Data

void setup()
{

  // constructor 4G
  protocol4G.initPublisher("orangeworld", "orange", "orange", "");
  publisher->initPublisher();

  // se conecta a la red
  publisher->join();

  arrayData[0] = 2;
}

void loop()
{
  mqttClient.poll();
  delay(5000);
  publisher->sendData(arrayData);
}
