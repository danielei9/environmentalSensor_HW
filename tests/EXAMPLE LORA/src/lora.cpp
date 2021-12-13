// #include <lora.hpp>
// #include <Ticker.h>

// #define CFG_sx1276_radio 1 // HPD13A LoRa SoC
// // Pins for LORA chip SPI interface, reset line and interrupt lines
// #define LORA_SCK (18)
// #define LORA_CS (5)
// #define LORA_MISO (19)
// #define LORA_MOSI (23)
// #define LORA_RST (14) // old 15
// #define LORA_IRQ (2)  // old 27
// #define LORA_IO1 (32) // old 33
// #define LORA_IO2 NOT_A_PIN

// osjob_t sendjob;
// QueueHandle_t LoraSendQueue;
// QueueHandle_t LoraReceiveQueue;
// QueueHandle_t blinkqueue;
// unsigned long lastMessage;
// hal_failure_handler_t handle_failure;

// int selectedSF = LORA_DEFAULT_SF;
// bool txComplete;

// TaskHandle_t lmicTask = NULL, lorasendTask = NULL;
// //--------------------------------------------------------//
// // data:bytes[], port:R ->  sendData
// // data to send
// void sendData(osjob_t *j, uint8_t *data, unsigned int port)
// {
//   Serial.print(os_getTime());
//   Serial.print(": ");
//   // Check if there is not a current TX/RX job running
//   if (LMIC.opmode & OP_TXRXPEND)
//   {
//     Serial.println(F("OP_TXRXPEND, not sending"));
//   }
//   else
//   {
//     if (txComplete)
//     {
//       Serial.print("Sending... ");
//       // Prepare upstream data transmission at the next possible time.
//       LMIC_setTxData2(port, data, sizeof(data) - 1, 0);
//       Serial.println(F("Packet queued"));
//       txComplete = false;
//     }
//   }
//   // Next TX is scheduled after TX_COMPLETE event.
// }
// void SendPayload(uint8_t port, sendprio_t prio, uint8_t *buff, uint8_t size, confirmed_t confirmed)
// {
//   lastMessage = millis();
//   MessageBuffer_t SendBuffer; // contains MessageSize, MessagePort, Message[]
//   SendBuffer.MessageSize = size;
//   SendBuffer.MessagePort = port;
//   SendBuffer.MessageConfirmed = confirmed;
//   memcpy(SendBuffer.Message, buff, size);
//   lora_enqueuedata(&SendBuffer, prio);
// } // SendPayload

// bool LoraQueueEmpty()
// {
//   int messagesWaiting = uxQueueMessagesWaiting(LoraSendQueue);
//   return messagesWaiting == 0;
// }

// bool LoraReceiveQueueEmpty()
// {
//   int messagesWaiting = uxQueueMessagesWaiting(LoraReceiveQueue);
//   return messagesWaiting == 0;
// }

// void LoraQueueClear()
// {
//   lora_queuereset();
// }

// class MyHalConfig_t : public Arduino_LMIC::HalConfiguration_t
// {

// public:
//   MyHalConfig_t(){};
//   virtual void begin(void) override
//   {
//     SPI.begin(LORA_SCK, LORA_MISO, LORA_MOSI, LORA_CS);
//   }
// };

// MyHalConfig_t myHalConfig{};

// // LMIC pin mapping

// const lmic_pinmap lmic_pins = {
//     .nss = LORA_CS,
//     .rxtx = LMIC_UNUSED_PIN,
//     .rst = LORA_RST == NOT_A_PIN ? LMIC_UNUSED_PIN : LORA_RST,
//     .dio = {LORA_IRQ, LORA_IO1,
//             LORA_IO2 == NOT_A_PIN ? LMIC_UNUSED_PIN : LORA_IO2},
//     // optional: set polarity of rxtx pin.
//     .rxtx_rx_active = 0,
//     // optional: set RSSI cal for listen-before-talk
//     // this value is in dB, and is added to RSSI
//     // measured prior to decision.
//     // Must include noise guardband! Ignored in US,
//     // EU, IN, other markets where LBT is not required.
//     .rssi_cal = 0,
//     // optional: override LMIC_SPI_FREQ if non-zero
//     .spi_freq = 250000,
//     .pConfig = &myHalConfig};

// // LMIC callback functions
// static const u1_t PROGMEM DEVEUI[8] = DEVEUI_DEF;

// void os_getDevKey(u1_t *buf) { memcpy(buf, appKey, 16); }

// void os_getArtEui(u1_t *buf)
// {
//   memcpy(buf, appEui, 8);
// }

// void os_getDevEui(u1_t *buf)
// {
//   memcpy(buf, DEVEUI, 8); // get fixed DEVEUI from loraconf.h
// }

// void onEvent(ev_t ev)
// {
//   char buff[24] = "";
//   switch (ev)
//   {

//   case EV_SCAN_TIMEOUT:
//     strcpy_P(buff, PSTR("SCAN TIMEOUT"));
//     break;

//   case EV_BEACON_FOUND:
//     strcpy_P(buff, PSTR("BEACON FOUND"));
//     break;

//   case EV_BEACON_MISSED:
//     strcpy_P(buff, PSTR("BEACON MISSED"));
//     break;

//   case EV_BEACON_TRACKED:
//     strcpy_P(buff, PSTR("BEACON TRACKED"));
//     break;

//   case EV_JOINING:
//     strcpy_P(buff, PSTR("JOINING"));
//     break;

//   case EV_JOINED:
//     strcpy_P(buff, PSTR("JOINED"));
//     // set data rate adaptation according to saved setting
//    // LMIC_setAdrMode(LORA_ADR);
//     // set cyclic lmic link check to off if no ADR because is not supported by
//     // ttn (but enabled by lmic after join)
//    // LMIC_setLinkCheckMode(LORA_ADR);
//    // // Set data rate and transmit power (note: txpower seems to be ignored by
//     // the library)
//     switch_lora(LORA_DEFAULT_SF, 14);

//     // show effective LoRa parameters after join
//     Serial.printf("DEVaddr=%08X\n", LMIC.devaddr);
//     break;

//   case EV_RFU1:
//     strcpy_P(buff, PSTR("RFU1"));
//     break;

//   case EV_JOIN_FAILED:
//     strcpy_P(buff, PSTR("JOIN FAILED"));
//     break;

//   case EV_REJOIN_FAILED:
//     strcpy_P(buff, PSTR("REJOIN FAILED"));
//     break;

//   case EV_TXCOMPLETE:
//             txComplete = true;

//     strcpy_P(buff, (LMIC.txrxFlags & TXRX_ACK) ? PSTR("RECEIVED ACK")
//                                                : PSTR("TX COMPLETE"));

//     if (LMIC.dataLen)
//     { // did we receive payload data -> display info
//       Serial.printf("Received %d bytes of payload, RSSI %d SNR %d\n",
//                     LMIC.dataLen, LMIC.rssi, LMIC.snr / 4);

//       if (LMIC.txrxFlags & TXRX_PORT)
//       { // FPort -> use to switch
//         MessageBuffer_t message;
//         message.MessageSize = LMIC.dataLen;
//         memcpy(message.Message, LMIC.frame + LMIC.dataBeg, LMIC.dataLen);
//         lora_enqueuereceiveddata(&message);
//       }
//     }
//     break;

//   case EV_LOST_TSYNC:
//     strcpy_P(buff, PSTR("LOST TSYNC"));
//     break;

//   case EV_RESET:
//     strcpy_P(buff, PSTR("RESET"));
//     break;

//   case EV_RXCOMPLETE:
//     // data received in ping slot
//     strcpy_P(buff, PSTR("RX COMPLETE"));
//     break;

//   case EV_LINK_DEAD:
//     strcpy_P(buff, PSTR("LINK DEAD"));
//     break;

//   case EV_LINK_ALIVE:
//     strcpy_P(buff, PSTR("LINK_ALIVE"));
//     break;

//   case EV_SCAN_FOUND:
//     strcpy_P(buff, PSTR("SCAN FOUND"));
//     break;

//   case EV_TXSTART:
//     if (!(LMIC.opmode & OP_JOINING))
//       strcpy_P(buff, PSTR("TX START"));
//     break;

//   case EV_TXCANCELED:
//     strcpy_P(buff, PSTR("TX CANCELLED"));
//     break;

//   case EV_RXSTART:
//     strcpy_P(buff, PSTR("RX START"));
//     break;

//   case EV_JOIN_TXCOMPLETE:
//     strcpy_P(buff, PSTR("JOIN WAIT"));
//     break;

//   default:
//     sprintf_P(buff, PSTR("LMIC EV %d"), ev);
//     break;
//   }

//   // Log & Display if asked
//   if (*buff)
//   {
//     Serial.printf("%s\n", buff);
//   }
// }

// void switch_lora(uint8_t sf, uint8_t tx)
// {
//   if (tx > 20)
//     return;
//   switch (sf)
//   {
//   case 7:
//     LMIC_setDrTxpow(DR_SF7, tx);
//     break;
//   case 8:
//     LMIC_setDrTxpow(DR_SF8, tx);
//     break;
//   case 9:
//     LMIC_setDrTxpow(DR_SF9, tx);
//     break;
//   case 10:
//     LMIC_setDrTxpow(DR_SF10, tx);
//     break;
//   case 11:
//     LMIC_setDrTxpow(DR_SF11, tx);
//     break;
//   case 12:
//     LMIC_setDrTxpow(DR_SF12, tx);
//     break;
//   default:
//     break;
//   }
// }

// int getWaitTime()
// {
//   switch (LMIC.datarate)
//   {
//   case 0:
//     return 360;
//   case 1:
//     return 300;
//   case 2:
//     return 240;
//   case 3:
//     return 180;
//   case 4:
//     return 120;
//   case 5:
//     return 60;
//   default:
//     return 60;
//   }
// }

// // LMIC send task
// void lora_send(void *pvParameters)
// {
//   configASSERT(((uint32_t)pvParameters) == 1); // FreeRTOS check

//   MessageBuffer_t SendBuffer;
//   uint16_t waits = 0;
//   while (1)
//   {
//     // postpone until we are joined if we are not
//     while (!LMIC.devaddr)
//     {
//       waits = 0;
//       vTaskDelay(pdMS_TO_TICKS(500));
//     }

//     if (LMIC.opmode & OP_TXRXPEND)
//     {
//       Serial.println("LMIC busy, waiting...");
//       waits += 1;
//       if (waits >= getWaitTime())
//       {
//         handle_failure("forced", 271);
//       }
//       vTaskDelay(pdMS_TO_TICKS(1000));
//       continue;
//     }
//     // fetch next or wait for payload to send from queue
//     else if (xQueueReceive(LoraSendQueue, &SendBuffer, portMAX_DELAY) != pdTRUE)
//     {
//       waits = 0;
//       Serial.println("Premature return from xQueueReceive() with no data!");
//       continue;
//     }
//     // attempt to transmit payload
//     else
//     {
//       waits = 0;
//       switch (LMIC_setTxData2_strict(SendBuffer.MessagePort, SendBuffer.Message,
//                                      SendBuffer.MessageSize, SendBuffer.MessageConfirmed))
//       {

//       case LMIC_ERROR_SUCCESS:
//         Serial.printf("%d byte(s) sent to LORA \n", SendBuffer.MessageSize);
//         char string_message[256];
//         for (int i = 0; i < SendBuffer.MessageSize; i++)
//         {
//           sprintf(string_message + 3 * i, "%02x ", SendBuffer.Message[i]);
//         }
//         Serial.printf("sending lora message %s\n", string_message);
//         Serial.printf("Queue: %d\n", uxQueueMessagesWaiting(LoraSendQueue));
//         break;
//       case LMIC_ERROR_TX_BUSY:   // LMIC already has a tx message pending
//       case LMIC_ERROR_TX_FAILED: // message was not sent
//         // ESP_LOGD(TAG, "LMIC busy, message re-enqueued"); // very noisy
//         vTaskDelay(pdMS_TO_TICKS(1000 + random(500))); // wait a while
//         lora_enqueuedata(&SendBuffer, prio_high);      // re-enqueue the undelivered message
//         break;
//       case LMIC_ERROR_TX_TOO_LARGE:    // message size exceeds LMIC buffer size
//       case LMIC_ERROR_TX_NOT_FEASIBLE: // message too large for current
//                                        // datarate
//         Serial.println("Message too large to send, message not sent and deleted");
//         // we need some kind of error handling here -> to be done
//         break;
//       default: // other LMIC return code
//         Serial.println("LMIC error, message not sent and deleted");
//       } // switch
//     }
//     delay(2); // yield to CPU
//   }
// }

// void handle_failure(const char *pMessage, uint16_t line)
// {
//   delay(30000);
//   Serial.println("Saving DR: " + String(LMIC.datarate));
//   EEPROM.put(1000, (int)1);
//   EEPROM.put(1000 + sizeof(int), LMIC.datarate);
//   EEPROM.commit();
//   ESP.restart();
// }

// // LMIC lorawan stack task
// void lmictask(void *pvParameters)
// {
//   configASSERT(((uint32_t)pvParameters) == 1);

//   // setup LMIC stack
//   hal_set_failure_handler(handle_failure);
//   os_init(); // initialize lmic run-time environment on core 1
//   while (1)
//   {
//     LMIC_reset(); // initialize lmic MAC
//     LMIC_setLinkCheckMode(0);
//     // This tells LMIC to make the receive windows bigger, in case your clock is
//     // faster or slower. This causes the transceiver to be earlier switched on,
//     // so consuming more power. You may sharpen (reduce) CLOCK_ERROR_PERCENTAGE
//     // in src/lmic_config.h if you are limited on battery.
//     LMIC_setClockError(MAX_CLOCK_ERROR * CLOCK_ERROR_PROCENTAGE / 100);
//     // Set the data rate to Spreading Factor 7.  This is the fastest supported
//     // rate for 125 kHz channels, and it minimizes air time and battery power.
//     // Set the transmission power to 14 dBi (25 mW).

//     LMIC_setDrTxpow(selectedSF, 14);

//     while (1)
//     {
//       os_runloop_once(); // execute lmic scheduled jobs and events
//       delay(2);          // yield to CPU
//     }
//   }
// } // lmictask

// esp_err_t lora_stack_init(bool reinit, int prevSF)
// {
//   if (reinit)
//   {
//     selectedSF = prevSF;
//   }
//   assert(SEND_QUEUE_SIZE);
//   LoraSendQueue = xQueueCreate(SEND_QUEUE_SIZE, sizeof(MessageBuffer_t));
//   if (LoraSendQueue == 0)
//   {
//     Serial.printf("Could not create LORA send queue. Aborting.\n");
//     return ESP_FAIL;
//   }
//   Serial.printf("LORA send queue created, size %d Bytes\n",
//                 SEND_QUEUE_SIZE * PAYLOAD_BUFFER_SIZE);

//   assert(RECEIVE_QUEUE_SIZE);
//   LoraReceiveQueue = xQueueCreate(RECEIVE_QUEUE_SIZE, sizeof(MessageBuffer_t));
//   if (LoraSendQueue == 0)
//   {
//     Serial.printf("Could not create LORA receive queue. Aborting.\n");
//     return ESP_FAIL;
//   }
//   Serial.printf("LORA receive queue created, size %d Bytes\n",
//                 RECEIVE_QUEUE_SIZE * PAYLOAD_BUFFER_SIZE);

//   lastMessage = 0;
//   // start lorawan stack
//   Serial.println("Starting LMIC...");
//   xTaskCreatePinnedToCore(lmictask,   // task function
//                           "lmictask", // name of task
//                           4096,       // stack size of task
//                           (void *)1,  // parameter of the task
//                           2,          // priority of the task
//                           &lmicTask,  // task handle
//                           1);         // CPU core

//   if (!LMIC_startJoining())
//   { // start joining
//     Serial.printf("Already joined\n");
//   }

//   // start lmic send task
//   xTaskCreatePinnedToCore(lora_send,      // task function
//                           "lorasendtask", // name of task
//                           3072,           // stack size of task
//                           (void *)1,      // parameter of the task
//                           1,              // priority of the task
//                           &lorasendTask,  // task handle
//                           1);             // CPU core

//   return ESP_OK; // continue main program
// }

// void lora_enqueuedata(MessageBuffer_t *message, sendprio_t prio)
// {
//   // enqueue message in LORA send queue
//   BaseType_t ret;
//   MessageBuffer_t DummyBuffer;
//   switch (prio)
//   {
//   case prio_high:
//     // clear space in queue if full, then fallthrough to normal
//     if (uxQueueSpacesAvailable(LoraSendQueue) == 0)
//       xQueueReceive(LoraSendQueue, &DummyBuffer, (TickType_t)0);
//   case prio_normal:
//     ret = xQueueSendToFront(LoraSendQueue, (void *)message, (TickType_t)0);
//     break;
//   case prio_low:
//   default:
//     ret = xQueueSendToBack(LoraSendQueue, (void *)message, (TickType_t)0);
//     break;
//   }
//   if (ret != pdTRUE)
//     Serial.printf("LORA sendqueue is full\n");
// }

// void lora_enqueuereceiveddata(MessageBuffer_t *message)
// {
//   // enqueue message in LORA send queue
//   MessageBuffer_t DummyBuffer;
//   // clear space in queue if full, then fallthrough to normal
//   if (uxQueueSpacesAvailable(LoraReceiveQueue) == 0)
//     xQueueReceive(LoraReceiveQueue, &DummyBuffer, (TickType_t)0);
//   BaseType_t ret = xQueueSendToBack(LoraReceiveQueue, (void *)message, (TickType_t)0);

//   if (ret != pdTRUE)
//     Serial.printf("LORA receive queue is full\n");
// }

// void lora_queuereset(void) { xQueueReset(LoraSendQueue); }

// void initLora()
// {
//   assert(lora_stack_init(false, selectedSF) == ESP_OK);
// }
