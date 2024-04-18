//
// Created by backo on 19/3/2024.
//

#ifndef CASA_DOMOTICA_ILUMINACIO_H
#define CASA_DOMOTICA_ILUMINACIO_H
#include "helpers/LEDArray.h"
#include "pins/EntradaDigital.h"

using CDPins::EntradaDigital;
class Iluminacio : private LEDArray {
protected:
    EntradaDigital button;
public:

    Iluminacio(int pinButton, CRGB** _leds, int _ledsSize);

    void begin();
    bool read();
    void changeBrightness(int delta);
    void update();


    bool isOn;
    int brightness;

    String brightnessStr() const;

};


#endif //CASA_DOMOTICA_ILUMINACIO_H
