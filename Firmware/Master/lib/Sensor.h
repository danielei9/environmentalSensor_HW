// -*- mode: c++ -*-

// --------------------------------------------------------------
// Autor: Yeray Candel Sampedro
// Date: 17 - 12 - 2021
//
// Description: Clase Sensor que es un objeto para controlar las
// mediciones que llegan desde el esclavo
// --------------------------------------------------------------
#ifndef SENSOR_H_INCLUDED
#define SENSOR_H_INCLUDED

#include "Publisher.h"
#include <Arduino.h>

class Sensor
{
public:
    // varuables publics
    uint32_t value = 0;
    String type = "";
    String unit = "";
    String name = "";

    // Constructor
    Sensor()
    {
    }
    /**
     * Constructor de la clase Sensor
     * @param _value valor
     * @param _type tipo de sensor
     * @param _unit unidades en las que mide el sensor
     * @param _name nombre del sensor
     */
    Sensor(uint32_t _value, String _type, String _unit, String _name)
    {
        (*this).value = _value;
        (*this).type = _type;
        (*this).unit = _unit;
        (*this).name = _name;
    }

    /**
     * Classifica el tipo de sensor 
     * @param _type tipo de sensor en bytes
     */
    static String checkSensorType(byte type)
    {
        switch (type)
        {
        case 0x17:
            return "HCO";
            break;
        case 0x18:
            return "VOC";
            break;
        case 0x19:
            return "CO";
            break;
        case 0x1A:
            return "Cl2";
            break;
        case 0x1B:
            return "H2";
            break;
        case 0x1C:
            return "H2S";
            break;
        case 0x1D:
            return "HCL";
            break;
        case 0x1E:
            return "HCN";
            break;
        case 0x1F:
            return "HF";
            break;
        case 0x20:
            return "NH3";
            break;
        case 0x21:
            return "NO2";
            break;
        case 0x22:
            return "O2";
            break;
        case 0x23:
            return "O3";
            break;
        case 0x24:
            return "SO2";
            break;
        // nuestros identificadores
        case 0x50:
            return "TEMP";
            break;
        case 0x51:
            return "NOISE";
            break;
        case 0x52:
            return "EPSILON";
            break;
        case 0x53:
            return "SOIL";
            break;
        default:
            return "";
            break;
        }
    }

    /**
     * Classifica el tipo de unidad en la que mide el sensor
     * @param _type tipo de sensor en bytes
     */
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

        // nuestros identificadores
        case 0x10:
            return "Cº";
            break;
        case 0x11:
            return "EPSI";
            break;
        case 0x12:
            return "DB";
            break;
        default:
            return "";
            break;
        }
    }
};

#endif