#include "Pantalla.h"
#include "Temperatura.h"
#include <Arduino.h>

bool Lines::operator==(const Lines& a) const {
    return (this->upperLine == a.upperLine && this->lowerLine == a.lowerLine);
}

Pantalla::Pantalla(Temperatura* _temp, Humitat* _hum)
        : LiquidCrystal_I2C(0x27, 16, 2), temp(_temp),
          lines({"", ""}), screenId(0), hum(_hum) {}


void Pantalla::begin() {
    this->init();
    this->backlight();
    this->idle();
}

bool Pantalla::update(const String& upperLine, const String& lowerLine, int id, bool forceRefresh) {
    if (this->lines == Lines{upperLine, lowerLine} && !forceRefresh) return false;

    this->screenId = id;

    this->lines.lowerLine = lowerLine;
    this->lines.upperLine = upperLine;

    this->clear();
    this->setCursor(0, 0);
    this->print(upperLine);
    this->setCursor(0, 1);
    this->print(lowerLine);
    return true;
}

bool Pantalla::update(const Lines& _lines, int id, bool forceRefresh) {
    if (this->lines == _lines && !forceRefresh) return false;
    return this->update(_lines.upperLine, _lines.lowerLine, id, forceRefresh);
}

bool Pantalla::idle() {
    // Comprovar si el valor del sensor és NaN (not a number)
    Lines idleLines = this->temp->value == this->temp->value ? Lines{"T " + String(this->temp->value, 1) + " C (" + String(this->temp->setting) + " C)",
                       "H " + String(this->hum->value, 1) + "%"} : Lines{"DHT Error", ""};

    return this->update(idleLines, 0);
}

unsigned char Pantalla::customChars[3][8] = {
        {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
        {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f},
        {0x1f,0x11,0x11,0x11,0x11,0x11,0x1f},
};

unsigned char* Pantalla::getCustomChar(CustomChars name) {
    return Pantalla::customChars[name];
}
