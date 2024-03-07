//
// Created by backo on 7/3/2024.
//

#include "Motor.h"

Motor::Motor(int pinInA, int pinInB, int pinEn) : inA(pinInA), inB(pinInB), en(pinEn),
                                                  speed(&en.value), prevSpeed(0), direction(true) {

}

void Motor::begin() {
    this->inA.begin();
    this->inB.begin();
    this->en.begin();
}

void Motor::on() {
    this->en.set(prevSpeed);
    this->inA.set(direction);
    this->inB.set(!direction);
}

void Motor::off() {
    this->prevSpeed = *speed;

    this->en.set(0);
    this->inA.set(0);
    this->inB.set(0);
}

void Motor::setSpeed(int _speed) {
    this->en.set(_speed);
}
