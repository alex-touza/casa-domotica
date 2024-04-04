#include "Pantalla.h"
#include "Temperatura.h"
#include <Arduino.h>

bool Lines::operator==(const Lines& a) const {
    return (this->upperLine == a.upperLine && this->lowerLine == a.lowerLine);
}

Pantalla::Pantalla(Temperatura* _temp, Humitat* _hum, Iluminacio* _ilum)
        : LiquidCrystal_I2C(0x27, 16, 2), temp(_temp), ilum(_ilum),
          lines({"", ""}), screenId(0), hum(_hum) {}


void Pantalla::begin() {
    this->init();
    this->backlight();
    this->idle();
}

void Pantalla::update(const String& upperLine, const String& lowerLine, int id, bool forceRefresh) {
    if (this->lines == Lines{upperLine, lowerLine} && !forceRefresh) return;

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
    return this->update(_lines.upperLine, _lines.lowerLine, id, forceRefresh);
}

void Pantalla::idle() {
    // Comprovar si el valor del sensor és NaN (not a number)
    if (this->temp->value == this->temp->value) {
        this->update("DHT Error", "");
    } else {
        String upperLine = "T " + String(this->temp->value, 1) + " C (" + String(this->temp->setting) + " C)";
        String lowerLine = "H " + String(this->hum->value, 1) + "%  L ";

        for (int i = 0; i < 13-lowerLine.length(); ++i) {
            lowerLine += " ";
        }

        this->update(upperLine, lowerLine + ilum->brightnessStr(), 0);
    }
}

unsigned char Pantalla::customChars[3][8] = {
        {0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0},
        {0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f},
        {0x1f,0x11,0x11,0x11,0x11,0x11,0x1f},
};

unsigned char* Pantalla::getCustomChar(CustomChars name) {
    return Pantalla::customChars[name];
}
