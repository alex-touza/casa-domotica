//
// Created by backo on 4/3/2024.
//

#include "Temperatura.h"

Temperatura::Temperatura(DHT* _dht, CRGB* _led) :
        dht(_dht),
        Sensor(_led, {Temperatura::rangesList, 2, false}) {}

void Temperatura::begin() {
    this->read();
}

bool Temperatura::read() {
    return this->process(this->dht->readTemperature(), Temperatura::colors);
}

const int Temperatura::rangesList[2] = {20, 24};

CRGB::HTMLColorCode Temperatura::colors[3] = {CRGB::Blue, CRGB::Green, CRGB::Red};