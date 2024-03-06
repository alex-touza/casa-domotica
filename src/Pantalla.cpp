#include "Pantalla.h"
#include "Temperatura.h"
#include <Arduino.h>

bool Lines::operator==(const Lines& a) const {
    return (this->upperLine == a.upperLine && this->lowerLine == a.lowerLine);
}

Pantalla::Pantalla(Temperatura* _temp, Humitat* _hum)
        : LiquidCrystal_I2C(0x27, 16, 2), t(0), maxT(0), temp(_temp), isIdle(true),
          lines({"", ""}), hum(_hum) {}

void Pantalla::begin() {
    this->init();
    this->backlight();
    this->idle();
}

bool Pantalla::update(const String& upperLine, const String& lowerLine, bool forceRefresh, bool forceIdle) {
    if (this->lines == Lines{upperLine, lowerLine} && !forceRefresh) return false;

    this->isIdle = forceIdle;


    this->lines.lowerLine = lowerLine;
    this->lines.upperLine = upperLine;

    this->clear();
    this->setCursor(0, 0);
    this->print(upperLine);
    this->setCursor(0, 1);
    this->print(lowerLine);
    return true;
}

bool Pantalla::update(const Lines& _lines, bool forceRefresh, bool forceIdle) {
    return this->update(_lines.upperLine, _lines.lowerLine, forceRefresh, forceIdle);
}

void Pantalla::update(const String& upperLine, const String& lowerLine, unsigned long _t) {
    //if (this->t != 0) return;
    this->t = millis();
    this->maxT = _t;
    this->update(upperLine, lowerLine);
}

Lines Pantalla::idle() {
    Lines idleLines = {"T " + String(this->temp->value, 1) + " C (" + String(*this->temp->tempSetting) + " C)",
                       "H " + String(this->hum->value, 1) + " %"};

    this->update(idleLines, false, true);
    return idleLines;
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
