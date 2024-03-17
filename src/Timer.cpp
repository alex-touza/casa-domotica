#include "Arduino.h"
#include "Timer.h"

Timer::Timer(unsigned long _duration) : duration(_duration), start(0), active(false) {}
Timer::Timer() : Timer(0) {}

void Timer::reset() {
    this->start = millis();
}

unsigned long Timer::delta() {
    return millis() - this->start;
}

bool Timer::hasFinished() {
    return this->delta() > this->duration || !active;
}
