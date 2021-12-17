
#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include "Publisher.h"
#include <Arduino.h>

class Sensor
{
public:
    uint32_t value = 0;
    String type = "";
    String unit = "";

    Sensor()
    {
    }

    Sensor(uint32_t _value, String _type, String _unit)
    {
        (*this).value = _value;
        (*this).type = _type;
        (*this).unit = _unit;
    }

    static String checkSensorType(byte type)
    {
        switch (type)
        {
        case 0x17:
            return "HCO";
            /* code */
            break;
        case 0x18:
            return "VOC";
            /* code */
            break;
        case 0x19:
            return "CO";
            /* code */
            break;
        case 0x1A:
            return "Cl2";
            /* code */
            break;
        case 0x1B:
            return "H2";
            /* code */
            break;
        case 0x1C:
            return "H2S";
            /* code */
            break;
        case 0x1D:
            return "HCL";
            /* code */
            break;
        case 0x1E:
            return "HCN";
            /* code */
            break;
        case 0x1F:
            return "HF";
            /* code */
            break;
        case 0x20:
            return "NH3";
            /* code */
            break;
        case 0x21:
            return "NO2";
            /* code */
            break;
        case 0x22:
            return "O2";
            /* code */
            break;
        case 0x23:
            return "O3";
            /* code */
            break;
        case 0x24:
            return "SO2";
            /* code */
            break;
        default:
            return "";
            break;
        }
    }
    static String checkSensorUnit(byte unit)
    {
        switch (unit)
        {
        case 0x02:
            return "ppm";
            break;
        case 0x04:
            return "ppb";
            break;
        case 0x08:
            return "%";
            break;

        default:
            return "";
            break;
        }
    }
};

#endif