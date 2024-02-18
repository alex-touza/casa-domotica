//
// Created by backo on 18/2/2024.
//

#include "EntradaAnalogica.h"
#include "Arduino.h"

void EntradaAnalogica::setup() {
    pinMode(this->pin, INPUT);
}

unsigned int EntradaAnalogica::read() { return analogRead(this->pin); }
