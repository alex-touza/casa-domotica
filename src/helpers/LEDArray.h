//
// Created by backo on 18/3/2024.
//

#ifndef CASA_DOMOTICA_LEDARRAY_H
#define CASA_DOMOTICA_LEDARRAY_H

#include "FastLED.h"

class LEDArray {
private:
    const int ledsSize;
    CRGB** leds;
public:
    LEDArray(CRGB** _leds, int _ledsSize);

    void setColorAll(CRGB color);
};


#endif //CASA_DOMOTICA_LEDARRAY_H
