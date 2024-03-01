//
// Created by backo on 18/2/2024.
//

#ifndef CASA_DOMOTICA_JOYSTICK_H
#define CASA_DOMOTICA_JOYSTICK_H

#include "EntradaAnalogica.h"

using CDPins::EntradaAnalogica;

template<typename T>
struct Pos {
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

    // Obtenir accés d'escriptura-lectura a la posició d'un eix
    int* getPosPtr(Axis axis);

protected:
    EntradaAnalogica* pinX;
    EntradaAnalogica* pinY;
public:
    Joystick(int _pinX, int _pinY, int deadzone);

    void begin();

    // Retornen true si la posició ha canviat des de l'última lectura.
    bool read(Axis axis); // Llegir un eix
    bool read();          // Llegir els dos eixos

    Pos<int> pos;

    Pos<unsigned long> lastUpdated;

    // Obtenir accés de només lectura a la posició d'un eix
    const int* getPos(Axis axis);
};


#endif //CASA_DOMOTICA_JOYSTICK_H
