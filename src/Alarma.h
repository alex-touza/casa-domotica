//
// Created by backo on 12/3/2024.
//

#ifndef CASA_DOMOTICA_ALARMA_H
#define CASA_DOMOTICA_ALARMA_H

#include "EntradaDigital.h"
#include "FastLED.h"

using CDPins::EntradaDigital;

class Alarma {
private:
    const int ledsSize;
    EntradaDigital button;
    EntradaDigital sensor;
    CRGB** leds;

    static CRGB::HTMLColorCode colors[2];

    int interval{-1};
    int mod{-1};
public:
    Alarma(int buttonPin, int sensorPin, CRGB* _leds[], int _ledsSize);

    bool active;

    void begin(int _interval, int _mod);
    bool read();


};


#endif //CASA_DOMOTICA_ALARMA_H
