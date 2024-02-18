#include "EntradaDigital.h"
#include "Arduino.h"


void EntradaDigital::setup() {
    pinMode(this->pin, INPUT);
}

int EntradaDigital::read() { return digitalRead(this->pin); }

unsigned long EntradaDigital::pulseIn() { return ::pulseIn(this->pin, HIGH); }
