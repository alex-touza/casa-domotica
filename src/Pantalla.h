//
// Created by backo on 1/3/2024.
//

#ifndef CASA_DOMOTICA_PANTALLA_H
#define CASA_DOMOTICA_PANTALLA_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include "Temperatura.h"
#include "Humitat.h"
#include "Iluminacio.h"
#include "helpers/Timer.h"

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

class Pantalla : private LiquidCrystal_I2C {
private:
    Temperatura* temp;
    Humitat* hum;
    Iluminacio* ilum;

    Timer timer;

public:
    Pantalla(Temperatura* _temp, Humitat* _hum, Iluminacio* _ilum);

    void begin();

    /*
     * forceRefresh: Força que la pantalla es refresqui encara que el contingut no canviï.
     *
     * Retorna true si la pantalla s'ha refrescat.
     */
    void update(const String& upperLine, const String& lowerLine, int id = -1, bool forceRefresh = false);

    void update(const Lines& _lines, int id = -1, bool forceRefresh = false);

    void updateTimed(const Lines& _lines, unsigned long t, int id = -1, bool forceRefresh = false);
    //bool checkTime();

    void idle();

    int screenId;

    Lines lines;
};


#endif //CASA_DOMOTICA_PANTALLA_H
