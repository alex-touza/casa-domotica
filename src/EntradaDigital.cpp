#include "EntradaDigital.h"
#include "Arduino.h"


void CDPins::EntradaDigital::begin() {
    pinMode(this->pin, INPUT);
}

unsigned int CDPins::EntradaDigital::read() {
    return this->value = digitalRead(this->pin);
}

unsigned long CDPins::EntradaDigital::pulseIn() {
    this->value = 0;
    return ::pulseIn(this->pin, HIGH);
}

/*
void CDPins::EntradaDigital::attachInterrupt(InterruptModes mode, void (* callback)()) {
    ::attachInterrupt(digitalPinToInterrupt(this->pin), callback, mode);
}

template<typename T>
void CDPins::EntradaDigital::attachInterrupt(InterruptModes mode, void (* callback)(T), T* arg) {
    ::attachInterruptArg(digitalPinToInterrupt(this->pin), callback, arg, mode);
}*/
