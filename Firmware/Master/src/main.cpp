#include <Arduino.h>
#include <Publisher.h>
#include <Protocol4G.h>

Protocol4G protocol4G;
// Publisher *publisher = new Protocol4G(); // forma 1 de definir
Publisher *publisher = &protocol4G; // forma 2 mediante direccion

void setup()
{
  Serial.begin(115200);
  protocol4G.initPublisher("pito", "a", "b", "");
  publisher->initPublisher();
}

void loop()
{
  if (!publisher->join())
  {
    delay(500);
    return;
  }
  
  delay(500);
  Serial.println("aaaa");
}