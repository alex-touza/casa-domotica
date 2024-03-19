//
// Created by backo on 18/3/2024.
//

#include "LEDArray.h"

LEDArray::LEDArray(CRGB** _leds, int _ledsSize) : leds(_leds), ledsSize(_ledsSize) {

}

void LEDArray::setColorAll(CRGB color) {
    for (int i = 0; i < this->ledsSize; ++i) {
        *this->leds[i] = color;
    }
}
