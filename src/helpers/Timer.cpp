#include "Arduino.h"
#include "Timer.h"

Timer::Timer(unsigned long _duration) : duration(_duration), start(0), active(false) {}
Timer::Timer() : Timer(0) {}

void Timer::reset() {
    this->start = millis();
    this->active = true;
}

void Timer::reset(unsigned long _duration) {
    this->duration = _duration;
    this->reset();
}


unsigned long Timer::delta() const {
    return millis() - this->start;
}

bool Timer::hasFinished() const {
    return this->delta() > this->duration || !active;
}

