//
// Created by backo on 4/3/2024.
//

#include "Temperatura.h"

Temperatura::Temperatura(int initSetting, DHT* _dht, CRGB* _ledTemp, CRGB* _ledSetting, Motor* _fan) :
        dht(_dht), ledSetting(_ledSetting), setting(initSetting), fan(_fan),
        Sensor(_ledTemp, {Temperatura::tempRangesList, 2, true}) {}

void Temperatura::begin() {
    this->read();
}

bool Temperatura::read() {
    this->value = this->dht->readTemperature();

    int settingRangesList[] = {this->setting - 1, this->setting + 1};

    const Range& range = Range(settingRangesList, 2, false);

    int level = range.getLevel(this->value);

    Serial.println(level);
    Serial.println(this->value);
    Serial.println();

    *ledSetting = Temperatura::settingColors[level];

    int dif = (int)(round(this->value) - this->setting);

    if (dif > 0) {
        this->fan->setSpeed(map(constrain(dif, 0, 10), 0, 10, 100, 255));
    } else this->fan->off();

    return this->process(this->value, Temperatura::tempColors);
}

const int Temperatura::tempRangesList[4] = {18, 20, 24, 26};
CRGB::HTMLColorCode Temperatura::tempColors[3] = {CRGB::Red, CRGB::Yellow, CRGB::Green};

CRGB::HTMLColorCode Temperatura::settingColors[3] = {CRGB::Red, CRGB::Green, CRGB::Blue};
