// clang-format off
// upload_speed 921600
// board esp32dev

#ifndef _IBOXLORA_H
#define _IBOXLORA_H

#include <stdint.h>

#define CFG_sx1276_radio 1 // HPD13A LoRa SoC

// Pins for LORA chip SPI interface, reset line and interrupt lines
#define LORA_SCK  (18)
#define LORA_CS   (5)
#define LORA_MISO (19)
#define LORA_MOSI (23)
#define LORA_RST  (14) // old 15
#define LORA_IRQ  (2) // old 27
#define LORA_IO1  (32) // old 33
#define LORA_IO2  NOT_A_PIN

#endif