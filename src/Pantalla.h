//
// Created by backo on 1/3/2024.
//

#ifndef CASA_DOMOTICA_PANTALLA_H
#define CASA_DOMOTICA_PANTALLA_H
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "TempHum.h"

class Pantalla : LiquidCrystal_I2C {
private:
    unsigned long t;
    unsigned long maxT;
    TempHum* tempHum;
    int* tempSetting;

public:
    explicit Pantalla(TempHum* _tempHum, int* _tempSetting);
    void begin();

    void update(const String& upperLine, const String& lowerLine);
    void update(const String& upperLine, const String& lowerLine, unsigned long t);

    void idle();

    void checkTime();
};


#endif //CASA_DOMOTICA_PANTALLA_H
