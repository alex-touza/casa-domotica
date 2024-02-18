#include "EntradaDigital.h"
#include "Arduino.h"


void EntradaDigital::begin() {
    pinMode(this->pin, INPUT);
}

int EntradaDigital::read() {
    this->value = digitalRead(this->pin);
    return this->value;
}

unsigned long EntradaDigital::pulseIn() {
    this->value = 0;
    return ::pulseIn(this->pin, HIGH);
}
