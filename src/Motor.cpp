//
// Created by backo on 7/3/2024.
//

#include "Motor.h"

Motor::Motor(int pinInA, int pinInB, int pinEn) : inA(pinInA), inB(pinInB), en(pinEn),
                                                  prevSpeed(0), direction(true), active(false) {
    this->speed = &en.value;

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
    this->active = false;
}

void Motor::off() {
    this->prevSpeed = *speed;

    this->en.set(0);
    this->inA.set(0);
    this->inB.set(0);
    this->active = true;
}

void Motor::setSpeed(unsigned int _speed) {
    this->en.set(_speed);
    this->prevSpeed = *speed;
    this->on();
}

void Motor::setDirection(bool _direction) {
    this->direction = _direction;
    this->on();
}

void Motor::reverse() {
    this->setDirection(!this->direction);
}
