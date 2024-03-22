//
// Created by backo on 18/2/2024.
//

#ifndef CASA_DOMOTICA_JOYSTICK_H
#define CASA_DOMOTICA_JOYSTICK_H

#include "pins/EntradaAnalogica.h"
#include "helpers/Timer.h"

using CDPins::EntradaAnalogica;

template<typename T>
struct Pair {
    T x;
    T y;
};

enum Axis {
    X,
    Y
};

class Joystick {
private:
    int deadzone;

    Pair<int> pos;

    // Obtenir accés d'escriptura-lectura a la posició d'un eix
    int* getPosPtr(Axis axis);

protected:
    Pair<EntradaAnalogica> pins;
public:
    Joystick(int _pinX, int _pinY, int deadzone);

    void begin();

    // Retornen true si la posició ha canviat des de l'última lectura.
    bool read(Axis axis); // Llegir un eix
    bool read();          // Llegir els dos eixos

    // Obtenir accés de només lectura a la posició d'un eix
    const int* getPos(Axis axis);
};


#endif //CASA_DOMOTICA_JOYSTICK_H
