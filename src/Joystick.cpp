//
// Created by backo on 18/2/2024.
//

#include "Joystick.h"

Joystick::Joystick(int _pinX, int _pinY, int _buttonPin, int _deadzone = 10) : deadzone(_deadzone), pos({0, 0}),
                                                                               axisPins({EntradaAnalogica{_pinX},
                                                                                         EntradaAnalogica{_pinY}}),
                                                                               buttonPin(_buttonPin),
                                                                               state({X, 0, true, 0}) {}

bool Joystick::read() {
    // Operador OR que no curtcircuita perquè s'evaluïn els dos operands.
    // Clever code > readability :)
    return read(X) | read(Y);
}

bool Joystick::read(Axis axis) {
    int* posAxis = getPosPtr(axis);
    EntradaAnalogica* pin = axis == X ? &this->axisPins.x : &this->axisPins.y;

    // [=] fa que es puguin accedir a les mateixes variables (com 'this')
    // que des de fora de la lambda.
    // Aplicar la deadzone.
    auto round = [=](int _pos) -> int { return abs(_pos) > this->deadzone ? _pos : 0; };

    *posAxis = round(::map((int) pin->read(), 0, 4095, -100, 100));

    return *posAxis != 0;
}

void Joystick::begin() {
    this->axisPins.y.begin();
    this->axisPins.x.begin();
}

// Aquest és el mètode privat, usat per accedir fàcilment
// a un valor.
// TODO Utilitzar template perquè es pugui utilitzar també per a axisPins
int* Joystick::getPosPtr(Axis axis) {
    return axis == X ? &this->pos.x : &this->pos.y;
}

// Aquest és el mètode públic. No hauríem de voler canviar la
// posició des de fora de la classe; per això es retorna un
// punter constant.
const int* Joystick::getPos(Axis axis) {
    return getPosPtr(axis);
}

bool Joystick::isPressed(bool debounce) {
    return this->buttonPin.read(debounce, false);
}

bool Joystick::readState() {
    bool active = this->read();

    if (this->state.idle && active) {
        if (abs(this->pos.x) > (abs(this->pos.y) + this->deadzone + 5)) {
            this->state.axis = X;
            this->state.pos = this->pos.x;
            this->state.idle = false;
        } else if (abs(this->pos.y) > (abs(this->pos.x) + this->deadzone + 5)) {
            this->state.axis = Y;
            this->state.pos = this->pos.y;
            this->state.idle = false;
        }
    } else if (active) {
        this->state.pos = *this->getPos(this->state.axis);
    } else {
        this->state.idle = true;
        this->state.lastActive = millis();
    }

    Serial.println("idle \t" + String(this->state.idle));
    Serial.println("axis \t" + String(this->state.axis));
    Serial.println("pos \t" + String(this->state.pos));
    //Serial.println("pressed \t" + String(this->isPressed()));
    Serial.println("pressed deb \t" + String(this->isPressed(true)));
    Serial.println("last active \t" + String(this->state.lastActive));
    Serial.println("raw");
    Serial.println("\t x " + String(this->pos.x));
    Serial.println("\t y " + String(this->pos.y));
    Serial.println();
;
    return active;
}

bool Joystick::State::operator==(const Joystick::State& other) const {
    return this->idle ? other.idle : (!other.idle && other.axis == this->axis && other.pos == this->pos);
}

bool Joystick::State::operator!=(const Joystick::State& other) const {
    return !(*this == other);
}
