//
// Created by backo on 18/2/2024.
//

#include "EntradaAnalogica.h"
#include "Arduino.h"

void EntradaAnalogica::begin() {
    pinMode(this->pin, INPUT);
}

unsigned int EntradaAnalogica::read() {
    this->value = analogRead(this->pin);
    return this->value;
}
