#ifndef EntradaDigital_h
#define EntradaDigital_h

#include <Arduino.h>
#include "Pin.h"

class EntradaDigital : Pin {
public:
    using Pin::Pin;

    void setup() override;

    int read();

    /*
    Equivalent a la funció integrada corresponent amb un
    interval de 10 microsegons.
    */
    unsigned long pulseIn();
};

#endif