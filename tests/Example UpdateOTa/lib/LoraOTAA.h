#include <../lib/Publisher.h>
#include <Arduino.h>
#include <../lib/IBM/src/lmic.h>
#include <../lib/IBM/src/hal/hal.h>
#include <EEPROM.h>
#include <../lib/Utils.h>

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
static u1_t APPEUI[8] = APPEUI_DEF;
void os_getArtEui(u1_t *buf) { memcpy(buf, APPEUI, 8); }
static const u1_t PROGMEM DEVEUI[8] = DEVEUI_DEF;
void os_getDevEui(u1_t *buf) { memcpy_P(buf, DEVEUI, 8); }
static u1_t APPKEY[16] = APPKEY_DEF;
void os_getDevKey(u1_t *buf) { memcpy(buf, APPKEY, 16); }

const lmic_pinmap lmic_pins = {
    .nss = 18,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 14,
    .dio = {26, 33, LMIC_UNUSED_PIN},
};
bool txComplete;

uint8_t recivedData[52];

class LoraOTAA : public Publisher
{
private:
    bool joined;
    unsigned long joinMillis;

    void once()
    {
        os_runloop_once();
    }

public:
    LoraOTAA()
    {
        txComplete = true;
        joined = false;
    }
    void initPublisher()
    {
        Serial.begin(9600);
        Serial.println("Starting");
        Serial.print("INit");
        os_init();
        LMIC_reset();
        uint8_t firstData[10] = "FirstSend";
        sendData(firstData);
    }
    bool join()
    {
        once();

        if (joined)
        {
            return true;
        }
        else
        {
            if (timerTrue(joinMillis, 2000))
            {
                Serial.println("JOINING...");
                joinMillis = millis();
                return false;
            }
        }
    }
    void sendData(uint8_t *data)
    {
        // Check if there is not a current TX/RX job running
        if (LMIC.opmode & OP_TXRXPEND)
        {
            Serial.println(F("OP_TXRXPEND, not sending"));
        }
        else
        {
            if (txComplete)
            {
                Serial.print("Sending... ");
                // Prepare upstream data transmission at the next possible time.
                LMIC_setTxData2(1, data, sizeof(data) - 1, 0);
                Serial.println(F("Packet queued"));
                txComplete = false;
            }
        }
        // Next TX is scheduled after TX_COMPLETE event.
    }

    void makePing(int interval, long previousMillis)
    {
        unsigned long currentMillis = millis();
        if (currentMillis - previousMillis > interval)
        {
            previousMillis = currentMillis;
            if (LMIC.opmode & OP_TXRXPEND)
            {
                Serial.println(F("OP_TXRXPEND, not sending"));
            }
            else
            {
                uint8_t ping[] = "PING";
                sendData(ping);
            }
        }
    }
    void onEventLora(ev_t ev)
    {
        Serial.print(os_getTime());
        Serial.print(": ");
        switch (ev)
        {
        case EV_SCAN_TIMEOUT:
            Serial.println(F("EV_SCAN_TIMEOUT"));
            break;
        case EV_BEACON_FOUND:
            Serial.println(F("EV_BEACON_FOUND"));
            break;
        case EV_BEACON_MISSED:
            Serial.println(F("EV_BEACON_MISSED"));
            break;
        case EV_BEACON_TRACKED:
            Serial.println(F("EV_BEACON_TRACKED"));
            break;
        case EV_JOINING:
            Serial.println(F("EV_JOINING"));
            break;
        case EV_JOINED:
            Serial.println(F("EV_JOINED"));
            joined = true;
            // Disable link check validation (automatically enabled
            // during join, but not supported by TTN at this time).
            LMIC_setLinkCheckMode(0);
            break;
        case EV_RFU1:
            Serial.println(F("EV_RFU1"));
            break;
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED"));
            break;
        case EV_REJOIN_FAILED:
            Serial.println(F("EV_REJOIN_FAILED"));
            break;
            break;
        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
            txComplete = true;
            if (LMIC.txrxFlags & TXRX_ACK)
                Serial.println(F("Received ack"));
            if (LMIC.dataLen)
            {
                Serial.print("$Received$");
                for (int i = 0; i < LMIC.dataLen; i++)
                {
                    Serial.print("_");
                    Serial.print(LMIC.frame[LMIC.dataBeg + i]);
                }
                Serial.println("_");
            }
            break;
        case EV_LOST_TSYNC:
            Serial.println(F("EV_LOST_TSYNC"));
            break;
        case EV_RESET:
            Serial.println(F("EV_RESET"));
            break;
        case EV_RXCOMPLETE:
            // data received in ping slot
            Serial.println(F("EV_RXCOMPLETE"));
            break;
        case EV_LINK_DEAD:
            Serial.println(F("EV_LINK_DEAD"));
            break;
        case EV_LINK_ALIVE:
            Serial.println(F("EV_LINK_ALIVE"));
            break;
        default:
            Serial.println(F("Unknown event"));
            break;
        }
    }
};