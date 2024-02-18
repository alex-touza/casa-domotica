#include "SortidaDigital.h"
#include "Arduino.h"

void SortidaDigital::setup() {
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

void SortidaDigital::set(int _estat) {
    digitalWrite(this->pin, _estat);
    this->estat = _estat;
}

void SortidaDigital::set(int _estat, unsigned long t) {
    this->set(_estat);
    delay(t);
    this->set(!_estat);
}

int SortidaDigital::toggle() {
    this->set(!this->estat);
    return this->estat;
}

void SortidaDigital::pulseOut() {
    this->on();
    delayMicroseconds(10);
    this->off();
}