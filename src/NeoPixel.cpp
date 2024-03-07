//
// Created by backo on 29/2/2024.
//

#include "NeoPixel.h"


CRGB CDNeoPixel::list[CD_NEOPIXEL_N_LEDS];

void CDNeoPixel::begin() {
    FastLED.addLeds<WS2812B, CD_NEOPIXEL_PIN, GRB>(CDNeoPixel::list, CD_NEOPIXEL_N_LEDS);
    FastLED.setBrightness(80);
}

void CDNeoPixel::refresh() {
    FastLED.show();
}
