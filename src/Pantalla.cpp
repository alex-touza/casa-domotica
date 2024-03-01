#include "Pantalla.h"
#include <Arduino.h>

Pantalla::Pantalla(TempHum* _tempHum, int* _tempSetting)
        : LiquidCrystal_I2C(0x27, 16, 2), t(0), maxT(0), tempHum(_tempHum), tempSetting(_tempSetting) {}

void Pantalla::begin() {
    this->init();
    this->backlight();
    this->idle();
}

void Pantalla::update(const String& upperLine, const String& lowerLine) {
    this->clear();
    this->setCursor(0, 0);
    this->print(upperLine);
    this->setCursor(0, 1);
    this->print(lowerLine);
}

void Pantalla::update(const String& upperLine, const String& lowerLine, unsigned long _t) {
    //if (this->t != 0) return;
    this->t = millis();
    this->maxT = _t;
    this->update(upperLine, lowerLine);
}

void Pantalla::idle() {
    this->update("T " + String((int) this->tempHum->temp) + " C (" + String(*this->tempSetting) + " C)",
                 "H " + String((int) this->tempHum->hum) + " %");
}

void Pantalla::checkTime() {
    // Hi ha un temporitzador i la diferència entre el moment
    // actual i el començament és major que la durada?
    if (this->t != 0 && millis() - this->t > this->maxT) {
        // Reiniciar instants
        this->t = 0;
        this->maxT = 0;

        // Tornar a missatge per defecte
        this->idle();
    }
}
