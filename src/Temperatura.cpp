//
// Created by backo on 4/3/2024.
//

#include "Temperatura.h"

Temperatura::Temperatura(DHT* _dht, CRGB* _ledTemp, CRGB* _ledSetting, int* _tempSetting) :
        dht(_dht), ledSetting(_ledSetting), tempSetting(_tempSetting),
        Sensor(_ledTemp, {Temperatura::tempRangesList, 2, true}) {}

void Temperatura::begin() {
    this->read();
}

bool Temperatura::read() {
    this->value = this->dht->readTemperature();

    int settingRangesList[] = {*this->tempSetting - 1, *this->tempSetting + 1};

    *ledSetting = Temperatura::tempColors[
            Range(settingRangesList, 2, false).getLevel(round(this->value))
    ];

    return this->process(this->value, Temperatura::tempColors);
}

const int Temperatura::tempRangesList[2] = {20, 24};

CRGB::HTMLColorCode Temperatura::tempColors[3] = {CRGB::Green, CRGB::Red};
CRGB::HTMLColorCode Temperatura::settingColors[3] = {CRGB::Blue, CRGB::Green, CRGB::Red};