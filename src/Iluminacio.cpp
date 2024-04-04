//
// Created by backo on 19/3/2024.
//

#include "Iluminacio.h"

Iluminacio::Iluminacio(int pinButton, CRGB** _leds, int _ledsSize) : brightness(255), on(false), button(pinButton),
                                                                     LEDArray(_leds, _ledsSize) {}

void Iluminacio::begin() {
    this->button.begin();
}

void Iluminacio::changeBrightness(int delta) {
    this->brightness += delta;
    this->brightness = constrain(this->brightness, 0, 255);
    this->update();
}

void Iluminacio::read() {
    if (this->button.read(true, true)) {
        this->on = !this->on;
        update();
    }
}

void Iluminacio::update() {
    this->setColorAll(CHSV{0, 0, static_cast<uint8_t>(this->on ? this->brightness : 0)});
}

String Iluminacio::brightnessStr() const {
    static int prev = -1;
    static String str = "";

    if (prev == -1 || prev != this->brightness) {
        if (this->on) {
            str = String(((float) this->brightness) / 2.55, 0) + "%";
        } else {
            str = "OFF";
        }
    }

    prev = this->brightness;

    return str;
}
