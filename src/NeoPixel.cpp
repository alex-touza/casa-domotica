//
// Created by backo on 29/2/2024.
//

#include "NeoPixel.h"

void NeoPixel::begin() {
    FastLED.addLeds<WS2812B, NEOPIXEL_PIN, GRB>(this->list, NEOPIXEL_N_LEDS);
    FastLED.setBrightness(80);
}

void NeoPixel::refresh() {
    FastLED.show();
}


