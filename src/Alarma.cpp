//
// Created by backo on 12/3/2024.
//

#include "Alarma.h"

Alarma::Alarma(int buttonPin, int sensorPin, CRGB* _leds[], int _ledsSize) : active(false), button(buttonPin),
                                                                             sensor(sensorPin),
                                                                             LEDArray(_leds, _ledsSize), interval(-1),
                                                                             mod(-1), state(Alarma::State::IDLE),
                                                                             wasPressed(false) {}

void Alarma::begin(int _interval, int _mod) {
    this->interval = _interval;
    this->mod = _mod;

    this->sensor.begin();
    this->button.begin();
}

void Alarma::read() {
    Alarma::State ret = Alarma::State::IDLE;

    this->button.read(false, true);

    if (this->sensor.read(false, true)) {
        this->active = true;
        this->wasPressed = false;
        ret = Alarma::State::TRIGGERED;

    } else {
        if (this->active && this->button.value) {
            this->active = false;
            this->wasPressed = true;
            ret = Alarma::State::DEACTIVATED;

        } else if (this->wasPressed && !this->button.value) this->wasPressed = false;
        else if (!this->wasPressed && this->button.value) {
            ret = Alarma::State::PRESSED;
            this->wasPressed = true;
        }
    }
    this->setColorAll(Alarma::colors[(millis() / this->interval) % this->mod && this->active]);

    Serial.println("alarm " + (this->active ? "ACTIVE" : Alarma::stateToString(this->state)));
    Serial.println();

    this->state = ret;
}

CRGB::HTMLColorCode Alarma::colors[2] = {CRGB::Black, CRGB::Red};

String Alarma::stateToString(Alarma::State s) {
    switch (s) {
        case State::IDLE:
            return "IDLE";
        case State::PRESSED:
            return "PRESSED";
        case State::DEACTIVATED:
            return "DEACTIVATED";
        case State::TRIGGERED:
            return "TRIGGERED";
        default:
            return "unknown";
    }
}
