//
// Created by backo on 29/2/2024.
//

#ifndef CASA_DOMOTICA_RANGE_H
#define CASA_DOMOTICA_RANGE_H

#include "Arduino.h"

class Range {
private:
    int size;
    bool cycle;
public:
    int* range;
    Range(int _range[], int _size, bool _cycle = false);

    int getLevel(double n) const;
};


#endif //CASA_DOMOTICA_RANGE_H
