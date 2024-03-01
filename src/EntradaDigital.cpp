#include "EntradaDigital.h"
#include "Arduino.h"


void CDPins::EntradaDigital::begin() {
    pinMode(this->pin, INPUT);
}

int CDPins::EntradaDigital::read() {
    return this->value = digitalRead(this->pin);
}

unsigned long CDPins::EntradaDigital::pulseIn() {
    this->value = 0;
    return ::pulseIn(this->pin, HIGH);
}
