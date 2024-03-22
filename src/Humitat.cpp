//
// Created by backo on 4/3/2024.
//

#include "Humitat.h"

Humitat::Humitat(DHT* _dht, CRGB* _led) :
        dht(_dht),
        Sensor(_led, {Humitat::rangesList, 4, true}) {}

void Humitat::begin() {
    this->read();
}

bool Humitat::read() {
    return this->process(this->value = this->dht->readHumidity(), Humitat::colors);
}

const int Humitat::rangesList[4] = {35, 45, 55, 65};

CRGB::HTMLColorCode Humitat::colors[3] = {CRGB::Red, CRGB::Orange, CRGB::Green};
