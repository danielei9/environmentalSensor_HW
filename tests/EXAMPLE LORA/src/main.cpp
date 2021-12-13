// #include <Arduino.h>
// bool joined =false;
// const unsigned TX_INTERVAL = 30;

// #include <lora.hpp>
// static osjob_t sendjob;
// void sendData(osjob_t *j, uint8_t *data, unsigned int port);
// #define APPEUI_DEF                                     \
//     {                                                  \
//         0x64, 0x47, 0x1d, 0xa3, 0xe1, 0x71, 0x99, 0x13 \
//     }
// #define DEVEUI_DEF                                     \
//     {                                                  \
//         0x64, 0x47, 0x1d, 0xa3, 0xe1, 0x71, 0x99, 0x13 \
//     }
// #define APPKEY_DEF                                                                                     \
//     {                                                                                                  \
//         0xd6, 0x37, 0xf7, 0x50, 0xc3, 0xa7, 0xc2, 0x25, 0x21, 0xdc, 0x53, 0x27, 0x19, 0xaa, 0x6c, 0x53 \
//     }
// uint8_t appEui[] = APPEUI_DEF;
// uint8_t appKey[] = APPKEY_DEF;

// static uint8_t mydata[] ="fIRSTSEND";

// lmic_txmessage_cb_t sendComplete;

// // global flag for test mode.
// bool g_fTestMode = false;
// void do_send(osjob_t* j);
// void sendComplete(
//         void *pUserData,
//         int fSuccess
// ) {
//     osjob_t * const j = (osjob_t *) pUserData;

//     if (! fSuccess)
//         Serial.println(F("sendComplete: uplink failed"));

//     if (! g_fTestMode) {
//             // Schedule next transmission
//             os_setTimedCallback(j, os_getTime()+sec2osticks(TX_INTERVAL), do_send);
//     }
// }
// void do_send(osjob_t* j){
//     // Check if there is not a current TX/RX job running
//     if (LMIC.opmode & OP_TXRXPEND) {
//         Serial.println(F("OP_TXRXPEND, not sending"));
//         sendComplete(j, 0);
//     } else if (g_fTestMode) {
//         Serial.println(F("test mode, not sending"));
//     } else {
//         // Prepare upstream data transmission at the next possible time.
//         if (LMIC_sendWithCallback(1, mydata, sizeof(mydata), 0, sendComplete, j) == 0) {
//             Serial.println(F("Packet queued"));
//         } else {
//             Serial.println(F("Packet queue failure; sleeping"));
//             sendComplete(j, 0);
//         }
//     }
// }

// void setup()
// {

//     Serial.begin(115200);
//   // lora_stack_init(false, 12);
//     initLora();
// }
// bool k = true;
// uint8_t data[] = {0x06, 0x06, 0x06};
//         uint8_t firstData[10] = "FirstSend";

// void loop()
// {
//     os_runloop_once(); // execute lmic scheduled jobs and events
//   /*  if (k)
//     {
//         k = false;
//         sendData(&sendjob, firstData, 3);
//     }*/
// }