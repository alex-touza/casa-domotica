//
// Created by backo on 12/3/2024.
//

#include "Alarma.h"

Alarma::Alarma(int buttonPin, int sensorPin, CRGB* _leds[], int _ledsSize) : active(false), button(buttonPin),
                                                                             sensor(sensorPin),
                                                                             LEDArray(_leds, _ledsSize), interval(-1),
                                                                             mod(-1) {}

void Alarma::begin(int _interval, int _mod) {
    this->interval = _interval;
    this->mod = _mod;

    this->sensor.begin();
    this->button.begin();
}

bool Alarma::read() {
    if (!this->sensor.read()) this->active = true; // NOLINT(*-branch-clone)
    else if (!this->button.read()) this->active = false;

    this->setColorAll(Alarma::colors[(millis() / this->interval) % this->mod && this->active]);

    return this->active;
}

CRGB::HTMLColorCode Alarma::colors[2] = {CRGB::Black, CRGB::Red};