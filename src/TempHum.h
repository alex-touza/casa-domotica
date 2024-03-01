//
// Created by backo on 29/2/2024.
//

#ifndef CASA_DOMOTICA_TEMPHUM_H
#define CASA_DOMOTICA_TEMPHUM_H
#include <DHT.h>
#include "Pin.h"
#include "Range.h"
#include "FastLED.h"

class TempHum : private DHT {
private:
    CRGB* ledTemp;
    CRGB* ledHum;

    // constexpr fa que sigui una constant de compilació, i així
    // poder-la declarar aquí mateix
    // https://stackoverflow.com/questions/13346879/const-vs-constexpr-on-variables
    static const int tempRangesList[];
    static const int humRangesList[];

    static CRGB colors[];

    Range* tempRange;
    Range* humRange;
protected:
    int pin;
public:
    explicit TempHum(int _pin, CRGB* _ledTemp, CRGB* _ledHum);
    void begin();

    bool read();
    double temp;
    double hum;

};


#endif //CASA_DOMOTICA_TEMPHUM_H
