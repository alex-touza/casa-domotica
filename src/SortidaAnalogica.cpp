#include "SortidaAnalogica.h"
#include "Arduino.h"

void SortidaAnalogica::begin() {
    pinMode(this->pin, OUTPUT);
}

void SortidaAnalogica::set(int _value) {
    analogWrite(this->pin, _value);
    this->value = _value;
}

void SortidaAnalogica::set(int _value, int min, int max) {
    this->set(map(constrain(_value, min, max), min, max, 1023, 0));
}
