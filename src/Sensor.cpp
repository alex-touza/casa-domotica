//
// Created by backo on 4/3/2024.
//

#include "Sensor.h"
#include "Arduino.h"

Sensor::Sensor(CRGB* _led, Range _range) : led(_led), range(_range), value(0) {}

bool Sensor::process(double _value, CRGB::HTMLColorCode colors[]) {
    double prev = this->value;

    this->value = _value;

    // if (abs(this->value - prev) < 1e-9)
    //     return false;

    int level = this->range.getLevel(this->value);

    *this->led = colors[level];

    return true;
}

DHT Sensor::initDHT(unsigned char _pin) {
    return {_pin, DHT11};
}

