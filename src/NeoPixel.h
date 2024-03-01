//
// Created by backo on 29/2/2024.
//

#ifndef CASA_DOMOTICA_NEOPIXEL_H
#define CASA_DOMOTICA_NEOPIXEL_H
#include <FastLED.h>
#define NEOPIXEL_PIN 25
#define NEOPIXEL_N_LEDS 8

class NeoPixel {
public:
    void begin();

    CRGB list[NEOPIXEL_N_LEDS];

    void refresh();
};


#endif //CASA_DOMOTICA_NEOPIXEL_H
