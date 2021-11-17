#include <Arduino.h>
#include <../lib/LoraOTAA.h>
#include <EEPROM.h>
#include <../lib/IBM/src/lmic.h>
#include <../lib/IBM/src/hal/hal.h>
/*
#define APPEUI_DEF                                     \
    {                                                  \
        0x64, 0x47, 0x1d, 0xa3, 0xe1, 0x71, 0x99, 0x13 \
    }

#define DEVEUI_DEF                                     \
    {                                                  \
        0x64, 0x47, 0x1d, 0xa3, 0xe1, 0x71, 0x99, 0x13 \
    }
    
#define APPKEY_DEF                                                                                     \
    {                                                                                                  \
        0xd6, 0x37, 0xf7, 0x50, 0xc3, 0xa7, 0xc2, 0x25, 0x21, 0xdc, 0x53, 0x27, 0x19, 0xaa, 0x6c, 0x53 \
    }
*/

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
            Lora.sendData(&sendjob,mydata,PORT_DATA, sizeof(mydata)-1 );
            mill = millis();
        }
    }
}
