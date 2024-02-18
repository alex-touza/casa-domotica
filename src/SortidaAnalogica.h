#ifndef SortidaAnalogica_h
#define SortidaAnalogica_h

#include <Arduino.h>
#include "Pin.h"

class SortidaAnalogica : Pin {
public:
    using Pin::Pin;

    void setup() override;

    void set(int valor);

    void set(int valor, int min, int max);

    int value;
};

#endif