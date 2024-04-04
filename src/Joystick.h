//
// Created by backo on 18/2/2024.
//

#ifndef CASA_DOMOTICA_JOYSTICK_H
#define CASA_DOMOTICA_JOYSTICK_H

#include "pins/EntradaAnalogica.h"
#include "pins/EntradaDigital.h"
#include "helpers/Timer.h"

using CDPins::EntradaAnalogica;
using CDPins::EntradaDigital;

template<typename T>
struct Pair {
    T x;
    T y;
};

enum Axis {
    X,
    Y
};


struct JoystickState {
    Axis axis;
    int pos;
    bool idle;
};

class Joystick {
private:
    int deadzone;

    Pair<int> pos;

    // Obtenir accés d'escriptura-lectura a la posició d'un eix
    int* getPosPtr(Axis axis);

protected:
    Pair<EntradaAnalogica> axisPins;
    EntradaDigital buttonPin;
public:
    Joystick(int _pinX, int _pinY, int _buttonPin, int deadzone);

    void begin();

    // Retornen true si la posició ha canviat des de l'última lectura.
    bool read(Axis axis); // Llegir un eix
    bool read();          // Llegir els dos eixos
    bool readState();     // Llegir i actualitzar state

    JoystickState state;

    bool isPressed(bool debounce = false);

    // Obtenir accés de només lectura a la posició d'un eix
    const int* getPos(Axis axis);
};


#endif //CASA_DOMOTICA_JOYSTICK_H
