//
// Created by backo on 12/3/2024.
//

#include "Alarma.h"

Alarma::Alarma(int buttonPin, int sensorPin, CRGB* _leds[], int _ledSize) : active(false), button(buttonPin),
                                                                            sensor(sensorPin), leds(_leds),
                                                                            ledsSize(_ledSize) {}

void Alarma::begin(int _interval, int _mod) {
    this->interval = _interval;
    this->mod = _mod;

    this->sensor.begin();
    this->button.begin();
}

bool Alarma::read() {
    if (!this->sensor.read()) this->active = true; // NOLINT(*-branch-clone)
    else if (!this->button.read()) this->active = true;

    CRGB::HTMLColorCode ledsColor = Alarma::colors[(millis() / this->interval) % this->mod && this->active];

    for (int i = 0; i < this->ledsSize; ++i) {
        *this->leds[i] = ledsColor;
    }

    return this->active;
}

CRGB::HTMLColorCode Alarma::colors[2] = {CRGB::Black, CRGB::Red};