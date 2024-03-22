//
// Created by backo on 4/3/2024.
//

#ifndef CASA_DOMOTICA_TIMER_H
#define CASA_DOMOTICA_TIMER_H


class Timer {
public:
    explicit Timer(unsigned long _duration);
    Timer();

    bool active;
    unsigned long duration;
    unsigned long start;

    void reset();           // Reiniciar el temporitzador.
    unsigned long delta() const;  // Temps des de l'últim reinici.
    bool hasFinished() const;
};


#endif //CASA_DOMOTICA_TIMER_H
