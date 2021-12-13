#include <Arduino.h>
#include <../lib/LoraOTAA.h>
#include <EEPROM.h>
#include <../lib/IBM/src/lmic.h>
#include <../lib/IBM/src/hal/hal.h>

uint8_t mydata[50] = "FirstSend";
LoraOTAA Lora;
unsigned long mill = 0;
void onEvent(ev_t ev)
{
    Lora.onEventLora(ev);
}
bool timerTrue(unsigned long lastmillis_, int interval);

void setup()
{
    Serial.begin(9600);
    Serial.println("Starting");
    Serial.begin(9600); // Start the built-in serial port
    Lora.initPublisher();
}
void loop()
{
    Lora.once();
    if (Lora.join())
    {
        if (timerTrue(mill, 20000))
        {
            Lora.sendData(&sendjob,mydata,PORT_DATA);
            mill = millis();
        }
    }
}
