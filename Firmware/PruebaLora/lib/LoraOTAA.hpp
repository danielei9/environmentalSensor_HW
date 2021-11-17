/* ----------------------------------------------------------------
 *   AUTHOR:        Daniel Burruchaga Sola 
 *   FILE:           PruebaLora.cpp
 *   DATE:           2/11/2021
 *   STATE:          DONE
 *  ---------------------------------------------------------------- */

#include <../lib/Publisher.h>
#include <Arduino.h>
#include <../lib/IBM/src/lmic.h>
#include <../lib/IBM/src/hal/hal.h>
#define PORT_PING 2
#define PORT_DATA 1
#define PORT_INFO 3

#ifdef APPEUI_DEF
#else
 #define APPEUI_DEF                                     \
    {                                                  \
        0x64, 0x47, 0x1d, 0xa3, 0xe1, 0x71, 0x99, 0x13 \
    }
#endif

#ifdef DEVEUI_DEF
#else
#define DEVEUI_DEF                                     \
    {                                                  \
        0x64, 0x47, 0x1d, 0xa3, 0xe1, 0x71, 0x99, 0x13 \
    }
#endif

#ifdef APPKEY_DEF
#else
#define APPKEY_DEF                                                                                     \
    {                                                                                                  \
        0xd6, 0x37, 0xf7, 0x50, 0xc3, 0xa7, 0xc2, 0x25, 0x21, 0xdc, 0x53, 0x27, 0x19, 0xaa, 0x6c, 0x53 \
    }
#endif

//--------------------------------------------------------//
//---------------------LORA UTILIES--------------------------//
static osjob_t sendjob;
static u1_t APPEUI[8] = APPEUI_DEF;
void os_getArtEui(u1_t *buf) { memcpy(buf, APPEUI, 8); }
static const u1_t PROGMEM DEVEUI[8] = DEVEUI_DEF;
void os_getDevEui(u1_t *buf) { memcpy_P(buf, DEVEUI, 8); }
static u1_t APPKEY[16] = APPKEY_DEF;
void os_getDevKey(u1_t *buf) { memcpy(buf, APPKEY, 16); }
// Pinout to lora
const lmic_pinmap lmic_pins = {
    .nss = 18,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 14,
    .dio = {26, 33, LMIC_UNUSED_PIN},
};
bool txComplete;