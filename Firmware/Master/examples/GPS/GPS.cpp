#include <Arduino.h>
#include "GPS.hpp"

// definimos el GPS
GPS gps;

void setup()
{
    // Se inicializa el GPS
    gps.init();
}
void loop()
{
    // se hace un test en el loop para obtener las cordenadas constanatemente
    gps.testLoop();
}