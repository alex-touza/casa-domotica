//
// Created by backo on 18/2/2024.
//

#include "Joystick.h"

Joystick::Joystick(int _pinX, int _pinY, int _deadzone = 10) : deadzone(_deadzone), pos({0, 0}),
                                                               pins({EntradaAnalogica{_pinX},
                                                               EntradaAnalogica{_pinY}}) {}

bool Joystick::read() {
    // Operador OR que no curtcircuita perquè s'evaluïn els dos operands.
    // Clever code > readability :)
    return read(X) | read(Y);
}

bool Joystick::read(Axis axis) {
    int* posAxis = getPosPtr(axis);
    EntradaAnalogica* pin = axis == X ? &this->pins.x : &this->pins.y;

    // [=] fa que es puguin accedir a les mateixes variables (com 'this')
    // que des de fora de la lambda.
    // Aplicar la deadzone.
    auto round = [=](int _pos) -> int { return abs(_pos) > this->deadzone ? _pos : 0; };

    int prev = *posAxis;

    *posAxis = round(::map((int) pin->read(), 0, 4095, -100, 100));


    return !(*posAxis == prev && *posAxis == 0);
}

void Joystick::begin() {
    this->pins.y.begin();
    this->pins.x.begin();
}

// Aquest és el mètode privat, usat per accedir fàcilment
// a un valor.
// TODO Utilitzar template perquè es pugui utilitzar també per a pins
int* Joystick::getPosPtr(Axis axis) {
    return axis == X ? &this->pos.x : &this->pos.y;

}

// Aquest és el mètode públic. No hauríem de voler canviar la
// posició des de fora de la classe; per això es retorna un
// punter constant.
const int* Joystick::getPos(Axis axis) {
    return getPosPtr(axis);
}