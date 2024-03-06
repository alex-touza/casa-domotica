//
// Created by backo on 4/3/2024.
//

#ifndef CASA_DOMOTICA_TEMPERATURA_H
#define CASA_DOMOTICA_TEMPERATURA_H

#include "Sensor.h"
#include "Pantalla.h"

// forward declaration per permetre friend Pantalla
class Pantalla;

class Temperatura : public Sensor {
private:
    static const int tempRangesList[];
    static CRGB::HTMLColorCode tempColors[];
    static CRGB::HTMLColorCode settingColors[];

    DHT* dht;

    CRGB* ledSetting;

    int* tempSetting;

    // Permetre a pantalla l'accés a membres privats.
    friend Pantalla;
public:
    explicit Temperatura(DHT* _dht, CRGB* _ledTemp, CRGB* _ledSetting, int* _tempSetting);

    void begin() override;
    bool read() override;


};


#endif //CASA_DOMOTICA_TEMPERATURA_H
