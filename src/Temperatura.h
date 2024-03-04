//
// Created by backo on 4/3/2024.
//

#ifndef CASA_DOMOTICA_TEMPERATURA_H
#define CASA_DOMOTICA_TEMPERATURA_H

#include "Sensor.h"

class Temperatura : public Sensor {
private:
    static const int rangesList[];
    static CRGB::HTMLColorCode colors[];

    DHT* dht;
public:
    explicit Temperatura(DHT* _dht, CRGB* _led);

    void begin() override;
    bool read() override;
};


#endif //CASA_DOMOTICA_TEMPERATURA_H
