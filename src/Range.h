//
// Created by backo on 29/2/2024.
//

#ifndef CASA_DOMOTICA_RANGE_H
#define CASA_DOMOTICA_RANGE_H

#include "Arduino.h"

/*
 * Rang amb múltiples estats i modes.
 *
 * Usat per als rangs de temperatura, on hi ha tres
 * estats (correcte, millorable, inadequat) i dos
 * modes (estiu, hivern).
 */
class Range {
private:
    int size;
    bool cycle;
    const int* range;
public:
    Range(const int _range[], int _size, bool _cycle = false);

    int getLevel(int n);
};


#endif //CASA_DOMOTICA_RANGE_H
