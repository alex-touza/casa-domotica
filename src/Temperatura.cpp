//
// Created by backo on 4/3/2024.
//

#include "Temperatura.h"
#include "Arduino.h"

Temperatura::Temperatura(int initSetting, DHT* _dht, CRGB* _ledTemp, CRGB* _ledSetting, Motor* _fan) :
        dht(_dht), ledSetting(_ledSetting), setting(initSetting), fan(_fan), season(Temperatura::Seasons::SUMMER),
        Sensor(_ledTemp, {Temperatura::seasons[0], 4, true}) {
}

void Temperatura::begin() {
    this->read();
}

void Temperatura::setSeason(Seasons _season) {
    this->season = _season;
    //this->range.range = _season == Temperatura::SUMMER ? Temperatura::summer : Temperatura::winter;
    this->range.range = Temperatura::seasons[_season];
}

bool Temperatura::read() {
    this->value = this->dht->readTemperature();

    int settingRangesList[] = {this->setting - 1, this->setting + 1};

    const Range& range = Range(settingRangesList, 2, false);

    int level = range.getLevel(this->value);

    *ledSetting = Temperatura::settingColors[level];

    int dif = (int)(round(this->value) - this->setting);

    if (dif > 0) {
        this->fan->setSpeed(map(constrain(dif, 0, 10), 0, 10, 100, 255));
    } else this->fan->off();

    return this->process(this->value, Temperatura::tempColors);
}
// estiu, hivern

/*
int Temperatura::summer[4] = {20, 24, 26, 29};
int Temperatura::winter[4] = {17, 21, 24, 26};
 */

int Temperatura::seasons[SEASONS][4] = {{20, 24, 26, 29}, {17, 21, 24, 26}};
String Temperatura::seasonsName[SEASONS] = {"Estiu", "Hivern"};

CRGB::HTMLColorCode Temperatura::tempColors[3] = {CRGB::Red, CRGB::Orange, CRGB::Green};

CRGB::HTMLColorCode Temperatura::settingColors[3] = {CRGB::OrangeRed, CRGB::Green, CRGB::Blue};


