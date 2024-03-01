//
// Created by backo on 29/2/2024.
//

#include "TempHum.h"
#include "Range.h"
#include "Arduino.h"

TempHum::TempHum(int _pin, CRGB* _ledTemp, CRGB* _ledHum) :
        pin(_pin), DHT(_pin, DHT11), ledTemp(_ledTemp),
        ledHum(_ledHum), temp(0), hum(0) {
    this->tempRange = new Range(tempRangesList, 4, true);
    this->humRange = new Range(humRangesList, 4, true);
}



void TempHum::begin() {
    DHT::begin();

    this->read();
}

bool TempHum::read() {
    double prevTemp = this->temp;
    double prevHum = this->hum;

    this->temp = this->readTemperature();
    this->hum = this->readHumidity();

    if (abs(this->temp - prevTemp) < 1e-9 && abs(this->hum - prevHum) < 1e-9)
        return false;

    int tempLevel = this->tempRange->getLevel(round(this->temp));
    int humLevel = this->humRange->getLevel(round(this->hum));

    *this->ledTemp = TempHum::colors[tempLevel];
    *this->ledHum = TempHum::colors[humLevel];

    return true;

}

CRGB TempHum::colors[] = {CRGB::Red, CRGB::Yellow, CRGB::Green};

const int TempHum::tempRangesList[4] = {16, 20, 24, 26};
const int TempHum::humRangesList[4] = {35, 45, 55, 65};