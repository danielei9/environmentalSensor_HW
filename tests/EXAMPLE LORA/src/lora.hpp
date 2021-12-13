// #ifndef LORA_H
// #define LORA_H

// #include <Arduino.h>
// #include <EEPROM.h>
// #include "iboxlora.h"
// #include <loraConfig.hpp>
// #include <lmic.h>
// #include <hal/hal.h>
// #include <SPI.h>
// #include <mutex>

// enum sendprio_t { prio_low, prio_normal, prio_high };

// enum confirmed_t { unconfirmed, confirmed};

// typedef struct {
//   bool MessageConfirmed;
//   uint8_t MessageSize;
//   uint8_t MessagePort;
//   uint8_t Message[PAYLOAD_BUFFER_SIZE];
// } MessageBuffer_t;

// extern QueueHandle_t blinkqueue;
// enum BlinkType {
//     Sent,
//     Received
// };

// extern QueueHandle_t LoraSendQueue;
// extern QueueHandle_t LoraReceiveQueue;

// extern unsigned long lastMessage;

// extern uint8_t appEui[8];
// extern uint8_t appKey[16];

// void onEvent(ev_t ev);
// void os_getDevKey(u1_t *buf);
// void os_getArtEui(u1_t *buf);
// void os_getDevEui(u1_t *buf);
// void switch_lora(uint8_t sf, uint8_t tx);
// void lora_send(void *pvParameters);
// esp_err_t lora_stack_init(bool reinit, int prevSF);
// void lora_enqueuedata(MessageBuffer_t *message, sendprio_t prio);
// void lora_enqueuereceiveddata(MessageBuffer_t *message);
// void lora_queuereset(void);
// extern void command_callback(uint8_t*, uint8_t);
// void setCallback(void (*cb)(uint8_t*, uint8_t));
// void loraLoop();
// void initLora();

// void SendPayload(uint8_t port, sendprio_t prio, uint8_t *buff, uint8_t size, confirmed_t confirmed = unconfirmed);
// bool LoraQueueEmpty();
// bool LoraReceiveQueueEmpty();
// void LoraQueueClear();

// #endif