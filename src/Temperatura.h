//
// Created by backo on 4/3/2024.
//

#ifndef CASA_DOMOTICA_TEMPERATURA_H
#define CASA_DOMOTICA_TEMPERATURA_H

#define SEASONS 2

#include "Sensor.h"
#include "Pantalla.h"
#include "Motor.h"


// forward declaration per permetre friend Pantalla
class Pantalla;

class Temperatura : public Sensor {
private:
    /*
    static int summer[4];
    static int winter[4];
     */
    static int seasons[SEASONS][4];
    static CRGB::HTMLColorCode tempColors[];
    static CRGB::HTMLColorCode settingColors[];

    DHT* dht;
    CRGB* ledSetting;
    Motor* fan;
public:
    enum Seasons {
        SUMMER = 0,
        WINTER = 1
    };

    static String seasonsName[SEASONS];

    Temperatura(int initSetting, DHT* _dht, CRGB* _ledTemp, CRGB* _ledSetting, Motor* _fan);

    void begin() override;

    bool read() override;

    void setSeason(Seasons _season);

    Seasons season;

    int setting;


};


#endif //CASA_DOMOTICA_TEMPERATURA_H
