//
// Created by backo on 4/3/2024.
//

#ifndef CASA_DOMOTICA_HUMITAT_H
#define CASA_DOMOTICA_HUMITAT_H

#include "Sensor.h"

class Humitat : public Sensor {
private:
    static int rangesList[];
    static CRGB::HTMLColorCode colors[];

    DHT* dht;
public:
    Humitat(DHT* _dht, CRGB* _led);

    void begin() override;
    bool read() override;
};


#endif //CASA_DOMOTICA_HUMITAT_H