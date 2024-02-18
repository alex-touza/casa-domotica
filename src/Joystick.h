//
// Created by backo on 18/2/2024.
//

#ifndef CASA_DOMOTICA_JOYSTICK_H
#define CASA_DOMOTICA_JOYSTICK_H

#include "EntradaAnalogica.h"
class Joystick {
private:
    int deadzone;
protected:
    EntradaAnalogica* pinX;
    EntradaAnalogica* pinY;
public:
    Joystick(int _pinX, int _pinY, int deadzone);

    // Retorna true si la posició ha canviat des de l'última lectura.
    bool read();

    int posX;
    int posY;
};


#endif //CASA_DOMOTICA_JOYSTICK_H
