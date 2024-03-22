//
// Created by backo on 4/3/2024.
//

#ifndef CASA_DOMOTICA_SENSOR_H
#define CASA_DOMOTICA_SENSOR_H

#include <DHT.h>
#include <FastLED.h>
#include "helpers/Range.h"

class Sensor {
private:
    CRGB* led;

    // No és un punter perquè pugui ser passat directament
    // com a paràmetre en lloc de ser creat amb una variable
    // temporal.
    Range range;

protected:
    // Processar un valor llegit des de la funció de la
    // classe filla.
    bool process(double _value, CRGB::HTMLColorCode colors[]);

public:
    Sensor(CRGB* _led, Range _range);
    virtual void begin() = 0;
    virtual bool read() = 0;

    double value;

    // Constructor simplificat de DHT
    static DHT initDHT(unsigned char _pin);

};



#endif //CASA_DOMOTICA_SENSOR_H
