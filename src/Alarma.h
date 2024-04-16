//
// Created by backo on 12/3/2024.
//

#ifndef CASA_DOMOTICA_ALARMA_H
#define CASA_DOMOTICA_ALARMA_H

#include "pins/EntradaDigital.h"
#include "FastLED.h"
#include "helpers/LEDArray.h"

using CDPins::EntradaDigital;



class Alarma : private LEDArray {
private:
    EntradaDigital sensor;
    EntradaDigital button;

    static CRGB::HTMLColorCode colors[2];

    bool wasPressed;
    int interval;
    int mod;
public:
    enum class State {
        IDLE,        // El botó no s'ha premut
        PRESSED,     // El botó s'ha premut, però l'alarma estava desactivada
        DEACTIVATED, // El botó s'ha premut i ha desactivat l'alarma
        TRIGGERED    // L'alarma s'ha activat
    };

    Alarma(int buttonPin, int sensorPin, CRGB* _leds[], int _ledsSize);

    bool active;

    State state;

    void begin(int _interval, int _mod);
    void read();

    static String stateToString(State st);
};


#endif //CASA_DOMOTICA_ALARMA_H
