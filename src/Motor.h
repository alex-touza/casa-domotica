//
// Created by backo on 7/3/2024.
//

#ifndef CASA_DOMOTICA_MOTOR_H
#define CASA_DOMOTICA_MOTOR_H
#include "SortidaDigital.h"
#include "SortidaAnalogica.h"

using CDPins::SortidaAnalogica;
using CDPins::SortidaDigital;

class Motor {
protected:
    SortidaDigital inA;
    SortidaDigital inB;
    SortidaAnalogica en;

public:
    Motor(int pinInA, int pinInB, int pinEn);

    void begin();

    void on();
    void off();
    void setSpeed(int _speed);

    // void reverse();

    const int* speed;
    int prevSpeed;

    bool direction; // true: A, false: B


};


#endif //CASA_DOMOTICA_MOTOR_H
