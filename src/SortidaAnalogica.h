#ifndef CASA_DOMOTICA_SORTIDAANALOGICA_H
#define CASA_DOMOTICA_SORTIDAANALOGICA_H

#include <Arduino.h>
#include "Pin.h"

namespace CDPins {
    class SortidaAnalogica : public Pin {
    public:
        using Pin::Pin;

        void begin() override;

        void set(int valor);

        void set(int valor, int min, int max);

        int value;
    };
}


#endif