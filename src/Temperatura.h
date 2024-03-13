//
// Created by backo on 4/3/2024.
//

#ifndef CASA_DOMOTICA_TEMPERATURA_H
#define CASA_DOMOTICA_TEMPERATURA_H

#include "Sensor.h"
#include "Pantalla.h"
#include "Motor.h"

// forward declaration per permetre friend Pantalla
class Pantalla;

class Temperatura : public Sensor {
private:
    static const int tempRangesList[];
    static CRGB::HTMLColorCode tempColors[];
    static CRGB::HTMLColorCode settingColors[];

    DHT* dht;
    CRGB* ledSetting;
    Motor* fan;

    // Permetre a pantalla l'accés a membres privats.
    friend Pantalla;
public:
    Temperatura(int initSetting, DHT* _dht, CRGB* _ledTemp, CRGB* _ledSetting, Motor* _fan);

    void begin() override;
    bool read() override;

    int setting;


};


#endif //CASA_DOMOTICA_TEMPERATURA_H
