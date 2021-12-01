// -*- mode: c++ -*-

/** --------------------------------------------------------------
 * Autor: Yeray Candel Sampedro
 * Date: 09 - 11 - 2021
 *
 * Description: Ejemplo de uso de la clase 4G
 * LOS PARAMETROS DE CONEXION DEL SERVIDOR MQTT SE HAN DE CONFIGURAR
 * EN LA CLASE 4G
 * 
 * DEFINIR TARJETA SIM A UTILIZAR
 * #define TINY_GSM_MODEM_SIM7000SSL // Modem is SIM800
 * 
 *  DEFINIR SECURE OR NOT
 *  TinyGsmClientSecure client(modem);
 * 
 * CONFIGURAR BROKER SERVER PORT MQTT Y TOPICS
 * CONFIGURAR CERTIFICADO SI SE USA SSL/TLS
 * 
 * --------------------------------------------------------------
 */

#include <Arduino.h>

#define PROTOCOL_4G
#include "../lib/Protocol4G.h"
#include "../lib/Utils.h"

uint8_t arrayData[52]; // array Data
unsigned long mill = 0;

// constructor
Protocol4G protocol4G("orangeworld", "orange", "orange");

void setup()
{
  // Init Publisher 4G
  protocol4G.initPublisher();
}
void loop()
{
  // joining to the 4G Network
  if (protocol4G.join())
  {
    if (timerTrue(mill, 10000))
    {
      // send the arrayData to MQTT

      protocol4G.sendData(arrayData);
      mill = millis();
    }
  }
}
