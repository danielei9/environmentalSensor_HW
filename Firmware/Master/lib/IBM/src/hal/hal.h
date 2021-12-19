/*******************************************************************************
 * Copyright (c) 2015 Matthijs Kooijman
 * All rights reserved. This program and the accompanying materials
 * are made available under the terms of the Eclipse Public License v1.0
 * which accompanies this distribution, and is available at
 * http://www.eclipse.org/legal/epl-v10.html
 *
 * This the HAL to run LMIC on top of the Arduino environment.
 *******************************************************************************/
#ifndef _hal_hal_h_
#define _hal_hal_h_

#define LORA_SCK  (18)
#define LORA_CS   (5)
#define LORA_MISO (19)
#define LORA_MOSI (23)
#define LORA_RST  (14) // old 15
#define LORA_IRQ  (2) // old 27
#define LORA_IO1  NOT_A_PIN// old 33
#define LORA_IO2  NOT_A_PIN

static const int NUM_DIO = 3;

struct lmic_pinmap {
    u1_t nss;
    u1_t rxtx;
    u1_t rst;
    u1_t dio[NUM_DIO];
};

// Use this for any unused pins.
const u1_t LMIC_UNUSED_PIN = 0xff;

// Declared here, to be defined an initialized by the application
extern const lmic_pinmap lmic_pins;

#endif // _hal_hal_h_
