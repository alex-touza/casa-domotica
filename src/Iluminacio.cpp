//
// Created by backo on 19/3/2024.
//

#include "Iluminacio.h"

Iluminacio::Iluminacio(int pinButton, CRGB** _leds, int _ledsSize) : brightness(255), isOn(false), button(pinButton),
                                                                     LEDArray(_leds, _ledsSize) {}

void Iluminacio::begin() {
    this->button.begin();
}

void Iluminacio::changeBrightness(int delta) {
    this->brightness += delta;
    this->brightness = constrain(this->brightness, 0, 255);
    this->update();
}

bool Iluminacio::read() {
    if (this->button.read(true, true)) {
        Serial.println("lights button pressed");
        Serial.println();

        this->isOn = !this->isOn;
        update();
        return true;
    }
    return false;
}

void Iluminacio::update() {
    this->setColorAll(CHSV{0, 0, static_cast<uint8_t>(this->isOn ? this->brightness : 0)});
}

String Iluminacio::brightnessStr() const {
    String str = "";

    if (this->isOn) {
        str = String(((float) this->brightness) / 2.55, 0) + "%";
    } else {
        str = "OFF";
    }


    Serial.println("brightness " + str);
    Serial.println();

    return str;
}
