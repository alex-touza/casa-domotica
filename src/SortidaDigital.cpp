#include "SortidaDigital.h"
#include "Arduino.h"

void SortidaDigital::begin() {
    pinMode(this->pin, OUTPUT);
}

void SortidaDigital::on() {
    this->set(HIGH);
}

void SortidaDigital::off() {
    this->set(LOW);
}

void SortidaDigital::on(unsigned long t) {
    this->set(HIGH, t);
}

void SortidaDigital::off(unsigned long t) {
    this->set(LOW, t);
}

void SortidaDigital::set(int _value) {
    digitalWrite(this->pin, _value);
    this->value = _value;
}

void SortidaDigital::set(int _estat, unsigned long t) {
    this->set(_estat);
    delay(t);
    this->set(!_estat);
}

int SortidaDigital::toggle() {
    this->set(!this->value);
    return this->value;
}

void SortidaDigital::pulseOut() {
    this->on();
    delayMicroseconds(10);
    this->off();
}