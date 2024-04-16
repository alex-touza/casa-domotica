#include "Pantalla.h"
#include "Temperatura.h"
#include <Arduino.h>

bool Lines::operator==(const Lines& a) const {
    return (this->upperLine == a.upperLine && this->lowerLine == a.lowerLine);
}

Pantalla::Pantalla(Temperatura* _temp, Humitat* _hum, Iluminacio* _ilum)
        : LiquidCrystal_I2C(0x27, 16, 2), temp(_temp), ilum(_ilum),
          lines({"", ""}), screenId(0), hum(_hum), timer() {}


void Pantalla::begin() {
    this->init();
    this->backlight();
    this->idle();
}

void Pantalla::update(const String& upperLine, const String& lowerLine, int id, bool forceRefresh) {
    if (this->lines == Lines{upperLine, lowerLine} && !forceRefresh) return;
    this->timer.active = false;

    this->screenId = id;

    this->lines.lowerLine = lowerLine;
    this->lines.upperLine = upperLine;

    this->clear();
    this->setCursor(0, 0);
    this->print(upperLine);
    this->setCursor(0, 1);
    this->print(lowerLine);
}

void Pantalla::update(const Lines& _lines, int id, bool forceRefresh) {
    if (this->lines == _lines && !forceRefresh) return;
    this->update(_lines.upperLine, _lines.lowerLine, id, forceRefresh);
}

void Pantalla::updateTimed(const Lines& _lines, unsigned long t, int id, bool forceRefresh) {
    this->update(_lines, id, forceRefresh);
    delay(t);
    this->idle();
}
/*
bool Pantalla::checkTime() {
    bool finished = this->timer.hasFinished() && this->timer.active;

    if (finished) {
        this->idle();
        this->timer.active = false;
    }

    return finished;
}

*/

void Pantalla::idle() {
    // Comprovar si el valor del sensor és NaN (not a number)
    if (this->temp->value != this->temp->value) {
        this->update("DHT Error", "");
    } else {
        String upperLine = "T " + String(this->temp->value, 1) + " C (" + String(this->temp->setting) + " C)";
        String lowerLine = "H " + String(this->hum->value, 1) + "%  L ";

        this->update(upperLine, lowerLine + this->ilum->brightnessStr(), 0);
    }
}


