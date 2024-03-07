//
// Created by backo on 29/2/2024.
//

#ifndef CASA_DOMOTICA_NEOPIXEL_H
#define CASA_DOMOTICA_NEOPIXEL_H
#include <FastLED.h>

#define CD_NEOPIXEL_PIN 25
#define CD_NEOPIXEL_N_LEDS 8

class CDNeoPixel {
public:
    static void begin();

    static CRGB list[CD_NEOPIXEL_N_LEDS];

    static void refresh();
};


#endif //CASA_DOMOTICA_NEOPIXEL_H
