//
// Created by backo on 18/2/2024.
//

#include "Joystick.h"

Joystick::Joystick(int _pinX, int _pinY, int _deadzone = 10) : deadzone(_deadzone
) {
    this->pinX = new EntradaAnalogica(_pinX);
    this->pinY = new EntradaAnalogica(_pinY);
}

bool Joystick::read() {
    // Declarem les funcions amb lambda per no repetir-les per cada eix.
    // [this] captura la instància de la classe.
    auto read = [](EntradaAnalogica* pin) -> int { return ::map(pin->read(), 0, 4095, -100, 100); };
    auto round = [this](int pos) -> int { return abs(((pos))) > this->deadzone ? pos : 0; };

    int prevX = this->posX;
    int prevY = this->posY;

    this->posX = round(read(this->pinX));
    this->posY = round(read(this->pinY));

    return prevX != this->posX || prevY != this->posY;
}