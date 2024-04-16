//
// Created by backo on 7/3/2024.
//

#ifndef CASA_DOMOTICA_MOTOR_H
#define CASA_DOMOTICA_MOTOR_H
#include "pins/SortidaDigital.h"
#include "pins/SortidaAnalogica.h"

using CDPins::SortidaAnalogica;
using CDPins::SortidaDigital;

class Motor {
private:
    unsigned int prevSpeed;
protected:
    SortidaDigital inA;
    SortidaDigital inB;
    SortidaAnalogica en;

public:
    Motor(int pinInA, int pinInB, int pinEn);

    void begin();

    void on();
    void off();
    void setSpeed(unsigned int _speed);
    void setDirection(bool _direction);
    void reverse();

    bool active;

    const unsigned int* speed; // punter a en.value

    bool direction; // true: A, false: B
};


#endif //CASA_DOMOTICA_MOTOR_H
