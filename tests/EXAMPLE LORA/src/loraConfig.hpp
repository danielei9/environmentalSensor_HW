#ifndef LORA_CONFIG_H
#define LORA_CONFIG_H
#include <Arduino.h>

#include "../lib/MCCI LoRaWAN LMIC library/src/lmic.h"
#include "../lib/MCCI LoRaWAN LMIC library/src/hal/hal.h" 
#define PAYLOAD_BUFFER_SIZE 128
#define SEND_QUEUE_SIZE 500
#define RECEIVE_QUEUE_SIZE 25
#define LORA_ADR true
#define LORA_DEFAULT_SF 12
#define RCMDPORT 4
#define LORA_CONFIRMED 0
#define CLOCK_ERROR_PROCENTAGE 5

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
#endif