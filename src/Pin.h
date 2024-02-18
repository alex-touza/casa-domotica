#ifndef CASA_DOMOTICA_PIN_H
#define CASA_DOMOTICA_PIN_H

// Classe abstracta per als pins d'entrada i sortida
class Pin {
protected:
    const int pin;
public:
    explicit Pin(int _pin);
    virtual void setup(); // virtual => obliga a ser redefinit en la classe filla

    int value;
};


#endif //CASA_DOMOTICA_PIN_H
