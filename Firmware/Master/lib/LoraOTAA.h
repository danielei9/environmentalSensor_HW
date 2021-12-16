#include <Arduino.h>
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
static osjob_t sendjob;

// Pin mapping
const lmic_pinmap lmic_pins = {
    .nss = 5,
    .rxtx = LMIC_UNUSED_PIN,
    .rst = 14,
    .dio = {2, 3, 4},
};

/**
     * print hex received
     * @param v index to print
     */
void printHex2(unsigned v)
{
    v &= 0xff;
    if (v < 16)
        Serial.print('0');
    Serial.print(v, HEX);
}
bool txComplete;

uint8_t recivedData[52];
#define DATA_PORT 1
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
        Serial.print("INitLORA");
        os_init();
        LMIC_reset();
        uint8_t firstData[10] = "FirstSend";
        delay(100);
        sendData(&sendjob, firstData, DATA_PORT, sizeof(firstData));
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

    /**
     * create a job to send data 
     * @param j osjob to create the transmission
     * @param data data arr pointer 
     * @param port lora port to send
     * @param size Data to send size
     */
    void sendData(osjob_t *j, uint8_t *data, unsigned int port, unsigned int size)
    {
        // Check if there is not a current TX/RX job running
        if (LMIC.opmode & OP_TXRXPEND)
        {
            Serial.println(F("OP_TXRXPEND, not sending"));
        }
        else
        {
            // Prepare upstream data transmission at the next possible time.
            LMIC_setTxData2(port, data, size - 1, 1);
            Serial.println(F("Packet queued"));
        }
        // Next TX is scheduled after TX_COMPLETE event.
    }
/**
     * create a job to send PING 
     * @param j osjob to create the transmission
     * @param data data arr pointer 
     * @param port lora port to send
     * @param size Data to send size
     * @param interval interval to send ping
     * @param previousMillis time last send
     */
    void makePing(int interval, long previousMillis,osjob_t *j, uint8_t *data, unsigned int port, unsigned int size)
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
                sendData(&sendjob, ping, DATA_PORT, sizeof(ping));
            }
        }
    }
    
/**
     * Schedule events on the OS
     * @param ev event ocurred in the os
     */
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
            /*{
              u4_t netid = 0;
              devaddr_t devaddr = 0;
              u1_t nwkKey[16];
              u1_t artKey[16];
             // LMIC_getSessionKeys(&netid, &devaddr, nwkKey, artKey);
              Serial.print("netid: ");
              Serial.println(netid, DEC);
              Serial.print("devaddr: ");
              Serial.println(devaddr, HEX);
              Serial.print("AppSKey: ");
              for (size_t i=0; i<sizeof(artKey); ++i) {
                if (i != 0)
                  Serial.print("-");
                printHex2(artKey[i]);
              }
              Serial.println("");
              Serial.print("NwkSKey: ");
              for (size_t i=0; i<sizeof(nwkKey); ++i) {
                      if (i != 0)
                              Serial.print("-");
                      printHex2(nwkKey[i]);
              }
              Serial.println();
            }*/
            // Disable link check validation (automatically enabled
            // during join, but because slow data rates change max TX
            // size, we don't use it in this example.
            LMIC_setLinkCheckMode(0);
            break;
        /*
        || This event is defined but not used in the code. No
        || point in wasting codespace on it.
        ||
        || case EV_RFU1:
        ||     Serial.println(F("EV_RFU1"));
        ||     break;
        */
        case EV_JOIN_FAILED:
            Serial.println(F("EV_JOIN_FAILED"));
            break;
        case EV_REJOIN_FAILED:
            Serial.println(F("EV_REJOIN_FAILED"));
            break;
        case EV_TXCOMPLETE:
            Serial.println(F("EV_TXCOMPLETE (includes waiting for RX windows)"));
            if (LMIC.txrxFlags & TXRX_ACK)
                Serial.println(F("Received ack"));
            if (LMIC.dataLen)
            {
                Serial.print(F("Received "));
                Serial.print(LMIC.dataLen);
                Serial.println(F(" bytes of payload"));
            }
            // Schedule next transmission
            // os_setTimedCallback(&sendjob, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
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
        /*
        || This event is defined but not used in the code. No
        || point in wasting codespace on it.
        ||
        || case EV_SCAN_FOUND:
        ||    Serial.println(F("EV_SCAN_FOUND"));
        ||    break;
        */
        case EV_TXSTART:
            Serial.println(F("EV_TXSTART"));
            break;
        case EV_TXCANCELED:
            Serial.println(F("EV_TXCANCELED"));
            break;
        case EV_RXSTART:
            /* do not print anything -- it wrecks timing */
            break;
        case EV_JOIN_TXCOMPLETE:
            Serial.println(F("EV_JOIN_TXCOMPLETE: no JoinAccept"));
            break;

        default:
            Serial.print(F("Unknown event: "));
            Serial.println((unsigned)ev);
            break;
        }
    }
};