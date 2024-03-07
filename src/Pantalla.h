//
// Created by backo on 1/3/2024.
//

#ifndef CASA_DOMOTICA_PANTALLA_H
#define CASA_DOMOTICA_PANTALLA_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Temperatura.h"
#include "Humitat.h"

/*
El compilador adverteix que la llibreria no està feta per ESP32,
 però teòricament això no és un problema:
 https://www.electronics-lab.com/project/using-16x2-i2c-lcd-display-esp32/#comment-398778
 */
class Temperatura;

struct Lines {
    String upperLine;
    String lowerLine;

    bool operator==(const Lines& a) const;
};

class Pantalla : LiquidCrystal_I2C {
private:
    unsigned long t;
    unsigned long maxT;
    Temperatura* temp;
    Humitat* hum;

public:
    explicit Pantalla(Temperatura* _temp, Humitat* _hum);

    void begin();

    /*
     * forceRefresh: Força que la pantalla es refresqui encara que el contingut no canviï.
     *
     * Retorna true si la pantalla s'ha refrescat.
     */
    bool update(const String& upperLine, const String& lowerLine, bool forceRefresh = false, bool forceIdle = false);

    bool update(const Lines& _lines, bool forceRefresh = false, bool forceIdle = false);

    void update(const String& upperLine, const String& lowerLine, unsigned long t);

    Lines idle();

    void checkTime();

    bool isIdle;

    Lines lines;
};


#endif //CASA_DOMOTICA_PANTALLA_H
