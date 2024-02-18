//
// Created by backo on 18/2/2024.
//

#ifndef CASA_DOMOTICA_ENTRADAANALOGICA_H
#define CASA_DOMOTICA_ENTRADAANALOGICA_H

#include "Arduino.h"
#include "Pin.h"

class EntradaAnalogica : Pin {
public:
    using Pin::Pin;

    void setup() override;

    unsigned int read();
};


#endif //CASA_DOMOTICA_ENTRADAANALOGICA_H
